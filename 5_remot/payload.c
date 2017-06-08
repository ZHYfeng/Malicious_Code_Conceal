#include <windows.h>
#include <stdio.h>
int main()
{
	int i;
	while (1)
	{	
		i = 100000;
		while(i){
			i--;
		}
		Sleep(1);
	}
	return 0;
}
