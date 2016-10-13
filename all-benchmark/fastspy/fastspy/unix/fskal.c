/**/
/* Kernel Abstraction Layer: Per system implementation of syscalls           */  
/* KAL for Unix/POSIX                                                         */ 
/**/
#include "fsincludes.h" 
#include "fstypes.h"
#include "fsconst.h"

#include "fskal.h"


typedef void *(*thread_funct_t)(void *);

int stricmp (const char *string1, const char *string2)
 {
   return (strcasecmp (string1, string2));
 }   


/**/
/* KalInit: Functions for intialization of libraries goes here               */
/* Input:   none.                                                            */
/* Output:  Boolean value: TRUE ok; FALSE not                                */
/**/           
BOOL KalInit ( VOID )
 {
   return (TRUE);
 }

/**/
/* KalClose: Functions for DEintialization of libraries goes here            */
/* Input:   none.                                                            */
/* Output:  Boolean value: TRUE ok; FALSE not                                */
/**/           
BOOL KalClose ( VOID )
 {
   return (TRUE);
 }

/**/
/* KalCreateSemaphore: creates a semaphore                                   */
/* Input:              PCHAR; Semaphore Name                                 */
/* Output:             FS_SEMHANDLE; Sem Handle: NULL if fails               */
/**/           
FS_SEMHANDLE KalCreateSemaphore( PCHAR SemaphoreName )
 {
   sem_t        *pSem;
   INT          nResult;
  
   /* sem_t is a structure so we will return back a pointer to a memory      */
   /* allocated by us containing that struct                                 */
   if ( !(pSem = (sem_t *) malloc (sizeof (sem_t))) )
      return ((FS_SEMHANDLE) NULL);
   
   /* Note: Seamphore Name has been ignored due to the lack of posix 1.b     */
   /*       implementation of Linux (sem_open doesn't exist)                 */
   /*       The object should do its work if called whithin the process space*/ 
   /*       used only by its handle.                                         */
   /* Creating an EMPTY semaphore                                            */
   if ((nResult = sem_init (pSem, 0, 0)) != 0)
    {
      free (pSem); /* releasing memory for error */
      return ((FS_SEMHANDLE) NULL);
    }
   
   return ((FS_SEMHANDLE) pSem);
 }

/**/
/* KalKillSemaphore: remove a semaphore and its allocated resources          */
/* Input:            FS_SEMHANDLE seamphore handle                           */
/* Output:           USHORT Code: SEM_OK remove ok; SEM_FAIL failing         */
/**/
USHORT KalKillSemaphore (FS_SEMHANDLE shSemHandle)
 {
   sem_destroy(shSemHandle);
   free (shSemHandle);

   return (SEM_OK);
 }

/**/
/* KalReceiveUnit: waits a unit from the semaphore                           */
/* Input:          FS_SEMHANDLE; Sem Handle                                  */
/*                 LONG; Timeout to wait in millisec or WAIT_FOREVER         */  
/* Output:         USHORT Code: SEM_TIMEOUT; SEM_OK; SEM_FAIL                */
/**/
USHORT KalReceiveUnit( FS_SEMHANDLE shSemHandle, LONG lTimeOut )
 {
   /* timeout on semaphore NOT implemented right now due to limit in posix   */
   /* standard call (pheraps it should be possible with variable condition)  */
   if (lTimeOut != WAIT_FOREVER)
      return (SEM_FAIL);

   sem_wait (shSemHandle); /* always return 0 so why checking the error?     */
   return (SEM_OK); 
 }


/**/
/* KalSendUnit: Send a unit to the semaphore                                  */
/* Input:       FS_SEMHANDLE; Semaphore Handler                               */
/* Output:      USHORT Code: SEM_OK; SEM_FAIL                                 */
/**/
USHORT KalSendUnit( FS_SEMHANDLE shSemHandle )
 {
   if ( sem_post (shSemHandle) != 0)
     return (SEM_FAIL); /* see last error */
   return (SEM_OK);
 }


/**/
/* KalCreateTask: Create a task using a thread                                */
/* Input:         PVOID; Pointer to the function to be run as thread          */
/*                PVOID; Option pointer to parameters of task, NULL if none   */
/* Output:        FS_TASKHANDLE; The task handle or NULL if fails             */
/* Note:          Priority not supported                                      */
/**/
FS_TASKHANDLE KalCreateTask ( PVOID TaskEntryPoint, PVOID pParam)
 {
  pthread_t        thread;
  pthread_attr_t   attr;
      

  pthread_attr_init(&attr);
  pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_DETACHED);
  if (pthread_create (&thread, &attr, (thread_funct_t) TaskEntryPoint, 
                      (void *) pParam) != 0 )
    {
       perror ("pthread_create:");
       return ( (FS_TASKHANDLE) NULL );  
    }

  return ( (FS_TASKHANDLE) thread );
 }

/**/
/* KalTerminateTask: Terminate a task                                         */
/* Input:      FS_TASKHANDLE *; NULL for current thread                       */ 
/* Output:     Boolean value: TRUE ok; FALSE not                              */
/**/
BOOL KalTerminateTask ( FS_TASKHANDLE  pNull )
 {
  pthread_exit (NULL);
  return (TRUE); 
 }

/**/
/* KalGetLastError: Gets the last error occured in the network libray         */
/* Input:         none;                                                       */
/* Output:        The error that should be remapped in defconst.h             */
/**/
INT KalGetLastError ( VOID )
 {
  return (errno); 
 }

/**/
/* KALCancelBlockingCall: Cancels a pendent blocking call                     */
/* Input:         none;                                                       */
/* Output:        The error that should be remapped in defconst.h             */
/**/
INT KalCancelBlockingCall( VOID )
 {
  return (0); /* not yet implemented */
 }

/**/
/* KALSleep: Sleep for a specified time in milliseconds                       */
/* Input:    LONG; Time in millisecods                                        */
/* Output:   none                                                             */
/* Note:     Better if used a realtime sleep                                  */
/**/
VOID KalSleep( LONG lTime )
 {
  usleep (lTime * 1000); /* < milliseconds precision */
 }

/**/
/* KalGetTimerValue: Returns the number of milliseconds, modulo 2^32,         */
/*                   since the start of the current session.                  */
/* Input:   none                                                              */
/* Output:  LONG; The timer value expressed in millisecond                    */
/* Note:    Used to compute the time difference for diagnostic and timing     */
/**/
LONG KalGetTimerValue ( VOID )
 {
   struct timeval t;
   gettimeofday( &t, NULL );
   return (t.tv_sec * 1000) + (t.tv_usec / 1000);
 } 

/**/
/* KalSetBlockingMode: Sets a socket descriptor to (non)blocking operation    */
/* Input:   socket to be set                                                  */
/*          boolean TRUE Blocking Mode; FALSE NonBlocking Mode                */
/* Output:  BOOL; Result of operation (TRUE ok; FALSE fail)                   */
/* Note:    Used to manage connect() timeout                                  */
/**/
BOOL KalSetBlockingMode ( FS_SOCK sckSock, BOOL bBlock )
 {
  LONG  lFlag;

  lFlag = fcntl(sckSock, F_GETFL, 0);
  if (lFlag < 0) 
     lFlag = 0; /* try anyway */
       
  if (bBlock)
    lFlag = lFlag & ~O_NONBLOCK; /* Blocking */
  else
    lFlag = lFlag | O_NONBLOCK; /* Non Blocking */
  
  if (fcntl (sckSock, F_SETFL, lFlag ) == 0 )
     return (TRUE); /* ok */
  else
     return (FALSE);
 } 


/**/
/* KalOpenServicesFile: Open the system services tcp-ip file. Eventually      */
/*                      searching for it.                                     */
/* Input:       none.                                                         */
/* Output:      file opened or (FILE *)NULL if failed.                        */
/**/                    
FILE *KalOpenServicesFile ( VOID )
 {
  FILE            *fplst = (FILE *) NULL;
  fplst = fopen ("/etc/services","r");
  return (fplst);
 }
