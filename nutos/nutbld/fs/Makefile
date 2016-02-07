# Do not edit! Automatically generated on Thu Feb  4 13:47:09 2016

PROJ =	libnutfs

top_srcdir = ../../nut
top_blddir = ../.././nutbld

VPATH = $(top_srcdir)/fs

SRCS =	 pathops.c basename.c dirname.c dirent.c uromfs.c uflashfs.c phatfs.c \
	 phatvol.c phatdir.c phatio.c phat12.c phat16.c phat32.c phatutil.c phatdbg.c \
	 pnutfs.c rawfs.c

OBJS = $(SRCS:.c=.o)
include $(top_blddir)/NutConf.mk

include $(top_srcdir)/Makedefs.avr-gcc

INCFIRST=$(INCPRE)$(top_blddir)/include 

all: $(PROJ).a $(OBJS)

install: $(PROJ).a
	$(CP) $(PROJ).a ../.././nutbld/lib/$(PROJ).a

include $(top_srcdir)/Makerules.avr-gcc

.PHONY: clean
clean: cleancc cleanedit
	-rm -f $(PROJ).a
