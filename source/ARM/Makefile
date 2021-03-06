###############################################################################
#	makefile
#	 by Alex Chadwick
#
#	A makefile script for generation of raspberry pi kernel images.
###############################################################################

# The toolchain to use. arm-none-eabi works, but there does exist
# arm-bcm2708-linux-gnueabi.
#ARMGNU ?= arm-none-eabi
ARMGNU ?= ~/devel/rpi/tools/arm-bcm2708/arm-bcm2708hardfp-linux-gnueabi/bin/arm-bcm2708hardfp-linux-gnueabi

# The intermediate directory for compiled object files.
BUILD = build/
# The directory in which source files are stored.
SOURCE = source/

# The name of the output file to generate.
TARGET = root/boot/kernel.img

# The name of the assembler listing file to generate.
#LIST = kernel.list
# The name of the map file to generate.
#MAP = kernel.map

# The name of the linker script to use.
LINKER = kernel.ld

# The names of all object files that must be generated. Deduced from the
# assembly code files in source.
OBJECTS := $(patsubst $(SOURCE)%.s,$(BUILD)%.o,$(wildcard $(SOURCE)*.s))

# Rule to make everything.
all: $(TARGET) $(LIST)

# Rule to remake everything. Does not include clean.
rebuild: all

# Rule to make the listing file.
#$(LIST) : $(BUILD)kernel.elf
#	$(ARMGNU)-objdump -d $(BUILD)kernel.elf > $(LIST)

# Rule to make the image file.
$(TARGET) : $(BUILD)kernel.elf
	$(ARMGNU)-objcopy $(BUILD)kernel.elf -O binary $(TARGET)

# Rule to make the elf file.
#$(BUILD)kernel.elf : $(OBJECTS) $(LINKER)
#	$(ARMGNU)-ld --no-undefined $(OBJECTS) -Map $(MAP) -o $(BUILD)kernel.elf -T $(LINKER)
$(BUILD)kernel.elf : $(OBJECTS) $(LINKER)
	$(ARMGNU)-ld --no-undefined $(OBJECTS) -o $(BUILD)kernel.elf -T $(LINKER)

# Rule to make the object files.
$(BUILD)%.o: $(SOURCE)%.s $(BUILD)
	$(ARMGNU)-as -I $(SOURCE) $< -o $@

$(BUILD):
	mkdir $@

# Rule to clean files.
clean :
	-rm -rf $(BUILD)
	-rm -f $(TARGET)
	-rm -f $(LIST)
	-rm -f $(MAP)
