# Do not edit! Automatically generated on Thu Feb  4 13:47:09 2016

PROJ =	libnutnet

top_srcdir = ../../nut
top_blddir = ../.././nutbld

VPATH = $(top_srcdir)/net

SRCS =	 tcpin.c tcpout.c tcpsm.c tcpsock.c tcputil.c udpin.c udpout.c udpsock.c \
	 ipcsum.c ipin.c ipout.c ipdemux.c route.c icmpin.c icmpout.c igmp.c igmpin.c \
	 igmpout.c inet.c arpcache.c arpin.c arpout.c ethin.c ethout.c ethdemux.c \
	 ether_addr.c pppin.c pppout.c pppsm.c ipcpin.c ipcpout.c lcpin.c lcpout.c papin.c \
	 papout.c ifconfig.c confnet.c netdebug.c pppdebug.c

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
