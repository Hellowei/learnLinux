
SRCDIR:=.
OBJDIR:=.
CC:=./../../build/toolchain/armlinux/gcc-3.4.4-glibc-2.3.5/arm-softfloat-linux-gnu/bin/arm-softfloat-linux-gnu-gcc
STRIP:=./../../build/toolchain/armlinux/gcc-3.4.4-glibc-2.3.5/arm-softfloat-linux-gnu/bin/arm-softfloat-linux-gnu-strip
CFLAGS:=-O2

#CC:=$(ARM_GCC)
#STRIP:=$(ARM_STRIP)
#CFLAGS:=-Os
STATIC:=-static

.PHONY: all
.DEFAULT: all

OBJDIR:=./obj
GUI_SRCDIR:=$(SRCDIR)
GUI_SRCS:=$(wildcard $(GUI_SRCDIR)/*.c)
GUI_OBJS:=$(addprefix $(OBJDIR)/,$(patsubst %.c,%.o,$(GUI_SRCS)))

GUI_PROGRAM:=m1000

all: $(GUI_PROGRAM)

$(GUI_OBJS): $(OBJDIR)/%.o : %.c
	@if [ ! -d $(dir $@) ] ; then mkdir -v -p $(dir $@) ; fi
	@echo compile: $<
	$(CC) $(CFLAGS) -c $< -o $@

$(GUI_PROGRAM): $(GUI_OBJS)
	$(CC) $(GUI_OBJS) -o $(GUI_PROGRAM) -lpthread $(STATIC)
	$(STRIP) $(GUI_PROGRAM)

	cp -f $(GUI_PROGRAM)  /mnt/nfs
clean:
	rm -rf $(OBJDIR)
	rm -rf $(GUI_PROGRAM)
