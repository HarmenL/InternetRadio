# Do not edit! Automatically generated on Thu Feb  4 13:47:09 2016

PROJ =	libnutcrypto

top_srcdir = ../../nut
top_blddir = ../.././nutbld

VPATH = $(top_srcdir)/crypto

SRCS =	 aes.c bigint.c rsa.c sha1.c rc4.c md2.c md5.c hmac.c

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
