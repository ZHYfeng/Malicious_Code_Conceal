ENTRY(start)
SECTIONS
{
	. = 0x08048054;
	.text : {
		*(.text.start)
		*(.text)
		*(.text.end)
	}
	/DISCARD/ : {
		*(.*)
	}
}
