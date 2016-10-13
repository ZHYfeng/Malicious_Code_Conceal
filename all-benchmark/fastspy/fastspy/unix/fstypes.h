#ifndef _FSTYPES_
#define _FSTYPES_

/**/
/* Unix Version                                                              */
/* Custom Definitions of types. There is one of this file for each porting   */
/* Contains the mapping of the exported types of system calls                */
/**/
#include "fsincludes.h"

#define BOOL              long

#define VOID              void
#define PVOID             void *

#define SHORT             short
#define USHORT            unsigned short
#define PSHORT            short *
#define PUSHORT           unsigned short *

#define INT               int
#define UINT              unsigned int
#define PINT              int *
#define PUINT             unsigned int *

#define LONG              long
#define ULONG             unsigned long
#define PLONG             long *
#define PULONG            unsigned long *

#define CHAR              char
#define UCHAR             unsigned char
#define PCHAR             char *
#define PUCHAR            unsigned char *

#define FLOAT             float
#define DOUBLE            double


#define FS_SEMHANDLE      sem_t *
#define FS_TASKHANDLE     pthread_t        
#define FS_SOCK           int
#define SOCKADDR_IN       struct sockaddr_in


/* *** Exception to kal function (compatible fcnt between win32 and unix)    */
int stricmp (const char *string1, const char *string2);
#endif
