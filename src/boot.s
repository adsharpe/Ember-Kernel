.global kmain                        # Declare kmain as global to avoid linker errors
.section .multiboot_header
.align 4

# Multiboot header
.set MAGIC, 0x1BADB002               # Multiboot magic number
.set FLAGS, 0x00000003               # Flags: multiboot + page alignment + ELF info
.set CHECKSUM, -(MAGIC + FLAGS)      # Checksum: magic + flags + checksum = 0

.long MAGIC                          # Multiboot magic number
.long FLAGS                          # Flags
.long CHECKSUM                       # Checksum

# ELF header information (GRUB2 will use this)
.long 0                              # Header address (not required for basic ELF)
.long 0                              # Load address (not required for basic ELF)
.long 0                              # Load end address (not required for basic ELF)
.long 0                              # BSS end address (not required for basic ELF)
.long _kstart                        # Entry point (GRUB2 will use this)

.section .text
.global _kstart
_kstart:
    cli                              # Disable interrupts
    call kmain                       # Call the kernel's main function
    hlt                              # Halt the CPU if kmain() returns

.section .bss
