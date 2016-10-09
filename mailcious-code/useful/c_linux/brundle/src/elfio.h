/*
 * Brundle Fly - Good-natured Linux ELF virus supporting kernel 2.2 and 2.4
 * Copyright 2001 Konrad Rieck <kr@roqe.org>, Konrad Kretschmer <kk@roqe.org>
 * In memory to Seth Brundle 
 *
 * $Id: elfio.h,v 1.4 2001/07/11 18:34:48 kr Exp $
 */

/*
 * These weird definition are intented for future use. Maybe some day, 
 * Brundle Fly will also work on 64-Bit ELF systems. 
 */
#ifndef ELF_64BIT
#define Elf_Ehdr Elf32_Ehdr
#define Elf_Shdr Elf32_Shdr
#define Elf_Phdr Elf32_Phdr
#else
#define Elf_Ehdr Elf64_Ehdr
#define Elf_Shdr Elf64_Shdr
#define Elf_Phdr Elf64_Phdr
#endif

#if defined(HAVE_ELF_H)
#include <elf.h>
#elif defined(HAVE_SYS_ELF_H)
#include <sys/elf.h>
#elif defined(HAVE_SYS_EXEC_ELF_H)
#include <sys/exec_elf.h>
#else
#error Your system is missing an Elf header
#endif

void print_ehdr(Elf_Ehdr * e);
void print_shdr(Elf_Shdr * s);
void print_phdr(Elf_Phdr * p);
Elf_Ehdr *read_ehdr(int fd);
Elf_Shdr *read_shdrs(int fd, Elf_Ehdr * e);
Elf_Phdr *read_phdrs(int fd, Elf_Ehdr * e);
int check_host(Elf_Ehdr * e);
