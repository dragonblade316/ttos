SRC_DIR = ./src
OBJ_DIR = ./obj
HEADER_DIR = ./headers

ISOFILES = ./target/iso
ISO = ./target/os.iso

CFLAGS = -ffreestanding -g -m32

CFILES = src/kernel.c src/cpu/GDT.c src/cpu/IDT.c src/display/print.c src/cpu/PIC.c src/cpu/except.c src/drivers/ps2_keyboard.c #liballoc_hooks.c liballoc.c
#CPPFILES =
ASMFILES = src/misc/multiboot_header.asm src/start.asm #src/asm/main.asm src/asm/main64.asm handler.asm


SOURCE_DIRS := $(dir $(CFILES))
#SOURCE_DIRS += $(dir $(CPPFILES))
SOURCE_DIRS += $(dir $(ASMFILES))

VPATH = $(sort $(SOURCE_DIRS))

C_FILENAMES := $(notdir $(CFILES))
#CPP_FILENAMES += $(notdir $(CPPFILES))
ASM_FILENAMES += $(notdir $(ASMFILES))

OBJ_FILES := $(patsubst %.c, $(OBJ_DIR)/%.o, $(C_FILENAMES) )
#OBJ_FILES += $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(CPP_FILENAMES) )
OBJ_FILES += $(patsubst %.asm, $(OBJ_DIR)/%.o, $(ASM_FILENAMES))

all : $(ISO)

$(ISO) : $(ISOFILES)/boot
	grub-mkrescue -o $@ $(ISOFILES)

#links the files and give kernel.bin to the iso
$(ISOFILES)/boot : $(OBJ_FILES)
	echo "this works"
	ld -n -m elf_i386 -o $(ISOFILES)/boot/kernel.bin -T $(SRC_DIR)/linker.ld $^

#compile c
$(OBJ_DIR)/%.o : %.c
	$(shell mkdir -p $(OBJ_DIR) )
	gcc -Wall $(CFLAGS) -I $(HEADER_DIR) -c $< -o $@

#compile cpp
#$(OBJ_DIR)/$.o : %.cpp | $(OBJ_DIR)
#	$(shell mkdir -p $(OBJ_DIR) )
#	g++ 
#compile the assembly files

$(OBJ_DIR)/%.o : %.asm
	$(shell mkdir -p $(OBJ_DIR) )
	nasm -f elf32 $< -o $@

run : $(ISO)
	qemu-system-x86_64 -d int -D output.txt  -cdrom ./target/os.iso

debug : $(ISO)
	qemu-system-x86_64 -s -S  -cdrom ./target/os.iso

clean:
	rm -fr $(OBJ_DIR)