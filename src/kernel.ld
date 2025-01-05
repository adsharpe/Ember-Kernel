/*
 * Format of binary
 */
OUTPUT_FORMAT(elf64-x86-64)

/*
 * Architecture that binary is for
 */
OUTPUT_ARCH(x86-64)

/*
 * Entry point symbol
 */
ENTRY(_kstart)

/*
 * Layout & order of the various sections of the kernel's binary file
 */
SECTIONS
{
	/*
	 * Start at the 1MB memory location.
	 */
	. = 1M;

	/*
	 * Program text goes here; the multiboot header is listed first.
	 */
	.text : ALIGN(4K)
	{
        *(.multiboot_header)         # Multiboot header
        *(.text)                     # Code
        *(.init)                     # C++ constructors
        *(.fini)                     # C++ destructors
	}

	/*
	 * Read Only data goes here.
	 */
	.rodata : ALIGN(4K)
	{
        *(.rodata)                   # Read-only data
	}

	/*
     * Initialized Read/Write data goes here.
	 */
	.data : ALIGN(4K)
	{
        *(.data)                     # Initialized data
	}

	.ctors : ALIGN(4K)
	{
        *(.ctors)
	}

	.dtors : ALIGN(4K)
	{
        *(.dtors)
	}

	/*
	 * Uninitialized Read/Write data goes here.
	 */
	.bss : ALIGN(4K)
	{
        *(.bss)                      # Uninitialized data
        *(COMMON)                    # Common symbols
	}

	  /*
	   * Add other sections here.
	   */
}
