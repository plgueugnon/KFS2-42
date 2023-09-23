CRED_BACK=\033[45m
CBLUE=\033[34m
CEND=\033[0m

CFLAGS  = -m32 -std=gnu99 -ffreestanding -O2 -Wall -Wextra -g3 -fno-builtin -fno-exceptions -fno-stack-protector -nostdlib -nodefaultlibs -Wno-overflow
CC      = i686-elf-gcc
LD_FLAGS= -ffreestanding -O2 -nostdlib
ASM     = i686-elf-as
# Directories

ISO_DIR		=	iso

# Files

GRUB_CFG	=	kernel/grub.cfg

BOOT_FILE	=	kernel/boot.s
BOOT_OBJ	=	kernel/boot.o

LINKER		=	kernel/linker.ld

SRCS        =	kernel/src/kernel.c      \
				kernel/src/gdt.c         \
				kernel/src/system.c  \



INCLUDE_FOLDER = kernel/include

H = ""

OBJS		=	$(patsubst %.c,%.o,$(SRCS)) #$(patsubst %.s,%.o,$(SRCS))

# Binary name

NAME		=	kfs_two
BIN			=	$(NAME).bin
ISO			=	$(NAME).iso

.PHONY: all libk boot kernel linker iso clean run

all: boot $(OBJS) linker iso
	@true

boot: $(BOOT_FILE)
	@echo "$(CRED_BACK)Creating $(BOOT_OBJ)$(CEND)"
	$(ASM) $(BOOT_FILE) -o $(BOOT_OBJ)

%.o: %.c
	@echo "$(CRED_BACK)Compiling $@$(CEND)"
	@echo "This should update on .h files too"
	$(CC) $(CFLAGS) -c $< -o $@

linker: $(LINKER) $(BOOT_OBJ) $(OBJS)
	@echo "$(CRED_BACK)Linking$(CEND)"
	$(CC) -T $(LINKER) -o $(BIN) $(LD_FLAGS) $(BOOT_OBJ) $(OBJS)
	@echo "$(CRED_BACK)$(BIN) ready!$(CEND)"

iso:
	@echo "$(CRED_BACK)Filling $(ISO_DIR) directory$(CEND)"
	mkdir -pv $(ISO_DIR)/boot/grub
	cp $(GRUB_CFG) $(ISO_DIR)/boot/grub
	cp $(BIN) $(ISO_DIR)/boot
	@echo "$(CRED_BACK)Making $(ISO)$(CEND)"
	@grub-file --is-x86-multiboot $(ISO_DIR)/boot/$(BIN)
	grub-mkrescue -o $(ISO) --compress=xz $(ISO_DIR)

clean:
	@echo "$(CRED_BACK)Cleaning$(CEND)"
	@rm -rf $(OBJS) $(BOOT_OBJ) $(ISO_DIR)

fclean: clean
	@echo "$(CRED_BACK)NUKING$(CEND)"
	@rm -rf $(BIN) $(ISO)

re: fclean all

drun:
	qemu-system-i386 -no-reboot -no-shutdown -s -cdrom $(ISO)

run:
	qemu-system-i386 -s -cdrom $(ISO)

brun:
	qemu-system-i386 -kernel $(BIN)