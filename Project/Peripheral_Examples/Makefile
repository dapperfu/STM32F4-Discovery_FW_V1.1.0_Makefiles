# Get all subdirectories that contain a makefile.
SUBMAKE=$(wildcard */Makefile)
# Artificially append a .clean to the end of it to clean.
SUBCLEAN = $(addsuffix .clean,$(SUBMAKE))
# Register the phony files.
.PHONY: force clean $(SUBCLEAN)

# make all & make clean.
all: $(SUBMAKE)
clean: $(SUBCLEAN)


$(SUBMAKE): force
	-@$(MAKE) -C $(@D)

$(SUBCLEAN): %.clean : force
	-@$(MAKE) -C $(@D) clean