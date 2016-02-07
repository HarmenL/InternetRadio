# Do not edit! Automatically generated on Thu Feb  4 13:47:09 2016

PROJ =	libnuttls

top_srcdir = ../../nut
top_blddir = ../.././nutbld

VPATH = $(top_srcdir)/tls

SRCS =	 tls_misc.c asn1.c tls1.c tls1_clnt.c tls1_svr.c gen_cert.c loader.c \
	 p12.c x509.c

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
