typedef struct {
	Elf32_Sym *dynsym;
	char *dynstr;
	int nsyms;
} libc_t;

/* there is no return value checks here, the whole thing is protected by signal */
static void find_libc(libc_t *libc)
{
	void *get_base(uint32_t addr) {
		addr &= ~4095;
		while (*(uint32_t*)addr != 0x464c457fUL)
			addr -= 4096;
		return (void*)addr;
	}
	void get_dyn_file_base(uint8_t *elf, Elf32_Dyn **dynamic, uint32_t *delta) {
		int i;
		Elf32_Phdr *phdr;
		uint32_t dyn = 0, low = 0xffffffff;
		phdr = (Elf32_Phdr*)(elf + ((Elf32_Ehdr*)elf)->e_phoff);
		for (i = 0; i < ((Elf32_Ehdr*)elf)->e_phnum; i++) {
			if (phdr[i].p_type == PT_LOAD && low > phdr[i].p_vaddr)
				low = phdr[i].p_vaddr;
			if (phdr[i].p_type == PT_DYNAMIC)
				dyn = phdr[i].p_vaddr;
		}
		*delta = (uint32_t)elf - low;
		*dynamic = (Elf32_Dyn*)(dyn + *delta);
	}
	void *get_from_dyn(Elf32_Dyn *dynamic, uint32_t tag) {
		Elf32_Dyn *dyn;
		for (dyn = dynamic; dyn->d_tag != DT_NULL; ++dyn)
			if (dyn->d_tag == tag)
				return (uint32_t*)dyn->d_un.d_ptr;
		return NULL;
	}
	void unwind(uint32_t addr, uint32_t **got, Elf32_Dyn **dyn, uint32_t *delta) {
		get_dyn_file_base(get_base(addr), dyn, delta);
		*got = get_from_dyn(*dyn, DT_PLTGOT);
	}
	uint32_t *got, delta;
	Elf32_Dyn *dyn;

	unwind((uint32_t)&__text_start, &got, &dyn, &delta);
	if (got[2])
		unwind(got[2], &got, &dyn, &delta);
	unwind(got[4], &got, &dyn, &delta);

	/* get symbol and string table */	
	libc->dynsym = (Elf32_Sym*)get_from_dyn(dyn, DT_SYMTAB);
	libc->dynstr = get_from_dyn(dyn, DT_STRTAB);
	
	/* get the number of symbols */
	uint32_t *hash;
	if ((hash = get_from_dyn(dyn, DT_HASH)) || (hash = get_from_dyn(dyn, DT_GNU_HASH)))
		libc->nsyms = hash[1];
	else
	/* don't blame me for this! the system loader is doing the same. vote for DT_SYMCOUNT! :-) */
		libc->nsyms = ((uint32_t)libc->dynstr - (uint32_t)libc->dynsym) / sizeof(Elf32_Sym);
}

static uint32_t resolve(libc_t *libc, char *name)
{
	/* one cannot use the library functions within the resolver */
	int strcmp (const char * s1, const char * s2) {
		for(; *s1 == *s2; ++s1, ++s2)
			if(*s1 == 0)
				return 0;
		return *(unsigned char *)s1 < *(unsigned char *)s2 ? -1 : 1;
	}
	int i;
	for (i = 0; i < libc->nsyms; i++)
		if (! strcmp(libc->dynsym[i].st_name + libc->dynstr, name))
			return libc->dynsym[i].st_value;
	return 0;
}
