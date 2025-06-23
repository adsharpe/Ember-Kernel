# Makefile for building the Ember kernel using LLVM toolchain

# Temporary spot for defining target build architecture
ARCH_X86_64 = 1

# Architecture switches

ifdef ARCH_X86_64
	ARCH_DIR = arch/x86_64
	TARGET = x86_64-pc-none-elf
	ARCH_OBJS   := boot.o
endif

# Compiler flags
CFLAGS     := -c -target $(TARGET) -ffreestanding -fno-PIC -O2 -Wall -Wextra -I.
CXXFLAGS   := $(CFLAGS) -fno-exceptions -fno-rtti -std=c++17
AFLAGS     := -target $(TARGET) -ffreestanding -c
LDFLAGS    := -nostdlib -z max-page-size=0x1000 -T kernel.ld

# Build directories
BUILD_DIR        := build
BUILD_BOOT_DIR   := $(BUILD_DIR)/boot/grub
BUILD_KERNEL_DIR := $(BUILD_DIR)/system/kernel

# Obj targets
VPATH = ./ $(ARCH_DIR)

KERNEL_OBJS	:= kmain.o

KERNEL      := ember.elf
OBJ_DIR     := objs

OBJS		:= $(ARCH_OBJS) $(KERNEL_OBJS)
OBJS		:= $(addprefix $(OBJ_DIR)/,$(OBJS))

# Toolchain (LLVM)
CC          := clang
CXX         := clang++
LD          := ld.lld

# Build rules
$(OBJ_DIR)/%.o : %.c
	@echo Compiling : $<
	@$(CC) $(CFLAGS) $< -o $@
$(OBJ_DIR)/%.o : %.cpp
	@echo Compiling : $<
	@$(CXX) $(CXXFLAGS) $< -o $@
$(OBJ_DIR)/%.o : %.s
	@echo Assembling: $<
	@$(CC) $(AFLAGS) -x assembler-with-cpp $< -o $@
$(OBJ_DIR)/%.o : %.S
	@echo Assembling: $<
	@$(CC) $(CFLAGS) -x assembler-with-cpp $< -o $@

# Default target
all: $(OBJ_DIR) $(BUILD_DIR) $(BUILD_KERNEL_DIR)/$(KERNEL) $(BUILD_BOOT_DIR)/$(GRUB2_CONFIG)

# Link kernel from object files
$(BUILD_KERNEL_DIR)/$(KERNEL): $(OBJS) $(BUILD_KERNEL_DIR)
	@echo Linking: $@
	@$(LD) $(LDFLAGS) -o $@ $(OBJS)

# Setup boot menu
$(BUILD_BOOT_DIR)/$(GRUB2_CONFIG): $(BUILD_BOOT_DIR)
	@echo Copying Grub2 Configuration files
	@cp ./boot/*.cfg $(BUILD_BOOT_DIR)

# Create object dir
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Create build dir (boot)
$(BUILD_BOOT_DIR): $(BUILD_DIR)
	@mkdir -p $(BUILD_BOOT_DIR)

# Create build dir (kernel)
$(BUILD_KERNEL_DIR): $(BUILD_DIR)
	@mkdir -p $(BUILD_KERNEL_DIR)

# Create build dir (build root)
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Clean build
clean:
	@echo Cleaning...
	@rm -rf $(OBJ_DIR)
	@rm -rf $(BUILD_DIR)

