CFLAGS = -g -std=c99
compile = $(CC) $(CFLAGS) $(CF_target) -o $@ -c $<
link = $(CC) $(CFLAGS) -o $@ $^

#  ---------------------------------
#  Standard parts

include Rules.mk
