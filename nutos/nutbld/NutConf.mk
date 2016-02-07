# Automatically generated on Thu Feb  4 13:47:09 2016
#
# Do not edit, modify UserConf.mk instead!
#

MCU_ATMEGA2560=atmega2560
MCU_ATMEGA2561=atmega2561
MCU_ATMEGA128=atmega128
MCU_ATMEGA103=atmega103
MCU = $(MCU_ATMEGA2561)
HWDEF += -D__HARVARD_ARCH__
HWDEF += -DATMega2561
HWDEF += -D__AVR_3_BYTE_PC__
NUTMEM_RESERVED=64
CRUROM=crurom


include $(top_blddir)/UserConf.mk
