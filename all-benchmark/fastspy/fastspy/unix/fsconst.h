#ifndef _FSCONST_
#define _FSCONST_

/**/
/* Unix Version                                                              */
/* Custom Constants Definition. There is one of this file for each porting   */
/* Contains the mapping of the exported constants of system calls            */
/**/

/* General constants                                                         */
#define TRUE   1
#define FALSE  0
/* Berkley constants abstraction                                             */
#define FS_INVALID_SOCKET   (-1) /* Returned by socket() on error            */
#define FS_SOCKET_ERROR     (-1) /* Returned by tx-rx funct. on error        */
/* op. would block when non-blocking mode set on connect                     */ 
#define FS_ECONNWOULDBLOCK      EINPROGRESS 
#define FS_ECONALREADYBLOCK     EALREADY
#define FS_EISCONNECTED         EISCONN
/* op. would block when non-blocking mode set on recv                        */ 
#define FS_ERECVWOULDBLOCK      EAGAIN 
#define FS_ENOBUFS              ENETUNREACH /* mapped in the much similar err*/
#endif
