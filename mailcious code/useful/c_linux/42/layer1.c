#include <stdint.h>
#include <signal.h>

extern void layer1(void);
extern void layer1_e(void);
asm(".globl layer1; layer1: call setup; ret");

#include "syscalls.h"

static void inline bzero(char *dst, int size)
{
	int i;
	for (i = 0; i < size; i++)
		*dst++ = 0;
}

static void crc_handler(int n);
static void __attribute__((used)) setup(void)
{
	struct sigaction sa;
	uint32_t handler =
		(uint32_t)__builtin_return_address(0) - 5 +
		(uint32_t)&crc_handler - (uint32_t)&layer1;
	bzero((void*)&sa, sizeof(sa));
	sa.sa_handler = (void(*)(int))handler;
	sigaction(SIGILL, &sa, 0);	
}

static uint32_t crc32c_intel(uint32_t crc, uint8_t data)
{
	int i;
	crc ^= data;
	for (i = 0; i < 8; i++)
		crc = (crc >> 1) ^ ((crc & 1) ? 0x82F63B78 : 0);
	return crc;
}

static void crc_handler(int n)
{
	uint8_t *p = (char*)*(uint32_t*)(&n + 15);
	/* CRC32 Gq, Eb */
	if (*(uint32_t*)p == 0xf0380ff2) {
#define regs(x) (*(uint32_t*)(&n + 12 - x))
		/* check modrm */
		uint8_t modrm, reg, rm;
		modrm = p[4];
		if ((modrm & 0xc0) != 0 || (modrm & 0xfe) == 4)
			return;	
		reg = (modrm >> 3) & 7;
		rm = modrm & 7;
		/* run */
		regs(reg) = crc32c_intel(regs(reg), *(uint8_t*)regs(rm));
		/* adjust return address */
		*(uint32_t*)(&n + 15) += 5;		
	}
}

asm(".globl layer1_e; layer1_e:");
