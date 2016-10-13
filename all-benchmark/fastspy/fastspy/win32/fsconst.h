#ifndef _FSCONST_
#define _FSCONST_

/**/
/* Win32 Version                                                             */
/* Custom Constants Definition. There is one of this file for each porting   */
/* Contains the mapping of the exported constants of system calls            */
/**/

/* Winsocket constants abstraction                                           */
#define FS_SOCKET_ERROR     SOCKET_ERROR
#define FS_INVALID_SOCKET   INVALID_SOCKET

#define FS_EWOULDBLOCK      WSAEWOULDBLOCK
#define FS_ECONALREADYBLOCK WSAEWOULDBLOCK
#define FS_ENOBUFS          WSAENOBUFS
#endif
