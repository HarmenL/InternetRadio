# Do not edit! Automatically generated on Thu Feb  4 13:47:09 2016

PROJ =	libnutarch

top_srcdir = ../../nut
top_blddir = ../.././nutbld

VPATH = $(top_srcdir)/arch

SRCS =	 avr/os/context_gcc.c avr/dev/ostimer.c avr/dev/wdt_avr.c \
	 avr/dev/ih_adc.c avr/dev/ih_analog_comp.c avr/dev/ih_canit.c avr/dev/ih_ee_ready.c \
	 avr/dev/ih_int0.c avr/dev/ih_int1.c avr/dev/ih_int2.c avr/dev/ih_int3.c \
	 avr/dev/ih_int4.c avr/dev/ih_int5.c avr/dev/ih_int6.c avr/dev/ih_int7.c \
	 avr/dev/ih_ovrit.c avr/dev/ih_spi_stc.c avr/dev/ih_spm_ready.c \
	 avr/dev/ih_timer0_comp.c avr/dev/ih_timer0_ovf.c avr/dev/ih_timer1_capt.c \
	 avr/dev/ih_timer1_compa.c avr/dev/ih_timer1_compb.c avr/dev/ih_timer1_compc.c \
	 avr/dev/ih_timer1_ovf.c avr/dev/ih_timer2_comp.c avr/dev/ih_timer2_ovf.c \
	 avr/dev/ih_timer3_capt.c avr/dev/ih_timer3_compa.c avr/dev/ih_timer3_compb.c \
	 avr/dev/ih_timer3_compc.c avr/dev/ih_timer3_ovf.c avr/dev/ih_twi.c avr/dev/irqstack.c \
	 avr/dev/ih_usart0_rx.c avr/dev/ih_usart0_tx.c avr/dev/ih_usart0_udre.c \
	 avr/dev/ih_usart1_rx.c avr/dev/ih_usart1_tx.c avr/dev/ih_usart1_udre.c avr/dev/ahdlc0.c \
	 avr/dev/ahdlc1.c avr/dev/ahdlcavr.c avr/dev/debug0.c avr/dev/debug1.c \
	 avr/dev/usart0avr.c avr/dev/usart1avr.c avr/dev/uart0.c avr/dev/uart1.c \
	 avr/dev/uartavr.c avr/dev/lanc111.c avr/dev/nicrtl.c avr/dev/eth0rtl.c \
	 avr/dev/gpio_avr.c avr/dev/adc.c avr/dev/ir.c avr/dev/irsony.c avr/dev/hd44780.c \
	 avr/dev/hd44780_bus.c avr/dev/sja1000.c avr/dev/spibus_avr.c avr/dev/spibus0avr.c \
	 avr/dev/sppif0.c avr/dev/spidigio.c avr/dev/i2cbus_avr.c avr/dev/twif.c \
	 avr/dev/pcmcia.c avr/dev/eeprom.c

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
