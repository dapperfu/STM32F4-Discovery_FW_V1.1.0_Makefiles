################################################################################
#
# Makefile targets.
#	Targets for STM32F4 Discovery
#
################################################################################

#
# Get objects 
#
OBJS   +=$(SRC:.c=.o)
OBJS   +=$(ASRC:.s=.o)

# Make all
all: $(OBJS) $(PROJECT).elf $(PROJECT).hex

# Make object files from C-files
%.o : %.c
	@echo Compiling $<
	@$(CC) -c $(CPFLAGS) -I . $(INCDIR) $< -o $@

# Make object files from Assembly files
%.o : %.s
	@echo Compiling $<
	@$(AS) -c $(ASFLAGS) $< -o $@

# Link the ELF.
%elf: $(OBJS)
	@echo Linking $@
	@$(CC) $(OBJS) $(LDFLAGS) $(LIBS) -o $@

# Convert to ihex format.
%hex: %elf
	@echo Object copy $@
	@$(CP) -O ihex $< $@

# Flash hex file to the board.
.PHONY: flash
.SINGLESHELL: flash
flash: $(PROJECT).hex
	@echo Flashing $(TARGET)
	@$(FLASH) $(FLASHFLAGS)

clean:
	-rm -f $(OBJS)
	-rm -f $(PROJECT).elf
	-rm -f $(PROJECT).map
	-rm -f $(PROJECT).hex
	-rm -f $(SRC:.c=.lst)
	-rm -f $(ASRC:.s=.lst)
	-rm -fR .dep
	
#
# Include the dependency files, should be the last of the makefile
#
-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)
# *** EOF ***