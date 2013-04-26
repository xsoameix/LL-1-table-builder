# Standard things

sp := $(sp).x
d_parent_$(sp) := $(d)
d := $(dir)

# Local variables

sources := SymbolTable.c Array.c
sources_in_d := $(addprefix $(d)/,$(sources))
objects_in_d := $(sources_in_d:.c=.o)

# Glogal variables

sources_all := $(sources_all) $(sources_in_d)
objects_all := $(objects_all) $(objects_in_d)
clean_all := $(clean_all) $(objects_in_d)

# Local rules

$(objects_in_d): CF_target := -I$(d)

# Subdirectories, in random order

dir := $(d)/lib
include $(dir)/Rules.mk

# Standard things

d := $(d_parent_$(sp))
sp := $(basename $(sp))
