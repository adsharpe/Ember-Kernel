.intel_syntax noprefix
.global _kstart
.global kmain

.section .multiboot_header, "a"
.align 8

# Multiboot2 header
.set MB2_MAGIC, 0xE85250D6
.set MB2_ARCH, 0
.set MB2_HEADER_LEN, 24
.set MB2_CHECKSUM, (0x100000000 - (MB2_MAGIC + MB2_ARCH + MB2_HEADER_LEN)) & 0xFFFFFFFF

.long MB2_MAGIC
.long MB2_ARCH
.long MB2_HEADER_LEN
.long MB2_CHECKSUM

.long 1        # ALIGN MODULES tag
.long 8

.long 9        # ENTRY ADDRESS tag
.long 16
.quad _kstart

.long 0        # END tag
.long 8

# 32-bit entry point
.section .text
.code32
.align 16
_kstart:
    cli
    mov ebx, multiboot_info_backup
    mov eax, multiboot_magic_backup

    call setup_page_tables
    call setup_long_mode

    # We never return here — control jumps to long_mode_start

halt:
    hlt
    jmp halt

setup_page_tables:
    # Set up pd_table[0] = 0x000000 | 0x83 (2MB page, RW, Present, PS)
    mov eax, 0x00000083
    mov ebx, offset pd_table
    mov [ebx], eax
    mov dword ptr [ebx + 4], 0

    # pdpt_table[0] = address of pd_table | 0x03
    mov eax, offset pd_table
    or eax, 0x03
    mov ebx, offset pdpt_table
    mov [ebx], eax
    mov dword ptr [ebx + 4], 0

    # pml4_table[0] = address of pdpt_table | 0x03
    mov eax, offset pdpt_table
    or eax, 0x03
    mov ebx, offset pml4_table
    mov [ebx], eax
    mov dword ptr [ebx + 4], 0

    ret

setup_long_mode:
    cli
    lgdt [gdt_descriptor]

    # Enable PAE
    mov eax, cr4
    or eax, 1 << 5
    mov cr4, eax

    # Enable Long Mode
    mov ecx, 0xC0000080       # IA32_EFER
    rdmsr
    or eax, 1 << 8            # Set LME
    wrmsr

    # Load PML4 into CR3
    mov eax, offset pml4_table
    mov cr3, eax

    # Enable Paging
    mov eax, cr0
    or eax, 1 << 31
    mov cr0, eax

    # Far jump to 64-bit mode: CS:offset
    ljmp 0x08, offset long_mode_start

# 64-bit code
.section .text
.code64
long_mode_start:
    mov ax, 0x10
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    lea rsp, [stack_top]

    mov multiboot_info_backup, rdi
    mov multiboot_magic_backup, rsi

    call kmain

.halt:
    hlt
    jmp .halt

# GDT
.section .data
.align 8
multiboot_info_backup:
    .quad 0
multiboot_magic_backup:
    .quad 0

.section .rodata
gdt:
    .quad 0                          # Null
    .quad 0x00AF9A000000FFFF         # Code: 0x08
    .quad 0x00AF92000000FFFF         # Data: 0x10

gdt_descriptor:
    .word gdt_end - gdt - 1
    .long gdt
gdt_end:

# Stack (16-byte aligned)
.section .bss
.align 16
stack_bottom:
    .skip 4096
stack_top:

# Page tables (identity map first 2MB)
.section .data
.align 4096
pml4_table:
    .quad 0
.align 4096
pdpt_table:
    .quad 0
.align 4096
pd_table:
    .quad 0
