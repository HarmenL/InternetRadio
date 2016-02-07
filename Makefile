PROJ = bin/internetradioA6


LIBDIR = nutos/nutbld/lib
top_srcdir = nutos/nut
top_blddir = nutos/nutbld
top_appdir = nutos/nutapp

INCFIRST=$(INCPRE)$(top_blddir)/include
include $(top_appdir)/NutConf.mk
include $(top_srcdir)/app/Makedefs.avr-gcc


SRCS =  $(wildcard lib/*.c *.c)
OBJS =  $(SRCS:%.c=%.o)
LIBS =  $(LIBDIR)/nutinit.o -lnutpro -lnutnet -lnutos -lnutfs -lnutgorp -lnutarch -lnutdev -lnutarch -lnutcrt $(ADDLIBS)


all: $(OBJS) $(TARG) $(ITARG) $(DTARG)

include nutos/nutapp/Makerules

clean:
	-rm -f $(OBJS)
	-rm -f $(TARG) $(ITARG) $(DTARG)
	-rm -f $(PROJ).eep
	-rm -f $(PROJ).obj
	-rm -f $(PROJ).map
	-rm -f $(SRCS:.c=.lst)
	-rm -f $(SRCS:.c=.bak)
	-rm -f $(SRCS:.c=.i)
	-rm -f $(SRCS:.c=.d)
