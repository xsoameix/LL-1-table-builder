# Standard things

d_parent := $(d)
d := $(dir)

# Local variables

sources := main.c Lib.c Scanner.c Parser.c ParserTree.c Array.c Semantic.c SymbolTable.c Token.c
targets := main
sources_in_d := $(addprefix $(d)/,$(sources))
objects_in_d := $(sources_in_d:.c=.o)
targets_in_d := $(addprefix $(d)/,$(targets))

# Glogal variables

sources_all := $(sources_all) $(sources_in_d)
objects_all := $(objects_all) $(objects_in_d)
targets_all := $(targets_all) $(targets_in_d)
clean_all := $(clean_all) $(objects_in_d) $(targets_in_d)

# Local rules

$(objects_in_d): CF_target := -I$(d)

# Subdirectories, in random order

#dir := $(d)/follow
#include $(dir)/Rules.mk
dir := $(d)/IntegrationTest
include $(dir)/Rules.mk
dir := $(d)/UnitTest
include $(dir)/Rules.mk

# Local rules

$(targets_in_d): $(objects_all)
	$(link)

# Standard things

d := $(d_parent)
