# Makefile for building the Ember kernel using LLVM toolchain

# Compiler flags
CFLAGS     := -c -target x86_64-pc-none-elf -ffreestanding -fno-PIC -O2 -Wall -Wextra -I.
CXXFLAGS   := $(CFLAGS) -fno-exceptions -fno-rtti -std=c++17
AFLAGS     := -target x86_64-pc-none-elf -ffreestanding -c

LDFLAGS    := -nostdlib -z max-page-size=0x1000 -T kernel.ld

# Obj targets
BOOT_OBJS       := boot.o
KERNEL_OBJS		:= kmain.o

OBJS			:= $(BOOT_OBJS) $(KERNEL_OBJS)

KERNEL     := kernel.elf
OBJDIR     := build
OBJS	:= $(addprefix $(OBJDIR)/,$(OBJS))

# Toolchain (LLVM)
CC         := clang
CXX        := clang++
LD         := ld.lld

# Build rules
$(OBJDIR)/%.o : %.c
	@echo Compiling : $<
	@$(CC) $(CFLAGS) $< -o $@
$(OBJDIR)/%.o : %.cpp
	@echo Compiling : $<
	@$(CXX) $(CXXFLAGS) $< -o $@
$(OBJDIR)/%.o : %.s
	@echo Assembling: $<
	@$(CC) $(AFLAGS) -x assembler-with-cpp $< -o $@
$(OBJDIR)/%.o : %.S
	@echo Assembling: $<
	@$(CC) $(CFLAGS) -x assembler-with-cpp $< -o $@

# Default target
all: $(OBJDIR) $(OBJDIR)/$(KERNEL)

# Link kernel from object files
$(OBJDIR)/$(KERNEL): $(OBJS)
	@echo Linking: $@
	@$(LD) $(LDFLAGS) -o $@ $(OBJS)

# Create object dir
$(OBJDIR):
	@mkdir -p $(OBJDIR)

# Clean build
clean:
	@echo Cleaning...
	@rm -rf $(OBJDIR) $(KERNEL)

