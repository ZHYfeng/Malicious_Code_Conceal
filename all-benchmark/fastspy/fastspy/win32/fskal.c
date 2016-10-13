/**/
/* Kernel Abstraction Layer: Per system implementation of syscalls           */  
/* KAL for Win32                                                             */ 
/**/
#include "fsincludes.h" 
#include "fstypes.h"

#include "fskal.h"
#include "fsutils.h"

#define close(s) closesocket(s)

/**/
/* KalInit: Functions for intialization of libraries goes here               */
/* Input:   none.                                                            */
/* Output:  Boolean value: TRUE ok; FALSE not                                */
/**/           
BOOL KalInit ( VOID )
 {
   WSADATA         wsaData;

   if (WSAStartup (MAKEWORD (1,1), &wsaData) != 0) 
    {
     printf ("\nIllegal error - You are not allowed to get this error. Next time you will get a penalty for that!\n"); 
     printf ("You'd better check your winsock library.\n");
     return (FALSE);
    }

  return (TRUE);
 }

/**/
/* KalClose: Functions for DEintialization of libraries goes here            */
/* Input:   none.                                                            */
/* Output:  Boolean value: TRUE ok; FALSE not                                */
/**/           
BOOL KalClose ( VOID )
 {
   WSACleanup ();
   return (TRUE);
 }


/**/
/* KalCreateSemaphore: creates a semaphore                                   */
/* Input:              PCHAR; Semaphore Name                                 */
/* Output:             FS_SEMHANDLE; Sem Handle: NULL if fails               */
/**/           
FS_SEMHANDLE KalCreateSemaphore( PCHAR SemaphoreName )
 {

  FS_SEMHANDLE     shReturnValue;
  ULONG         dwErrCode;

  shReturnValue = CreateSemaphore(
                                  NULL,         /* Security attributes.      */
                                  0,            /* Initial count             */
                                  0xFFFF,       /* Maximum count             */
                                  SemaphoreName /* Semaphore name.           */
                                 );
  if ( shReturnValue == NULL ) 
   {
    Printf ("Horrible bug encountered - Only God knows what has happened.\n");
    dwErrCode = GetLastError();
   }
  return( shReturnValue );
 }


/**/
/* KalReceiveUnit: waits a unit from the semaphore                           */
/* Input:          FS_SEMHANDLE; Sem Handle                                  */
/*                 LONG; Timeout to wait in millisec or WAIT_FOREVER         */  
/* Output:         USHORT Code: SEM_TIMEOUT; SEM_OK; SEM_FAIL                */
/**/
USHORT KalReceiveUnit( FS_SEMHANDLE shSemHandle, LONG lTimeOut )
 {

  LONG  lMilliseconds = lTimeOut;

  if ( lTimeOut == WAIT_FOREVER ) lMilliseconds = INFINITE;

  if ( WaitForSingleObject( shSemHandle, lMilliseconds ) == WAIT_TIMEOUT )
   return( SEM_TIMEOUT );

  return( SEM_OK );
 }

/**/
/* KalSendUnit: Send a unit to the semaphore                                  */
/* Input:       FS_SEMHANDLE; Semaphore Handler                               */
/* Output:      USHORT Code: SEM_OK; SEM_FAIL                                 */
/**/
USHORT KalSendUnit( FS_SEMHANDLE shSemHandle )
 {
  ReleaseSemaphore(
                   shSemHandle,
                   1,                   /* Value to be added.                 */
                   NULL                 /* Previous value not needed.         */
                  );
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
   FS_TASKHANDLE hThread;
   if ( (hThread = _beginthread (TaskEntryPoint, 0 , pParam)) <= 0)
    {
     printf("Error - Multitasking Attempted - System confused.\n");
     return ((FS_TASKHANDLE) NULL);
    }
   return (hThread);
 }

/**/
/* KalTerminateTask: Terminate a task                                         */
/* Input:      FS_TASKHANDLE *; NULL for current thread                       */ 
/* Output:     Boolean value: TRUE ok; FALSE not                              */
/**/
BOOL KalTerminateTask ( FS_TASKHANDLE  pNull )
 {
  _endthread();
  return (TRUE);
 }

/**/
/* KalGetLastError: Gets the last error occured in the network libray         */
/* Input:         none;                                                       */
/* Output:        The error that should be remapped in defconst.h             */
/**/
INT KalGetLastError ( VOID )
 {
  return (WSAGetLastError ());
 }

/**/
/* KALCancelBlockingCall: Cancels a pendent blocking call                     */
/* Input:         none;                                                       */
/* Output:        The error that should be remapped in defconst.h             */
/**/
INT KalCancelBlockingCall( VOID )
 {
  return (WSACancelBlockingCall ());
 }

/**/
/* KALSleep: Sleep for a specified time in milliseconds                       */
/* Input:    LONG; Time in millisecods                                        */
/* Output:   none                                                             */
/* Note:     Better if used a realtime sleep                                  */
/**/
VOID KalSleep( LONG lTime )
 {
  Sleep (lTime); /* 3/4 milliseconds precision */
 }

/**/
/* KalGetTimerValue: Returns back the tick counter of the system in millisec. */
/* Input:   none                                                              */
/* Output:  LONG; The timer value expressed in millisecond                    */
/* Note:    Used to compute the time difference for diagnostic and timing     */
/**/
LONG KalGetTimerValue ( VOID )
 {
  return (GetTickCount());
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
      
  ULONG  ulFlag;

  if (bBlock)
    ulFlag = 0; /* Blocking */
  else
    ulFlag = 1; /* Non Blocking */
  
  if (ioctlsocket (sckSock, FIONBIO, &ulFlag ) == 0 )
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
    char            cSystemPath[160];
    BOOL            bExitLoop;
    char            *PathVar;
    char            Path[80];
    char            *App;
    char            Buff  [150];
    FILE            *fplst = (FILE *) NULL;
             
	    GetEnvironmentVariable("SystemRoot", cSystemPath, sizeof (cSystemPath));

	    bExitLoop = FALSE;
	    if (HIWORD(GetVersion()) & 0x8000)
	    {
		/*  Windows 3.1 / 95 / 98(?) */
		strcat (cSystemPath, "\\Services");
		if ( (fplst = fopen (cSystemPath,"r")) == (FILE *)NULL)       
		{
		    if ((PathVar = getenv ("PATH"))  != NULL)
			do
                         {
			    if ( (App = strstr (PathVar,";")) == NULL)  
			    {
				App = PathVar + strlen(PathVar); 
				bExitLoop = TRUE; 
			    }
			    memcpy(Buff, PathVar, (size_t)(App - PathVar));
			    Buff[App - PathVar] = '\0';
			    PathVar = App + 1;
			    sprintf(Path,"%s\\Services", Buff);
			 } 
			while ( ((fplst = fopen (Path,"r")) == (FILE *)NULL) && (bExitLoop != TRUE));
		}
	    }
	    else
	    {
		/* Windows NT 3.5x/4.x/5.x(?) */
		strcat (cSystemPath, "\\System32\\DRIVERS\\ETC\\Services");
		if ( (fplst = fopen (cSystemPath,"r")) == (FILE *)NULL)       
		{
		    if ((PathVar = getenv ("PATH"))  != NULL)
			do{
			    if ( (App = strstr (PathVar,";")) == NULL)  
			    {
				App = PathVar + strlen(PathVar); 
				bExitLoop = TRUE; 
			    }
			    memcpy(Buff, PathVar, (size_t)(App - PathVar));
			    Buff[App - PathVar] = '\0';
			    PathVar = App + 1;
			    sprintf(Path,"%s\\Services", Buff);
			} 
			while ( ((fplst = fopen (Path,"r")) == (FILE *)NULL) && (bExitLoop != TRUE));
		}
	    }
            
   return (fplst);            

 }
