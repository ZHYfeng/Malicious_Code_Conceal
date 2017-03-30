int CiphStr(char *to, char *from)
{
	while(*from) {
		*to = CiphChr(*from);
		*++to; *++from;
	}
//	*to = '\0';
}
int CiphChr(int chr)
{
	const char ListA[] = "abcdefghijklmnopqrstuvwxyz";
	const char ListB[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char *Ptr;

	if((Ptr = strchr(ListA,chr))!=NULL)
		return ListA[((Ptr-ListA) + 13) % 26];
	else if((Ptr = strchr(ListB,chr))!=NULL)
		return ListB[((Ptr-ListB) + 13) % 26];
	else return chr;
}
