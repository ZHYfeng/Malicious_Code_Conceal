		BITS	32
		global	_start
		section .text

_start:		mov	esi, _virus
		mov	edi, virus
		mov	ecx, code_size
		cld
		rep	movsb
		
		sub	edi, esi
		mov	esi, virus		
		xor	ecx, ecx
	relocate:
		mov	eax, [rel + ecx * 4]
		add	[esi + eax], edi
		inc	ecx
		cmp	ecx, rel_count
		jb	relocate
		jmp	virus

_virus:		align	1024
		mov	eax, [var]
fix_var		equ	$ - 4 - _virus
		int	3
var		dd	0x55aa55aa
rel		dd	fix_var
rel_count	equ	($ - rel) / 4

code_size	equ	$ - _virus

		section .bss
virus:		resb	4096
