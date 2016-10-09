		BITS	32
		global	_start
		section .text

_start:		mov	esi, _virus
		mov	edi, virus
		mov	ecx, code_size
		cld
		rep	movsb
		
		mov	eax, virus
		lea	ebx, [eax + (virus_data - _virus)]
		mov	[eax + fix_vd], ebx
		
		jmp	virus

_virus:		align	1024
		mov	ebp, strict dword 0
fix_vd		equ	$ - 4 - _virus
		mov	eax, [ebp + (var - virus_data)]
		int	3
	virus_data:
var		dd	0x55aa55aa
code_size	equ	$ - _virus

		section .bss
virus:		resb	4096
