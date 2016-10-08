void putc(char c)
{
	write(1, &c, 1);
}

void putx1(uint8_t x)
{
	putc(x > 9 ? x - 10 + 'a' : x + '0');
}

void putx2(uint8_t x)
{
	putx1(x >> 4);
	putx1(x & 15);
}
void puts(char *s)
{
	while (*s)
		putc(*s++);
	putc(10);
}
void putx4(uint32_t x)
{
	int i;
	for (i = 28; i >= 0; i -= 4)
		putx1((x >> i) & 15);
}
