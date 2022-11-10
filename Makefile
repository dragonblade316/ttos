SRC_DIR = ./src
OBJ_DIR = ./obj
HEADER_DIR = ./headers

ISOFILES = ./target/iso
ISO = ./target/os.iso

CFILES = src/kernel.c src/print.c PIC.c src/exception_handler.c src/IDT.c
#CPPFILES =
ASMFILES = src/asm/multiboot_header.asm src/asm/main.asm src/asm/main64.asm handler.asm


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
	ld -n -o $(ISOFILES)/boot/kernel.bin -T $(SRC_DIR)/linker.ld $^

#compile c
$(OBJ_DIR)/%.o : %.c
	$(shell mkdir -p $(OBJ_DIR) )
	gcc -Wall -ffreestanding -I $(HEADER_DIR) -c $< -o $@

#compile cpp
#$(OBJ_DIR)/$.o : %.cpp | $(OBJ_DIR)
#	$(shell mkdir -p $(OBJ_DIR) )
#	g++ 
#compile the assembly files

$(OBJ_DIR)/%.o : %.asm
	$(shell mkdir -p $(OBJ_DIR) )
	nasm -f elf64 $< -o $@

run:	
	qemu-system-x86_64 -cdrom ./target/os.iso

clean:
	rm -fr $(OBJ_DIR)