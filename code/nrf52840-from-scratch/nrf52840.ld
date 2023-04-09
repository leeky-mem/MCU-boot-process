MEMORY
{
	rom(rx) : ORIGIN = 0x00000000, LENGTH = 0x00800000
	ram(rwx): ORIGIN = 0x20000000, LENGTH = 0x00040000
}

STACK_SIZE = 0x200; /* 8kB */

SECTIONS
{
	.text :
	{
		KEEP(*(.vectors*))
		*(.text*)
		_etext = .;
	} > rom

	.bss (NOLOAD):
	{
		_sbss = .;
		*(.bss*)
		*(COMMON)
		_ebss = .;
	} > ram

	.data :
	{
		_sdata = .;
		*(.data*);
		_edata = .;
	} > ram AT > rom

	/* stack section */
	.stack (NOLOAD):
	{
		. = ALIGN(8);
		_sstack = .;
		. = . + STACK_SIZE;
		. = ALIGN(8);
		_estack = .;
	} > ram

	. = ALIGN(4);
	_end = . ;
}
