# Do not edit! Automatically generated on Thu Feb  4 13:47:09 2016

PROJ =	libnutpro

top_srcdir = ../../nut
top_blddir = ../.././nutbld

VPATH = $(top_srcdir)/pro

SRCS =	 discover.c dhcpc.c ssdp.c ssdpc.c ssdpd.c upnp.c upnp_ctrl.c upnp_dev.c \
	 confdns.c resolv.c uri.c tcphost.c ftpd.c pop3c.c smtpc.c uhttp/uhttpd.c \
	 uhttp/envinit.c uhttp/envreg.c uhttp/envvars.c uhttp/mediatypes.c uhttp/mtinit.c \
	 uhttp/mtreg.c uhttp/responses.c uhttp/utils.c uhttp/modules/mod_auth_basic.c \
	 uhttp/modules/mod_cgi_func.c uhttp/modules/mod_redir.c uhttp/modules/mod_ssi.c \
	 uhttp/os/nut/streamio.c auth.c cgi.c dencode.c discover.c httpd.c httpd_p.c httpopt.c asp.c \
	 ssi.c rfctime.c httpu.c soapc.c soapd.c soap.c snmp.c snmp_api.c snmp_auth.c \
	 snmp_config.c snmp_mib.c snmp_pdu.c asn1.c snmp_agent.c snmp_session.c sntp.c \
	 syslog.c syslog_P.c wins.c uxmlparse.c uxmlstream.c uxmltree.c

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
