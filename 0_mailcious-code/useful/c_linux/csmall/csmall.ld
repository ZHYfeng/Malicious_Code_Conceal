OUTPUT_FORMAT("elf32-i386", "elf32-i386", "elf32-i386")
OUTPUT_ARCH(i386)
ENTRY(entry)
SECTIONS {
	. = 0x08048054;
	.text : {
		*(.text)
	}
	/DISCARD/	: {
		*(.*)
	}
}
