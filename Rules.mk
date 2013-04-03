# Standard things

.SUFFIXES:

# Subdirectories, in random order

dir := app
include $(dir)/Rules.mk

#  The variables sources_all may be added to by
#  Makefile fragments in the various subdirectories.
#  auto-dependency generation

depend: $(sources_all)
	$(CC) -M $^ > $@
include depend

# General directory independent rules

%.o: %.c
	$(compile)
%: %.o
	$(link)

#  The variables targets_all, clean_all may be added to by
#  Makefile fragments in the various subdirectories.

.PHONY: all
all: $(targets_all)

.PHONY: clean
clean:
	-@rm -f $(clean_all) depend
