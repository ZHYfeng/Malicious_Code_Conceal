/* Falls er sich mal aus dem Staub macht ... 
 *
 * $ cc -O2 nacs.c get.c file_ops.c -o nacs
 * $ strip nacs 
 *
 * NetW0rker/ S V A T
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "vx.h"

#undef DEBUG
 
int scan_dir (char*, char*, int);
int disinfect(char*);

int main (int argc, char *argv[])
{
   	int FLAG = 0; /* == 0 -> nicht saeubern, == 1 saeubern */
 
        if (argc < 2) {
       	        printf("\n\n        nacs V 0.1 Beta   \\/ ><    Virusscanner fuer den LDV I\n\n"
                       "Aufruf: <nacs [directory] [logfile]> scannt 'directory' mit allen Unterverzeichnissen\n\n");
                exit(0);
        }        
  
     	if (argc == 4)
           	FLAG = 1;
     	scan_dir (argv[1], argv[2], FLAG);
        printf ("\n\nnacs: fertig\n\n");
        return 0;
}
 
/*------------------------------------------------- */
 
int scan_dir (char *directory, char *logfile, int flag) 
{ 
     	FILE *fd;
        char *fileapath; 
        struct dirent **filelist;
        struct stat buf;
        int count = 0,i = 0;
        char *detectstring = "VLP";
 
        fd = fopen(logfile, "w+"); /* return egal */
      	if ((fileapath = (char*) (malloc (1000))) == NULL)
           	perror (""), exit (1);
        if ((i = scandir (directory, &filelist, 0, 0)) == -1) // dir. scannen
           	perror (""), exit (2);
        for (count = 2; count < i; count++) {  /* alle gefundenen Dateien,ausser "." , ".."  */
           	if ((fileapath = strcpy (fileapath, directory)) == NULL) // Pfad
                perror (""), exit (3);
                fileapath = strcat (fileapath, "/");  /* Trenner */
                if ((fileapath = strcat (fileapath, filelist[count]->d_name)) == NULL) // + Datei
                   	perror (""), exit (4);
                stat (fileapath, &buf); 
                if ((buf.st_mode & S_IFDIR) == S_IFDIR) /* falls Unterverzeichniss */
                   	scan_dir (fileapath, logfile, flag); /* rekursiv weiter */
                else { /* sonst scannen */
                        printf("\r                                     ");
                        printf("                                     \r");
                        printf("Datei <%s> ist ", fileapath);
                        if (isinfected (fileapath)) {
                           	if (fd != NULL)
                                   	fprintf(fd, "Datei <%s> ist infiziert.", fileapath);
                           	printf ("infiziert");
                                if (flag) {
                                   	disinfect(fileapath);
                                        printf(" ... I disinfect ...");
                                        if (fd != NULL)
                                           	fprintf(fd, " ... I disinfect ...");
                                }        
                        if (fd != NULL)
                           	fprintf(fd, "\n");
                        }
                        else 
                           	printf("sauber");  
                        fflush(stdout);
                } /* else      */
        } /* for */
        return count;
}


int disinfect(char *file)
{
   	int in, out, r;
        char *buf;        
                
        buf = (char*)malloc(10000);
        if (buf == NULL)
           	perror(""), exit(1);
        cp(file, "./tmp");
        in = open("./tmp", O_RDWR);
        out = open(file, O_RDWR|O_TRUNC);
        lseek(in, VLENGTH, SEEK_SET); /* ueber virus wegSEEKEN */
        while ((r = read(in, buf, 10000)) > 0) /* cleanen teil kopieren */
           	write(out, buf, r);
        close(in);
        close(out);
        remove("./tmp");
        return 0;
}
 
        
