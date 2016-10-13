/**/
/* Kernel Abstraction Layer Absoloute prototypes and constant                */  
/* This is Not a Custom File                                                 */
/**/
#include "fstypes.h"

/**/
/* Absolute KAL Constants that must be supported in fskal.c                  */
/**/

/* General                                                                   */
#define FS_FAIL        0   
#define FS_OK          1


/* Semaphores routines constant and return codes:                            */
#define WAIT_FOREVER        -1
#define SEM_TIMEOUT          0
#define SEM_OK               1
#define SEM_FAIL             2

/* Tasks routines constant and return codes                                  */

/**/
/* Prototypes                                                                */
/* See fskal.c for a brief explanation of each function                      */
/**/

BOOL            KalInit ( VOID );
BOOL            KalClose ( VOID );

FS_SEMHANDLE    KalCreateSemaphore( PCHAR SemaphoreName );
USHORT          KalKillSemaphore (FS_SEMHANDLE shSemHandle);
USHORT          KalReceiveUnit( FS_SEMHANDLE shSemHandle, LONG lTimeOut );
USHORT          KalSendUnit( FS_SEMHANDLE shSemHandle );

FS_TASKHANDLE   KalCreateTask ( PVOID TaskEntryPoint, PVOID pParam);
BOOL            KalTerminateTask ( FS_TASKHANDLE  pNull );

INT             KalGetLastError ( VOID );
INT             KalCancelBlockingCall( VOID );
VOID            KalSleep( LONG lTime );
LONG            KalGetTimerValue ( VOID );
BOOL            KalSetBlockingMode ( FS_SOCK sckSock, BOOL bMode );
FILE  *         KalOpenServicesFile ( VOID );

