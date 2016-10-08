/*
 *	By using this file, you agree to the terms and conditions set
 *	forth in the COPYING file which can be found at the top level
 *	of this distribution.
 */
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
