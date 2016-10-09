/*
 * Brundle Fly - Good-natured Linux ELF virus supporting kernel 2.2 and 2.4
 * Copyright 2001 Konrad Rieck <kr@roqe.org>, Konrad Kretschmer <kk@roqe.org>
 * In memory to Seth Brundle 
 *
 * This is a debugging program. Useful to display information about an 
 * ELF file. We liked it during the creation of Brundle Fly. 
 *
 * $Id: elfstat.c,v 1.4 2001/07/11 18:34:48 kr Exp $
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <config.h>
#include <elfio.h>

char *filename;

/* 
 * Print the stat struct of the file. 
 */
void print_stat(struct stat *st, char *filename)
{
    printf("File stats\n");
    printf("  File name:    %s\n", filename);
    printf("  File size:    %ld\n", st->st_size);
    printf("  Permission:   %o\n", st->st_mode & 0x01ff);
    printf("  Owner uid:    %d\n", st->st_uid);
    printf("  Owner gid:    %d\n", st->st_gid);
    printf("\n");
}

/*
 * Read in the stat struct using fstat. 
 */
struct stat *read_stat(fd)
{
    struct stat *st;

    st = (struct stat *) malloc(sizeof(struct stat));

    if (fstat(fd, st) < 0) {
	perror("fstat");
	exit(EXIT_FAILURE);
    }

    if (!S_ISREG(st->st_mode)) {
	fprintf(stderr, "%s: Not a regular file\n", filename);
	exit(EXIT_FAILURE);
    }
    return st;
}

/*
 * Bla? Bla!
 */
void print_usage(void)
{
    fprintf(stderr, "usage: elfstat [-ehps] <elf-file>\n");
    fprintf(stderr, "options:  -e  print Elf header\n");
    fprintf(stderr, "          -s  print Elf section headers\n");
    fprintf(stderr, "          -p  print Elf program headers\n");
    fprintf(stderr, "          -h  print this help screen\n");
}

int main(int argc, char **argv)
{
    extern char *optarg;
    extern int optind, opterr, optopt;

    Elf_Ehdr *ehdr;
    Elf_Shdr *shdrs;
    Elf_Phdr *phdrs;
    int show_ehdr = 0, show_shdrs = 0, show_phdrs = 0, usage = 0;
    int fd, i, c;

    while ((c = getopt(argc, argv, "ehps")) != EOF)
	switch (c) {
	case 'e':
	    show_ehdr++;
	    break;
	case 'p':
	    show_phdrs++;
	    break;
	case 's':
	    show_shdrs++;
	    break;
	default:
	    usage++;
	    break;
	}

    if (usage || argc == optind) {
	print_usage();
	exit(EXIT_FAILURE);
    }

    filename = argv[optind];

    if ((fd = open(filename, O_RDONLY)) < 0) {
	perror(filename);
	exit(EXIT_FAILURE);
    }

    print_stat(read_stat(fd), filename);

    /*
     * Read in ELF header, section headers and program headers. 
     */
    ehdr = read_ehdr(fd);
    shdrs = read_shdrs(fd, ehdr);
    phdrs = read_phdrs(fd, ehdr);

    if (show_ehdr)
	print_ehdr(ehdr);

    /*
     * Iterate through the program headers and print them if show_phdrs
     * is set. 
     */
    if (show_phdrs) {
	for (i = 0; i < ehdr->e_phnum; i++) {
	    print_phdr(phdrs);
	    phdrs++;
	}
	phdrs -= ehdr->e_phnum;
    }

    /*
     * Iterate through the section headers and print them if show_shdrs
     * is set. 
     */
    if (show_shdrs) {
	for (i = 0; i < ehdr->e_shnum; i++) {
	    print_shdr(shdrs);
	    shdrs++;
	}
	shdrs -= ehdr->e_shnum;
    }


    close(fd);

    free(ehdr);
    free(phdrs);
    free(shdrs);

    return EXIT_SUCCESS;
}
