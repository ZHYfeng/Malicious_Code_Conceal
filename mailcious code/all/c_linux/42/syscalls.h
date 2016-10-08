/* Syscalls */
asm(	"_syscall:\n"
	"	pusha\n"
	"	mov	36(%esp),%eax\n"
	"	mov	40(%esp),%ebx\n"
	"	mov	44(%esp),%ecx\n"
	"	mov	48(%esp),%edx\n"
	"	mov	52(%esp),%esi\n"
	"	mov	56(%esp),%edi\n"
	"	mov	60(%esp),%ebp\n"
	"	int	$0x80\n"
	"	mov	%eax,28(%esp)\n"
	"	popa\n"
	"	ret\n");
extern unsigned int _syscall();
#define exit(a)			_syscall(1,  a)
#define read(a,b,c)		_syscall(3,  a,b,c)
#define	write(a,b,c)		_syscall(4,  a,b,c)
#define open(a,b)		_syscall(5,  a,b)
#define	close(a)		_syscall(6,  a)
#define	creat(a,b)		_syscall(8,  a,b)
#define	chdir(a)		_syscall(12, a)
#define time(a)			_syscall(13, a)
#define lseek(a,b,c)		_syscall(19, a,b,c)
#define	getpid()		_syscall(20)
#define	access(a,b)		_syscall(33, a,b)
#define	rename(a,b)		_syscall(38, a,b)
#define	brk(a)			_syscall(45, a)
#define	signal(a,b)		_syscall(48, a,b)
#define	sigaction(a,b,c)	_syscall(67, a,b,c)
#define readdir(a,b)		_syscall(89, a,b)
#define munmap(a,b)		_syscall(91, a,b)
#define	ftruncate(a,b)		_syscall(93, a,b)
#define	lstat(a,b)		_syscall(107,a,b)
#define	mprotect(a,b,c)		_syscall(125,a,b,c)
#define	mremap(a,b,c,d)		_syscall(163,a,b,c,d)
#define pwrite(a,b,c,d,e)	_syscall(181,a,b,c,d,e)
#define mmap(a,b,c,d,e,f)	_syscall(192,a,b,c,d,e,f)

#define	R_OK	4		/* Test for read permission.  */
#define	W_OK	2		/* Test for write permission.  */
#define	X_OK	1		/* Test for execute permission.  */
#define	F_OK	0		/* Test for existence.  */
