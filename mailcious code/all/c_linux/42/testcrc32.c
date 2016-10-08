#include <stdint.h>
#include <assert.h>

static uint32_t crc32c_intel(uint32_t crc, uint8_t data)
{
	int i;
	crc ^= data;
	for (i = 0; i < 8; i++)
		crc = (crc >> 1) ^ ((crc & 1) ? 0x82F63B78 : 0);
	return crc;
}

main()
{
	/* http://msdn.microsoft.com/en-us/library/bb514036.aspx */
	unsigned int crc = 1;
	unsigned char input = 100;
	unsigned int res = crc32c_intel(crc, input);
	printf("Result res: %u\n", res);
	assert(res == 1412925310);
}
