# Do not edit! Automatically generated on Thu Feb  4 13:47:09 2016

PROJ =	libnutdev

top_srcdir = ../../nut
top_blddir = ../.././nutbld

VPATH = $(top_srcdir)/dev

SRCS =	 ihndlr.c usart.c chat.c term.c circbuff.c netbuf.c can_dev.c nvmem.c \
	 reset.c watchdog.c sbbif0.c spibus_gpio.c spibus0gpio.c i2cbus0gpio.c \
	 owibus0gpio.c owibus_uart.c owibus_uartif.c owibus_uart.c owibus0uart.c null.c \
	 spi_mlcd.c spi_lcd_st7565r.c spi_vscodec.c spi_vscodec0.c dm9000.c null_ether.c \
	 phy.c blockdev.c spi_at45d.c spi_at45d0.c spi_at45d1.c spi_at45d2.c \
	 spi_at45d3.c spi_at45dib.c spi_flash_at45d.c spi_blkio_at45d.c spi_node_at45d.c \
	 spi_at45d_info.c spi_mmc.c spi_mmc_gpio.c mmcard.c rtc.c ds1307rtc.c i2c_pcf85xx.c \
	 spibus.c i2cbus.c owibus.c at24c.c eeprom.c sht21.c mma745x.c led.c keys.c \
	 jtag_tap.c jtag_gpio0.c avrtarget.c nvmem_at45d.c at49bv.c sbi0mmc0.c sbi0mmc1.c \
	 sbi1mmc0.c sbi1mmc1.c ppp_hdlc.c ppp.c spi_7seg.c

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
