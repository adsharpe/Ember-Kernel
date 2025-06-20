.global kmain
.global _kstart

.section .multiboot_header
.align 8

# Multiboot2 header fields

.set MB2_MAGIC, 0xE85250D6       # Multiboot2 magic
.set MB2_ARCH, 0                 # Architecture (0 = i386)
.set MB2_HEADER_LEN, 24          # Length of header including tags
.set MB2_CHECKSUM, (0x100000000 - (MB2_MAGIC + MB2_ARCH + MB2_HEADER_LEN)) & 0xFFFFFFFF

# Start of header
.long MB2_MAGIC                  # magic
.long MB2_ARCH                  # architecture
.long MB2_HEADER_LEN            # header length (bytes)
.long MB2_CHECKSUM              # checksum

# Tag: Align modules on page boundaries (type 1, size 8)
.long 1                        # tag type = ALIGN MODULES
.long 8                        # tag size

# Tag: Entry point (type 9, size 16)
.long 9                        # tag type = ENTRY ADDRESS
.long 16                       # tag size
.quad _kstart                  # entry point address (64-bit)

# Tag: End tag (type 0, size 8)
.long 0                        # end tag type
.long 8                        # end tag size

.section .text
.align 16
_kstart:
    cli
    call kmain
1:
    hlt
    jmp 1b

.section .bss
