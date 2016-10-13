/*****************************************************************************/
/* Fastspy                                                                   */
/* Author(s): Neural Revenge; [...]                                          */
/* Last Modification: 25/08/1999                                             */
/* Release: see VERSION costant                                              */
/* Links: [...]                                                              */
/* Thanks To: [...]                                                          */
/*****************************************************************************/
/* An Informative TCP port scanner and logger with an attitude ;)            */
/*                                                                           */
/* Main Features:                                                            */
/*             * Scanning single or multiple addresses looking for multiple  */
/*               or single port                                              */
/*             * Input address(es) by asterisks mask (with proper option)    */
/*             * Input addresses from a file (one per line, IPs or names)    */
/*             * Input file with raw data to be sent when a connection to a  */
/*               service occured and log answer                              */
/*             * Report file & stdout together                               */
/*             * System services search (fast scan) on a specific address    */
/*             * Port Triggered search in a subnet address space             */
/*             * Ports Range Scan supported                                  */
/*             * Timing and Delay Controls                                   */
/*             * Easy options for script interfaces                          */
/* ToDo:                                                                     */
/*             * One word: abstraction!                                      */
/*             * Better open architecture (see wishlist)                     */
/*             * Better options parsing (that is terrible!)                  */
/*             * Perhaps a host name subnet search with /num like nmap       */
/*             * redefine -s option with an optional file argument           */
/*             * Autoconf for unix like systems                              */
/*             * cvs development system (sourceforge should be ok)           */
/*             * I would like to know how to create the man page :)          */
/*             * Coloured output for xterm and console stdout                */
/* WhishList:                                                                */
/*             * Simple client modules: Autorecognizes the service found (by */
/*               its port) and acts like a simple client to retrieve some    */
/*               sensitive information.  Es: Ident Query request or SMB      */
/*               share list, whatever...                                     */
/*               This should be enable with verbosity level and not raw input*/
/*               option selected                                             */
/*               The user select a level of verbosity (1;4)                  */
/*               and the compliant modules will try to get more info in depth*/
/*               It has to be done with a syncronization method between main */
/*               connections thread and the module callbacks. This is funny  */
/*               and usefull feauture in my opinion. :)                      */
/*****************************************************************************/
/* Notes for portability:                                                    */
/*****************************************************************************/
/* The code here must be portable. Only ANSI C routines and Berkley socket   */
/* should be used as the main abstraction layer across operating systems     */
/* Actualy only two major "architecture" types are supported: unix and win32.*/
/* All flavour of unix with Posix 1003.1c compliant call should be ok even if*/
/* some implementations lack features on named semaphore or wait timeout     */ 
/* KAL is the Kernel Abstraction Layer. It's a library of exported function  */
/* that supplies the main operating system functionality where ANSI C funct. */
/* do not. Es: mutex, thread, tick counter, timers, etc...                   */
/* These routines should be as simple as possible and do the right thing :)  */
/* Many costants for error code management must be remapped into their host  */
/* specific equivalents.  This should be done into fsconst.h file.           */
/* Some structures and types definitions must be defined into fstypes.h      */
/* System include files must be declared into fsincludes.h                   */
/* Finally every porting must include the proper subdir with the mentioned   */
/* files at compile time so there must not be any relative dir include into  */
/* the sources. See Makefiles or project settings.                           */     /*****************************************************************************/
/* Main Changes Log & Bug Tracking History:                                  */
/*             * Duplicated results sometimes appear in win version.         */
/*               To be investigated [FIXME] (Neural)                         */
/* 17-08-2000  * Made some changes into the gnu makefile, now should be ok   */
/* 17-08-2000  * Removed the 'press a key' thread (ctrl-c will only work)    */
/* 18-08-2000  * First runnable porting on unix platform. Simple Posix KAL   */
/*               has been done. Now it's time to make things work properly   */
/* [... to be edited]                                                        */
/*****************************************************************************/
/* O.S. Abstraction Layer Includes files:                                    */
#include "fsincludes.h"                       /* Custom system includes      */
#include "fstypes.h"                          /* Custom Types Definitions    */
#include "fsconst.h"                          /* Custom Const Definitions    */
                    
#include "fskal.h"                            /* K.A.L. Unique Definitions   */

#include "fastspy.h"                                          
#include "fsutils.h"                          /* aux routines                */


/**/
/* Local Constant Defintions                                                 */
/**/
#define VERSION        "2.2.1 [25/08/1999]"

#define AUT            "NeuraL RevengE"

#define ASTRO          -1 
#define ISASTRO(a)     (a == ASTRO)

#define DEFAULT_FROM   1
#define DEFAULT_TO     500
#define DEFAULT_RANGE  500
#define DEFAULT_DELAY  20

#define DEFAULT_SECOND_TIMEOUT  5

#define WARNINGTHWINDIM         500           /* Warning threshold of threads*/

/**/
/* Global Variables                                                          */
/**/

USHORT FromPort   = 0;
USHORT ToPort     = 0;
USHORT TargetPort = 0;
USHORT Verbose    = 0;
USHORT SubGroup   = 0;
USHORT Resolve    = 0;
USHORT PortSearch = 0;
ULONG  Counter    = 0;
USHORT InputFromFile = 0;
UCHAR  InputFileName[128];
USHORT OutputToFile = 0;
UCHAR  OutputFileName[128];
USHORT AddressFromFile = 0;
UCHAR  AddressFileName[128];
USHORT RepeatDelay= DEFAULT_DELAY;
ULONG  ConnectionTimeout = DEFAULT_SECOND_TIMEOUT;
ULONG  msecConnectionTout= DEFAULT_SECOND_TIMEOUT * 1000;
UCHAR  *pData;
LONG   lLen;
FILE   *fpIn = NULL;
FILE   *fpAddrIn = NULL;
USHORT nNumberOfHits;


UCHAR              dest[4];
CHAR               sdest[4][20];

INT                argcind = 1;

FS_SEMHANDLE       SemParam;
FS_SEMHANDLE       SemCounter;
BOOL               bStop = FALSE;

INT                TaskCounter = 0;

typedef struct Pack
{
   USHORT      Port;
   SOCKADDR_IN sConSin;
} PACK;

/**/
/* Local prototypes                                                          */
/**/
VOID      SocketConnection  ( struct Pack * ) ;


/**/
/* Signals handler routine */
/**/
void Prefinish (int sig)
{
    /* Key hit, enable soft exit */
    if ( (sig == SIGINT) && (!bStop) )
    {
	Printf ("\nGracefully Exit...\n");
    }
    else
    {
	Printf ("Don't panic. Forcing exit.\n"); 
	// exit(0); for linux thread see below
        KalTerminateTask ((FS_TASKHANDLE) NULL);
	printf ("OK PANIC!\n"); /* ;-PPP */
    }

    bStop = TRUE;
    signal (SIGINT, SIG_DFL); 
    signal (SIGABRT, SIG_DFL); 
}

/* Trying to reach the destination */
VOID TryIPAddress (b1, b2, b3, b4)
{
    struct Pack     ParamPack;

    /* Preparing thread parameters */
    ParamPack.sConSin.sin_family = AF_INET;
    ParamPack.sConSin.sin_addr.s_addr = htonl(MAKESINADDR(b1, b2, b3 ,b4));
    ParamPack.sConSin.sin_port = htons (TargetPort);

    if ( KalCreateTask (SocketConnection, (VOID *) &ParamPack) == 
	    (FS_TASKHANDLE) NULL )
	return; /* Try later <grin> */


    /* Waits the task to retrieve the parameters                             */
    KalReceiveUnit (SemParam, WAIT_FOREVER);
    KalSleep (RepeatDelay);
}


/**/
/* Recursive function : checks all possible address of the user mask         */
/* Params: b1 (byte 1), b2 (byte 2), b3 (byte 3), b4 (byte 4) (b1.b2.b3.b4)  */
/**/
VOID CheckAddress(SHORT b1, SHORT b2, SHORT b3, SHORT b4)
{
    SHORT j;

    if (bStop)
	return; /* No more threads to launch */

    if (ISASTRO(b1))
    {
	for (j=0; j<256; j++)
	    CheckAddress(j, b2, b3, b4);
	return; 
    }

    if (ISASTRO(b2))
    {
	for (j=0; j<256; j++)
	    CheckAddress(b1, j, b3, b4);
	return;
    }

    if (ISASTRO(b3))
    {
	for (j=0; j<256; j++)
	    CheckAddress(b1, b2, j, b4);
	return;
    }

    if (ISASTRO(b4))
    {
	for (j=0; j<256; j++)
	    CheckAddress(b1, b2, b3, j);
	return;
    }

    if (bStop)
	return; /* No more thread to launch */

    if (!(b1 == ASTRO || b2 == ASTRO || b3 == ASTRO || b4 == ASTRO))
	/* Here all of bytes are some valid combination:  */
	/* trying to connect to this address */
	TryIPAddress (b1, b2, b3, b4);

}




VOID print_usage( char *name )
 {
   printf ("\nA Parallel Port Spying Utility with stub to log connection and response\n");
   printf ("\nChecks active TCP ports running on the target"); 
   printf ("\nIt could also perform a sub-net, or a address list searching, to find out");
   printf ("\na specific active port in a range of an address space.");
   printf ("\nUsage: %s ", name);
   printf ("\n          [-v][-s][-d <delay>] [-w <timeout>] [-f from_port -t to_port]");
   printf ("\n          [-l <addr_list_file>] [-p <target_port> | <service name>] [-r]");
   printf ("\n          [-i <input_data_file>] [-o <output_txt_file>]");  
   printf ("\n          [<host_name> | <ip_address>] ");
   printf ("\n        -v           Verbose On (Useful to test delay settings)");
   printf ("\n        -d           Connection Rate Delay (%d msec by default)", RepeatDelay);
   printf ("\n        -w           Maximum number of SECONDS to wait for each connection");
   printf ("\n                     (%ld by default),  DO NOT SET this value too high", ConnectionTimeout);
   printf ("\n        -s           Searching in the registered group of ports");
   printf ("\n                      stored into system services file");
   printf ("\n                      This choice override [-f -t] options");
   printf ("\n        -f           Starting port of scanning range");
   printf ("\n        -t           Ending port of scanning range");
   printf ("\n        -p           Specific Port Searching ");
   printf ("\n                      Destination MUST be a dotted IP address");
   printf ("\n                      In this case jolly character '*'");
   printf ("\n                      is supported (es: 194.10.*.*)");
   printf ("\n                      This option override [-f -t] and [-s] options");
   printf ("\n        -r            Try to resolve the numeric address found with -p option");           
   printf ("\n        -i           Input data from a file (when connect occures it sends ");
   printf ("\n                       the data to the host and receives the answer)");
   printf ("\n        -l           Input addresses List file. The file contains one address");
   printf ("\n                       per line and tells fastspy to looking for an active ");
   printf ("\n                       port for each host listed. Use it in combination with");
   printf ("\n                       [-p] option, This choice override [-f -t][-s] options");
   printf ("\n        -o           Output logged to a text file (stdout will work anyhow)");
   printf ("\n        <host_name>  Verbose target name");
   printf ("\n        <ip_address> Dotted IP target address");
   printf ("\n");
   printf ("\n... but remember, \"curiosity killed the cat\"! ;>\n");
   exit (1);
 }

	

/**/
/* Utility to get option of the command line, from some source file out there*/
/**/
int mygetopt (int argc, char *argv[], char *optstr, char *optarg)
{
    int i;
    int k;

    argc--;
    i = argcind;
    while (i <= argc)
    {
	if (argv[i][0] == '-')
	{
	    k = 0;
	    while (optstr[k] != '\0')
	    {
		if (optstr[k] != ':')
		    if (optstr[k] == argv[i][1]) 
		    {
			if ( (argv[i+1] != NULL)&&
				(argv[i+1][0] != '-') )
			{
			    strcpy(optarg, argv[i+1]);
			    argcind = i+2;
			}
			else
			    argcind = i+1;
			return ((int)argv[i][1]);
		    }
		k++;
	    }
	    return ( 0 ); /* no option find */
	}
	i++;
    }

    argcind = i-1;
    if ( i > argc) 
       return ( -1 );

    return (0); /* added to satisfy compiler warning */ 
}

/* Function to retrieve the user parameters */
VOID get_options (int argc, char *argv[])
{
    char optarg[40];
    int    c, i;
    struct hostent *phe;
    struct servent *psService;

    while (( c = mygetopt (argc, argv, "v:p:r:s:f:t:d:w:i:o:l", optarg)) > 0) 
    {
	switch (c) 
	{
	    case 'v':
		Verbose = TRUE;
		break;
	    case 'd':
		RepeatDelay = atoi(optarg);
		break;
	    case 'i':
		InputFromFile = TRUE;
		strcpy(InputFileName, optarg);
		break;
	    case 'o':
		OutputToFile = TRUE;
		strcpy(OutputFileName, optarg);
		break;
	    case 'l':
		AddressFromFile = TRUE;
		strcpy(AddressFileName, optarg);
		break;
	    case 'w':
		ConnectionTimeout = atoi(optarg);
		break;
	    case 'p':
		PortSearch = TRUE;
		if ((psService = getservbyname (optarg,NULL)) == NULL)
		{
		    /* Could already be a port number */
		    TargetPort = atoi (optarg);
		    if (!TargetPort)
		    { 
			printf ("ERROR - Target Port/Service is not valid: %s\n", 
				optarg);
			exit (0);
		    }
		}
		else
		    /* Service found */
		    TargetPort = ntohs(psService->s_port);
		break;
	    case 'r':
		Resolve = TRUE;
		break;
	    case 's':
		SubGroup = TRUE;
		break;
	    case 'f' :
		FromPort = atoi (optarg);
		ToPort   = FromPort + DEFAULT_RANGE;
		break;
	    case 't' :
		ToPort = atoi (optarg);
		if (!FromPort)
		    print_usage(argv[0]);
		break;
	    default : 
		print_usage (argv[0]);
	}
    }

    if (InputFromFile)
    {
	if ((fpIn = fopen (InputFileName, "rb")) == (FILE *)NULL)
	{
	    printf ("ERROR: Cannot open %s\n",InputFileName);
	    exit (1);
	}
	fseek (fpIn, 0, SEEK_END);
	lLen  = ftell(fpIn);
	fseek (fpIn, 0, SEEK_SET);
	if ( (pData = (char *) malloc (lLen)) == NULL )
	{ 
	    printf ("ERROR: Not enough memory to allocate file data [%ld]\n",
		    lLen);
	    exit (1);
	}
	/* Load data from the file */
	if (fread (pData, 1, lLen, fpIn) == 0)
	{
	    printf ("ERROR: Cannot load data from the file %s\n",
		    InputFileName);
	    exit (1);
	}
    }

    if (AddressFromFile)
    {
	if ((fpAddrIn = fopen (AddressFileName, "r")) == (FILE *)NULL)
	{
	    printf ("ERROR: Cannot open %s\n",AddressFileName);
	    exit (1);
	}
    }

    if (OutputToFile)
    {
	FILE *fpOut;
	/* if the file exist will be reset overwriting it */
	if ((fpOut = fopen (OutputFileName, "w")) == (FILE *)NULL)
	{
	    printf ("ERROR: Cannot open %s to write\n",OutputFileName);
	    exit (1);
	}
	fclose (fpOut);
    }

    if ((PortSearch) && (!AddressFromFile))
    {
	char *pAux;
	int i;

	pAux = argv[argcind];
	for (i=0; i<4; i++)
	{
	    strncpy (sdest[i], pAux, 20);

	    if( (pAux = strchr (sdest[i], '.') ) == NULL)
		break;
	    *pAux = '\0';
	    if ( !IsAddressNumber (sdest[i]) )
	    {
		printf ("ERROR: Destination MUST be a dotted IP address and not %s \n", 
			argv[argcind]);
		exit(0);
	    }
	    pAux++;
	}

	return;
    }

    if (Resolve && !PortSearch)
    {
	printf ("ERROR: If resolving addresses option is enable you must use the port [-p] option\n");
	exit (0);
    }

    if (AddressFromFile && !PortSearch)
    {
	printf ("ERROR: If Address List File is supplied you must specify a port with [-p] option\n");
	exit (0);
    }

    if (AddressFromFile)
	return;

    if (ToPort < FromPort) 
	print_usage (argv[0]);
    
    if ((FromPort == 0) && (ToPort == 0))
    {
	FromPort = DEFAULT_FROM;
	ToPort   = DEFAULT_TO; 
    }
    
    if ( argcind >= argc )  print_usage (argv[0]);

    if (c == 0) 
	print_usage (argv[0]);

    if (isIPJollyAddress(argv[argcind]) && (!PortSearch))
    {
	printf ("ERROR: If a dotted jolly address is supplied (multiple addresses to test) you must specify a single port with [-p] option\n");
	exit (0);
    }

    if (isIPAddress(argv[argcind]))
    {
        /* REMOVED: %u needs unsigned short fileds and not char!  
        sscanf(argv[argcind], "%u.%u.%u.%u", 
	       &dest[0], &dest[1], &dest[2], &dest[3]);  */
        *(unsigned long *)dest = inet_addr (argv[argcind]);
    }
    else
    {
	phe = gethostbyname(argv[argcind]);
	if (phe == NULL) 
	{
	    printf ("Error - You have typed Host Name too fast. Please relax.\n");
	    exit (1);
	}
	for (i=0; i<4; i++) dest[i]= (u_char) phe->h_addr[i];
    }

}

/**/
/* Main Thread launched by scanning procedure                                */
/**/
VOID SocketConnection  (struct Pack *pPack)
{
    INT             Result;
    USHORT          port; 
    FS_SOCK         sckSock; 
    SOCKADDR_IN     sConSinT;
    struct servent  *pse = NULL;
    struct hostent  *phe = NULL;
    char            *strtime;   /* Timestamp             */
    time_t          t;          /* Use to retrieve time  */
    fd_set          writefds;
    fd_set          exceptfds;
    fd_set          readfds;
    BOOL            bConnect  = FALSE;
    BOOL            bReceived = FALSE;
    struct timeval  sSelectTimeout;
    char            Buffer[128];
    char            RecvBuff[1024];
    LONG            recvLen = 0;


    /* Retrieve task parameter                                               */
    port = ntohs (pPack->sConSin.sin_port);
    sConSinT = pPack->sConSin;

    /*Ok, parameter fetched, unblocking the father task                      */
    KalSendUnit (SemParam);
    
    /* Update the global counter of the number of threads launched           */
    KalReceiveUnit (SemCounter, WAIT_FOREVER);
    TaskCounter ++;
    KalSendUnit (SemCounter);

    if ((sckSock = socket (AF_INET, SOCK_STREAM, 0)) == FS_INVALID_SOCKET)
    {
	printf ("Error - Network Access Attempted - System confused.\n");
	KalReceiveUnit (SemCounter, WAIT_FOREVER);
	TaskCounter --;
	KalSendUnit (SemCounter);
	KalTerminateTask((FS_TASKHANDLE) NULL);
    }

    if (Verbose) 
    {
	if (PortSearch)
	    printf (" Trying host %s\n", inet_ntoa(sConSinT.sin_addr));
	else
	    printf (" Trying port no. %d\n",port);
    }

    /* *** Seting NonBlocking operation on the socket *** */
    KalSetBlockingMode (sckSock, FALSE); 
    FD_ZERO (&writefds);
    FD_ZERO (&exceptfds);
    FD_SET  (sckSock, &writefds);
    FD_SET  (sckSock, &exceptfds);

    /* Connecting.... */
    while (connect( sckSock, (struct sockaddr *) &sConSinT, sizeof(sConSinT)) == 
	    FS_SOCKET_ERROR)
    {
	Result = KalGetLastError();
	if ( (Result == FS_ECONNWOULDBLOCK) || (Result == FS_ECONALREADYBLOCK))
	{
            sSelectTimeout.tv_sec = ConnectionTimeout;
            sSelectTimeout.tv_usec = 0;
	    Result = select(sckSock+1, NULL, 
                            &writefds, &exceptfds, &sSelectTimeout);
            if (Result <= 0)
	    {
		/* select timeout or select failure */
		/* Connection Timed out */
		bConnect = FALSE;
		KalCancelBlockingCall(); /* is really usefull? bah */
		break;
	    }
            
	    if (FD_ISSET (sckSock, &writefds))
	    { 

#if 0 /* $$$ */             
                if ( send (sckSock, Buffer, 0, 0) < 0 )
                  bConnect = FALSE; /* writeble but not connected */ 
                else
		  /* Ok Connection established */
	  	  bConnect = TRUE;
		break;
#else
                /* Something happens. Idle time completed. now checking again*/
                /* with the connect to know if we have been connected        */
                /* we assert we are connected (socket writeble)              */
                bConnect = TRUE;
                continue; /* reapeat the same connect */
#endif
	    }
	    if (FD_ISSET (sckSock, &exceptfds))
	    {
		/* Connection Refused */
		bConnect = FALSE;
		break;
	    }
	}
	else
	{
	    if (Result == FS_ENOBUFS)
		Counter++;
            /* Connect fail for a real reason */
            /* if we are under win repeating the connect() lead us to this   */
            /* error:                                                        */
            if (Result == FS_EISCONNECTED)
              bConnect = TRUE; /* the socket is already connected            */
            else
              bConnect = FALSE;
	    break;
	}
    }

    if (bConnect) 
    {
	/*** Set *Blocking* Mode yet */
        KalSetBlockingMode (sckSock, TRUE);

	pse = getservbyport ( htons(port), NULL);
	t=time((time_t *)NULL); 
	strtime=ctime(&t);
	strtime+=11;               /* skip day name */
	strtime[8]='\0';           /* keep HH:MM:SS */

	nNumberOfHits++ ;

	if (PortSearch)
	{
	    /* Preout of the string */
	    /* print into a buffer because of possible following recv()      */
	    /* function                                                      */
	    if (Resolve)
		phe = gethostbyaddr ( (char *) &sConSinT.sin_addr, 4, AF_INET);
	    if (pse)
		sprintf (Buffer," %s  Service %s found at %s [%s]\n", strtime,
		       	 pse->s_name, inet_ntoa(sConSinT.sin_addr), 
			 (phe)?phe->h_name: "unresolved");
	    else
		sprintf (Buffer," %s  Port %d found at %s [%s]\n", strtime, 
			 port, inet_ntoa(sConSinT.sin_addr), 
			 (phe)?phe->h_name: "unresolved" );
	}
	else
	    sprintf (Buffer," %s  Service found at port no. %d  \t Service: %s\n", 
		     strtime, port, ( pse != NULL ) ? pse->s_name : "Unknown");
    }

    if (InputFromFile && bConnect)
    {
	if ( send (sckSock, pData, lLen, 0) == FS_SOCKET_ERROR)
	{
	    printf ("Error sending data through the socket\n");
	}
	else
	{
	    /* waiting some possible answer data */
	    /*** Set NonBlocking Mode */
	    KalSetBlockingMode (sckSock, FALSE);
	    FD_ZERO (&readfds);
	    FD_SET  (sckSock, &readfds);
	    while ( (recvLen = recv (sckSock, RecvBuff, sizeof (RecvBuff), 0))
		    == FS_SOCKET_ERROR)
	    {
		Result = KalGetLastError();
		if ( Result == FS_ERECVWOULDBLOCK)
		{
                    sSelectTimeout.tv_sec = ConnectionTimeout;
                    sSelectTimeout.tv_usec = 0;
		    if (select(sckSock+1, &readfds, 
                               NULL, NULL, &sSelectTimeout) == 0)
		    {
			/* select timeout */
			/* receive timed out */
			bReceived = FALSE;
			KalCancelBlockingCall();
			break;
		    }

		    if (FD_ISSET (sckSock, &readfds))
		    {
			/* Ok Data arrived */
			bReceived = TRUE;
			//recvLen= recv(sckSock, RecvBuff, sizeof (RecvBuff), 0);
			continue; /* go to read data */
		    }

		    KalSleep (500);
		}
		else
                {
                   /* generic blocing error */
                   bReceived = FALSE;
		   break;
                }
	    }
            
          if (recvLen > 0)
           bReceived = TRUE; /* something received, setting flag anyway */  
	}

	KalReceiveUnit (SemCounter, WAIT_FOREVER);
	Printf (Buffer);
	if (bReceived)
	{
	    Printf (" <Data Received>\n");
	    OutWrite (RecvBuff, recvLen);
	    Printf (" <End Data>\n\n");
	}
	else
	    Printf (" - No Data Received: Timeout -\n\n");

	TaskCounter --;
	KalSendUnit (SemCounter);
    }
    else
    {
	KalReceiveUnit (SemCounter, WAIT_FOREVER);
	if (bConnect) 
	    Printf (Buffer);
	TaskCounter --;
	KalSendUnit (SemCounter);
    }

    /*** Set *Blocking* Mode yet */
    KalSetBlockingMode (sckSock, TRUE);
    close ( sckSock );
    KalTerminateTask((FS_TASKHANDLE)NULL);
}

/********/
/* Main */
/********/
int main (int argc, char *argv[])
{
    USHORT          port;
    FILE            *fplst = NULL;
    char            Buff  [150];
    char            String [80];
    struct Pack     ParamPack;
    char            *strtime;   /* Timestamp             */
    char            *year;      /* Timestamp             */
    time_t          t;          /* Use to retrieve time  */
    char            OutputBuffer[160];
    char            cType[160];
    short           i;
    int             nThreadsWinDim;

    sprintf (OutputBuffer, "FastSpy v%s by %s\n", VERSION, AUT);
    Printf (OutputBuffer);

    if (!KalInit()) 
    {
	printf ("Sorry, Initialization Phase goes wrong. Could not start the program\n");
	exit(1);
    }


    /* Catch system interrupt by ctrl-c event */
    signal (SIGINT, Prefinish);
    signal (SIGABRT, Prefinish);

    if (argc < 2)
	print_usage(argv[0]);

    get_options (argc, argv);

    SemCounter = KalCreateSemaphore ("SemCounter"); 
    KalSendUnit (SemCounter);

    SemParam   = KalCreateSemaphore ("SemParam");

    /* Calculating foreseen Load */
    nThreadsWinDim = (int) ((ConnectionTimeout * 1000) / 
	                    ((RepeatDelay >= 4)?RepeatDelay:4)) ;
    if (nThreadsWinDim >= WARNINGTHWINDIM)
    {
	printf ("\n[WARNING] Parallel tasks foreseen Peak: %d\n", nThreadsWinDim);
	printf ("          If this slow down your system hit CTRL-C twice to force exit\n");
	printf ("          and reduce connection wait timout with -w option\n");
    }

    /* Calculating Date for log */
    t=time((time_t *)NULL); 
    strtime=ctime(&t);
    strtime+=4;            /* skip day name */
    strtime[6]='\0';       /* keep HH:MM:SS */
    year = &strtime[16];
    year[4] = '\0';
    sprintf (OutputBuffer,"\nDate: %s %s\n", strtime, year);
    Printf (OutputBuffer);

    nNumberOfHits = 0;

    if (PortSearch)
    {
	SHORT  b1,b2,b3,b4;    /* b1.b2.b3.b4 */
	struct servent *pse;

	pse = getservbyport ( htons(TargetPort), NULL);

	if (!AddressFromFile)
	{
	    sprintf (OutputBuffer,"Looking for port: %d [%s] in %s.%s.%s.%s\n\n", 
		     TargetPort, ( pse != NULL ) ? pse->s_name : "Unknown",
		     sdest[0], sdest[1], sdest[2], sdest[3]);
	    Printf(OutputBuffer);
	    /* Analyzing destination address */
	    if ( !strcmp(sdest[0],"*"))
		b1 = ASTRO;
	    else
		b1 = atoi (sdest[0]);

	    if ( !strcmp(sdest[1],"*") )
		b2 = ASTRO;
	    else
		b2 = atoi (sdest[1]);

	    if ( !strcmp(sdest[2],"*"))
		b3 = ASTRO;
	    else
		b3 = atoi (sdest[2]);

	    if ( !strcmp(sdest[3],"*"))
		b4 = ASTRO;
	    else
		b4 = atoi (sdest[3]);

	    /* Loop for each possible Address */
	    CheckAddress (b1, b2, b3, b4);
	}
	else 
	{
	    sprintf (OutputBuffer,"Looking for port: %d [%s] from the Address List File\n\n", 
		     TargetPort, ( pse != NULL ) ? pse->s_name : "Unknown");
	    Printf(OutputBuffer);

	    ParamPack.sConSin.sin_family = AF_INET;
            ParamPack.sConSin.sin_port   = htons (TargetPort);

	    while ((fgets (Buff, sizeof(Buff), fpAddrIn) != NULL) && (!bStop))
	    {
		if ((Buff[0] == '#') || (Buff[0] == ';'))
		    continue; /* skip possible comment */

		if ((Buff[0] == '\r') || (Buff[0] == '\n'))
		    continue; /* skip empty line */

		sscanf (Buff, "%s\n", Buff);

		if (isIPAddress(Buff))
                 {
                   /* REMOVED %u is not valid 
		    sscanf(Buff,"%u.%u.%u.%u", 
                           	   &dest[0], &dest[1], &dest[2], &dest[3]); */
                   *(unsigned long *)dest = inet_addr (Buff);
                    
                 }
		else
		{
		    struct hostent *phe;
		    phe = gethostbyname(Buff);
		    if (phe == NULL) 
		    {
			if (Verbose)
			{
			    char String[160];
			    sprintf (String, "SKIP - due to unresolving: %s\n",
				     Buff);
			    Printf(String);
			}
			continue;
		    }

		    for (i=0; i<4; i++) dest[i]= (u_char) phe->h_addr[i];
		}

		memcpy((char *)&(ParamPack.sConSin.sin_addr), dest, 4);

		if (KalCreateTask (SocketConnection, (VOID *) &ParamPack) == 
			(FS_TASKHANDLE) NULL)
		{
		    printf("Insufficient resources to allocate more threads, ignoring...\n");
		    continue;
		}

		/* Waits the task to retrieve the parameter                  */  
		KalReceiveUnit (SemParam, WAIT_FOREVER);
		KalSleep (RepeatDelay);
	    } /* end while on addr file                                      */
	} /* end else on PortSearch and AddressFromFile                      */
    } /* end if on PortSearch                                                */
    else
    {
	/* Target is Not a group of addresses but is a specific one          */
	ParamPack.sConSin.sin_family = AF_INET;

	memcpy((char *)&(ParamPack.sConSin.sin_addr), dest, 4);
	sprintf (OutputBuffer, "Target address: %u.%u.%u.%u\n", 
		dest[0], dest[1], dest[2], dest[3]);
	Printf (OutputBuffer);

	if (!SubGroup)
	{
	    sprintf (OutputBuffer, "\nScanning port %d to %d in progress...\n\n",
		    FromPort, ToPort);
	    Printf (OutputBuffer);

	    port = FromPort;
	    while ((port < ToPort) && (!bStop))
	    {
		ParamPack.sConSin.sin_port = htons (port);
		if (KalCreateTask (SocketConnection, (VOID *) &ParamPack) == 
			(FS_TASKHANDLE) NULL)
		{
		    printf("Insufficient resources to allocate more threads, ignoring...\n");
		    port++;
		    continue;
		}

		/* Waits the task to retrieve the parameters                 */
		KalReceiveUnit (SemParam, WAIT_FOREVER);
		KalSleep (RepeatDelay);
		port++ ;
	    }
	} /* end if */
	else
	{
	    /* Searches in sub-group of all port (known service)             */
	    sprintf (OutputBuffer, "\nScanning all known services ports in progress...\n\n");
	    Printf (OutputBuffer);
            fplst = KalOpenServicesFile ();

	    if (fplst == (FILE *) NULL)
	    {
		printf ("User error - Not my fault. Is Not! Is Not!\n");
		printf ("Unable to find out or open the system services file\n");
		exit (1);
	    }

	    while ((fgets (Buff, sizeof(Buff), fplst) != NULL) && (!bStop))
	    {
		if (sscanf(Buff,"%s %hu/%s", String, &port, cType) != 3)
		    continue;

		if (stricmp(cType, "tcp") != 0)
		    continue;

		ParamPack.sConSin.sin_port = htons (port);

		if (KalCreateTask (SocketConnection, (VOID *) &ParamPack) == 
			(FS_TASKHANDLE) NULL)
		{ 
		    printf("Insufficient resources to allocate more threads, ignoring...\n");      
		    continue;
		}

		/* Waits the task to retrieve the parameter                  */
		KalReceiveUnit (SemParam, WAIT_FOREVER);
		KalSleep (RepeatDelay);
	    }
	    fclose (fplst);
	}
    }

    if (Verbose) 
	printf ("Waiting tasks end...\n");

    while (TRUE)                                             
    {
	KalReceiveUnit (SemCounter, WAIT_FOREVER);
	/* To be or not to be ?? */
	if (TaskCounter <= 0)
	{
	    KalSendUnit (SemCounter);
	    /* Not to be           */
	    break;
	}
	if (Verbose) printf(" %d Tasks Remaining.\n", TaskCounter);
	KalSendUnit (SemCounter);
	KalSleep (600);
    }
    sprintf (OutputBuffer,"\n%d occurence(s) have been found.\n", 
	     nNumberOfHits);
    Printf (OutputBuffer);
    Printf ("Scanning complete, Bye.\n\n");
    sprintf (OutputBuffer,"Reporting %ld Network Error.\n", Counter);
    Printf (OutputBuffer);

    KalKillSemaphore (SemCounter);
    KalKillSemaphore (SemParam);

    KalClose ();

    if (InputFromFile)
    {
	free(pData);
	fclose (fpIn);
    }
    if (AddressFromFile)
	fclose (fpAddrIn); 

    return (1);
}

