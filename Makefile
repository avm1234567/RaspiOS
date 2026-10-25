ARMGNU ?= aarch64-linux-gnu

INCLUDES = -Ikernel/include -Idrivers/include
COPS = -g -Wall -nostartfiles -ffreestanding $(INCLUDES) -mgeneral-regs-only
ASMOPS = -g $(INCLUDES)

BUILD_DIR = build
LINKER_SCRIPT = linker/linker.ld

all : kernel8.img

clean :
	rm -rf $(BUILD_DIR) *.img

run : kernel8.img
	qemu-system-aarch64 -M raspi4b -kernel kernel8.img -display none -serial stdio -monitor none

# Source files across all modules
C_FILES   = $(wildcard drivers/src/*.c) $(wildcard kernel/src/*.c)
ASM_FILES = $(wildcard boot/*.S) $(wildcard irq/*.S)

# Object files mapping into build/
C_OBJS    = $(patsubst %.c, $(BUILD_DIR)/%_c.o, $(C_FILES))
ASM_OBJS  = $(patsubst %.S, $(BUILD_DIR)/%_s.o, $(ASM_FILES))
OBJ_FILES = $(C_OBJS) $(ASM_OBJS)

$(BUILD_DIR)/%_c.o: %.c
	mkdir -p $(@D)
	$(ARMGNU)-gcc $(COPS) -MMD -c $< -o $@

$(BUILD_DIR)/%_s.o: %.S
	mkdir -p $(@D)
	$(ARMGNU)-gcc $(ASMOPS) -MMD -c $< -o $@

DEP_FILES = $(OBJ_FILES:%.o=%.d)
-include $(DEP_FILES)

kernel8.img: $(LINKER_SCRIPT) $(OBJ_FILES)
	$(ARMGNU)-ld -T $(LINKER_SCRIPT) -o $(BUILD_DIR)/kernel8.elf $(OBJ_FILES)
	$(ARMGNU)-objcopy $(BUILD_DIR)/kernel8.elf -O binary kernel8.img
