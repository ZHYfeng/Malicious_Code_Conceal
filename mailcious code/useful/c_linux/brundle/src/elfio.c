/*
 * Brundle Fly - Good-natured Linux ELF virus supporting kernel 2.2 and 2.4
 * Copyright 2001 Konrad Rieck <kr@roqe.org>, Konrad Kretschmer <kk@roqe.org>
 * In memory to Seth Brundle 
 *
 * This file holds all functions related to the ELF file format. Note: those
 * functions are used in inject and elf2bin, but *NOT* in the Brundle Fly
 * virus. The Brundle Fly virus uses own variants of these functions that
 * are not that space consuming.
 *
 * $Id: elfio.c,v 1.5 2001/07/11 18:34:48 kr Exp $
 */

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <config.h>
#include <elfio.h>
#include <brundle-fly.h>

/*
 * Print all information of the given ELF header. 
 */
void print_ehdr(Elf_Ehdr * e)
{
    printf("Elf header\n");
    printf("  Magic number               (e_ident):     ");
    printf("%s\n", e->e_ident);

    printf("  Object file type           (e_type):      ");
    switch (e->e_type) {

    case ET_NONE:
	printf("No file type\n");
	break;
    case ET_REL:
	printf("Relocatable file\n");
	break;
    case ET_EXEC:
	printf("Executable file\n");
	break;
    case ET_DYN:
	printf("Shared object file\n");
	break;
    case ET_CORE:
	printf("Core file\n");
	break;
    default:
	printf("Unknown type\n");
    }

    printf("  Architecture               (e_machine):   ");
    switch (e->e_machine) {
    case EM_NONE:
	printf("No machine\n");
	break;
    case EM_M32:
	printf("AT&T WE 32100\n");
	break;
    case EM_SPARC:
	printf("SUN SPARC\n");
	break;
    case EM_386:
	printf("Intel 80386\n");
	break;
    case EM_68K:
	printf("Motorola m68k family\n");
	break;
    case EM_88K:
	printf("Motorola m88k family\n");
	break;
    case EM_860:
	printf("Intel 80860\n");
	break;
    case EM_MIPS:
	printf("MIPS R3000 big-endian\n");
	break;
    case EM_PARISC:
	printf("HPPA\n");
	break;
    case EM_VPP500:
	printf("Fujitsu VPP500\n");
	break;
    case EM_SPARC32PLUS:
	printf("Sun's \"v8plus\"\n");
	break;
    case EM_960:
	printf("Intel 80960\n");
	break;
    case EM_PPC:
	printf("PowerPC\n");
	break;
    case EM_V800:
	printf("NEC V800 series\n");
	break;
    case EM_FR20:
	printf("Fujitsu FR20\n");
	break;
    case EM_RH32:
	printf("TRW RH32\n");
	break;
    case EM_MMA:
	printf("Fujitsu MMA\n");
	break;
    case EM_ARM:
	printf("ARM\n");
	break;
    case EM_FAKE_ALPHA:
	printf("Digital Alpha\n");
	break;
    case EM_SH:
	printf("Hitachi SH\n");
	break;
    case EM_SPARCV9:
	printf("SPARC v9 64-bit\n");
	break;
    case EM_TRICORE:
	printf("Siemens Tricore\n");
	break;
    case EM_ARC:
	printf("Argonaut RISC Core\n");
	break;
    case EM_H8_300:
	printf("Hitachi H8/300\n");
	break;
    case EM_H8_300H:
	printf("Hitachi H8/300H\n");
	break;
    case EM_H8S:
	printf("Hitachi H8S\n");
	break;
    case EM_H8_500:
	printf("Hitachi H8/500\n");
	break;
    case EM_IA_64:
	printf("Intel Merced\n");
	break;
    case EM_MIPS_X:
	printf("Stanford MIPS-X\n");
	break;
    case EM_COLDFIRE:
	printf("Motorola Coldfire\n");
	break;
    case EM_68HC12:
	printf("Motorola M68HC12\n");
	break;
    default:
	printf("Unknown machine\n");
    }

    printf("  Object File Version        (e_version):   ");
    printf("%d\n", e->e_version);
    printf("  Entry point                (e_entry):     ");
    printf("0x%.8x\n", e->e_entry);
    printf("  Elf hdr size               (e_ehsize):    ");
    printf("%d\n", e->e_ehsize);
    printf("\n");
    printf("  Program hdr tbl off        (e_phoff):     ");
    printf("%d\n", e->e_phoff);
    printf("  Program hdr tbl entry size (e_phentsize): ");
    printf("%d\n", e->e_phentsize);
    printf("  Program hdr tbl entry num  (e_phnum):     ");
    printf("%d\n", e->e_phnum);
    printf("\n");
    printf("  Section hdr tbl off        (e_shoff):     ");
    printf("%d\n", e->e_shoff);
    printf("  Section hdr tbl entry size (e_shentsize): ");
    printf("%d\n", e->e_shentsize);
    printf("  Section hdr tbl entry num  (e_shnum):     ");
    printf("%d\n", e->e_shnum);
    printf("------------------------------------------------------\n");
}

/*
 * Print all information fo the given section header. 
 */
void print_shdr(Elf_Shdr * s)
{
    printf("Section header:\n");
    printf("  Section name               (sh_name):     ");
    printf("%d\n", s->sh_name);

    printf("  Section type               (sh_type):     ");
    switch (s->sh_type) {

    case SHT_NULL:
	printf("Section header table entry unused\n");
	break;
    case SHT_PROGBITS:
	printf("Program data\n");
	break;
    case SHT_SYMTAB:
	printf("Symbol table\n");
	break;
    case SHT_STRTAB:
	printf("String table\n");
	break;
    case SHT_RELA:
	printf("Relocation entries with addends\n");
	break;
    case SHT_HASH:
	printf("Symbol hash table\n");
	break;
    case SHT_DYNAMIC:
	printf("Dynamic linking information\n");
	break;
    case SHT_NOTE:
	printf("Notes\n");
	break;
    case SHT_NOBITS:
	printf("Program space with no data (bss)\n");
	break;
    case SHT_REL:
	printf("Relocation entries, no addends\n");
	break;
    case SHT_SHLIB:
	printf("Reserved\n");
	break;
    case SHT_DYNSYM:
	printf("Dynamic linker symbol table\n");
	break;
    case SHT_NUM:
	printf("Number of defined types. \n");
	break;
    case SHT_LOOS:
	printf("Start OS-specific\n");
	break;
    case SHT_GNU_verdef:
	printf("Version definition section. \n");
	break;
    case SHT_GNU_verneed:
	printf("Version needs section. \n");
	break;
    case SHT_GNU_versym:
	printf("Version symbol table. \n");
	break;
    case SHT_LOPROC:
	printf("Start of processor-specific\n");
	break;
    case SHT_HIPROC:
	printf("End of processor-specific\n");
	break;
    case SHT_LOUSER:
	printf("Start of application-specific\n");
	break;
    case SHT_HIUSER:
	printf("End of application-specific\n");
	break;
    default:
	printf("Unknown type\n");
    }

    printf("  Section flags              (sh_flags):    ");
    printf("0x%.8x\n", s->sh_flags);
    printf("  Section address at exec    (sh_addr):     ");
    printf("0x%.8x\n", s->sh_addr);
    printf("  Section offset             (sh_offset):   ");
    printf("%d\n", s->sh_offset);
    printf("  Section size               (sh_size):     ");
    printf("%d\n", s->sh_size);
    printf("  Section link to next       (sh_link):     ");
    printf("%d\n", s->sh_link);
    printf("------------------------------------------------------\n");
}

/*
 * Print all information of the given program header. 
 */
void print_phdr(Elf_Phdr * p)
{
    printf("Program header:\n");
    printf("  Segment type               (p_type):      ");

    switch (p->p_type) {

    case PT_NULL:
	printf("Program header table entry unused\n");
	break;
    case PT_LOAD:
	printf("Loadable program segment\n");
	break;
    case PT_DYNAMIC:
	printf("Dynamic linking information\n");
	break;
    case PT_INTERP:
	printf("Program interpreter\n");
	break;
    case PT_NOTE:
	printf("Auxiliary information\n");
	break;
    case PT_SHLIB:
	printf("Reserved\n");
	break;
    case PT_PHDR:
	printf("Entry for header table itself\n");
	break;
    case PT_NUM:
	printf("Number of defined types. \n");
	break;
    case PT_LOOS:
	printf("Start of OS-specific\n");
	break;
    case PT_HIOS:
	printf("End of OS-specific\n");
	break;
    case PT_LOPROC:
	printf("Start of processor-specific\n");
	break;
    case PT_HIPROC:
	printf("End of processor-specific\n");
	break;
    default:
	printf("Unknown type\n");
    }

    printf("  Segment offset             (p_offset):    ");
    printf("%d\n", p->p_offset);
    printf("  Segment flags              (p_flags):     ");
    printf("0x%.8x\n", p->p_flags);
    printf("  Segment virtual address    (p_vaddr):     ");
    printf("0x%.8x\n", p->p_vaddr);
    printf("  Segment physical address   (p_paddr):     ");
    printf("0x%.8x\n", p->p_paddr);
    printf("  Segment size in file       (p_filesz):    ");
    printf("%d\n", p->p_filesz);
    printf("  Segment size in memory     (p_memsz):     ");
    printf("%d\n", p->p_memsz);
    printf("------------------------------------------------------\n");
}

/*
 * Read in an ELF header for the file given by the file descriptor fd. 
 * The space for the ELF header is allocated on the heap and needs to be
 * free'd using free(). 
 */
Elf_Ehdr *read_ehdr(int fd)
{
    Elf_Ehdr *ehdr;
    ehdr = (Elf_Ehdr *) malloc(sizeof(Elf_Ehdr));

    if (read(fd, ehdr, sizeof(Elf_Ehdr)) != sizeof(Elf_Ehdr)) {
	perror("read ehdr");
	exit(EXIT_FAILURE);
    }

    if (strncmp((const char *) ehdr->e_ident, ELFMAG, SELFMAG)) {
	fprintf(stderr, "Not an ELF file.\n");
	exit(EXIT_FAILURE);
    }
    return ehdr;
}

/*
 * Read in an section header for the file given by the file descriptor fd. 
 * The space for the section header is allocated on the heap and needs to be
 * free'd using free().
 */
Elf_Shdr *read_shdrs(int fd, Elf_Ehdr * e)
{
    Elf_Shdr *shdrs;
    int shdrs_len;

    shdrs_len = sizeof(Elf_Shdr) * e->e_shnum;
    shdrs = (Elf_Shdr *) malloc(shdrs_len);

    if (lseek(fd, e->e_shoff, SEEK_SET) < 0) {
	perror("lseek shdrs");
	exit(EXIT_FAILURE);
    }

    if (read(fd, shdrs, shdrs_len) != shdrs_len) {
	perror("read shdrs");
	exit(1);
    }

    return shdrs;
}

/*
 * Read in an program header for the file given by the file descriptor fd. 
 * The space for the program header is allocated on the heap and needs to be
 * free'd using free().
 */
Elf_Phdr *read_phdrs(int fd, Elf_Ehdr * e)
{
    Elf_Phdr *phdrs;
    int phdrs_len;

    phdrs_len = sizeof(Elf_Phdr) * e->e_phnum;
    phdrs = (Elf_Phdr *) malloc(phdrs_len);

    if (lseek(fd, e->e_phoff, SEEK_SET) < 0) {
	perror("lseek phdrs");
	exit(EXIT_FAILURE);
    }

    if (read(fd, phdrs, phdrs_len) != phdrs_len) {
	perror("read phdrs");
	exit(1);
    }
    return phdrs;
}

/* 
 * Check if the file containing the given ELF header is a suitable 
 * host for the Brundle Fly virus. 
 */
int check_host(Elf_Ehdr * e)
{
    if (e->e_type != ET_EXEC && e->e_type != ET_DYN) {
	fprintf(stderr, "Error.\nNot an executable file.\n");
	return 0;
    }

    if (e->e_machine != EM_386) {
	fprintf(stderr, "Error.\nWrong architecture.\n");
	return 0;
    }

    if (e->e_version != EV_CURRENT) {
	fprintf(stderr, "Error.\nVersion mismatch.\n");
	return 0;
    }
    return 1;
}
