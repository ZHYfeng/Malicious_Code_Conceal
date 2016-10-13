#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <windows.h>
int main(int argc, char *argv[])
{
	int ch, slide = 0;
	FILE *file1 = fopen(argv[1],"rb"), *file2 = fopen("_d__.meta","wb");
	while((ch = fgetc(file1))!=EOF) fputc((unsigned char)ch+(++slide),file2);
	fclose(file1); fclose(file2);
	DeleteFile(argv[1]);
	MoveFile("_d__.meta",argv[1]);
	return 0;
}
