# Do not edit! Automatically generated on Thu Feb  4 13:47:09 2016

PROJ =	libnutos

top_srcdir = ../../nut
top_blddir = ../.././nutbld

VPATH = $(top_srcdir)/os

SRCS =	 version.c heap.c bankmem.c thread.c timer.c event.c devreg.c confos.c \
	 semaphore.c mutex.c msg.c condition.c osdebug.c tracer.c fatal.c panic.c
OBJ1 = nutinit.o

OBJS = $(SRCS:.c=.o)
include $(top_blddir)/NutConf.mk

include $(top_srcdir)/Makedefs.avr-gcc

INCFIRST=$(INCPRE)$(top_blddir)/include 

all: $(PROJ).a $(OBJS) $(OBJ1)

install: $(PROJ).a $(OBJ1)
	$(CP) $(PROJ).a ../.././nutbld/lib/$(PROJ).a
	$(CP) $(OBJ1) ../.././nutbld/lib/$(notdir $(OBJ1))

include $(top_srcdir)/Makerules.avr-gcc

.PHONY: clean
clean: cleancc cleanedit
	-rm -f $(PROJ).a
	-rm -f $(OBJ1)
