#ifndef _INCLUDE_CFG_MEMORY_H_
#define _INCLUDE_CFG_MEMORY_H_

/*
 * Do not edit! Automatically generated on Thu Feb  4 13:47:09 2016
 */

#ifndef ARTHERCPLDSTART
#define ARTHERCPLDSTART 0x1100
#endif

#ifndef ARTHERCPLDSPI
#define ARTHERCPLDSPI 0x1200
#endif

#ifndef NUTMEM_SIZE
#define NUTMEM_SIZE 8192
#endif

#ifndef NUTMEM_START
#define NUTMEM_START 0x200
#endif

#ifndef NUTMEM_RESERVED
#define NUTMEM_RESERVED 64
#endif

#ifndef NUTXMEM_SIZE
#define NUTXMEM_SIZE 24064
#endif

#ifndef NUTXMEM_START
#define NUTXMEM_START 0x2200
#endif

#ifndef NUTBANK_COUNT
#define NUTBANK_COUNT 30
#endif

#ifndef NUTBANK_START
#define NUTBANK_START 0x8000
#endif

#ifndef NUTBANK_SIZE
#define NUTBANK_SIZE 0x4000
#endif

#ifndef NUTBANK_SR
#define NUTBANK_SR 0xFFFF
#endif

#ifndef SPI_RATE_AT45D0
#define SPI_RATE_AT45D0 33000000
#endif

#ifndef SPI_MODE_AT45D0
#define SPI_MODE_AT45D0 SPI_MODE_3
#endif

#ifndef SPI_RATE_AT45D1
#define SPI_RATE_AT45D1 33000000
#endif

#ifndef SPI_RATE_AT45D2
#define SPI_RATE_AT45D2 33000000
#endif

#ifndef SPI_RATE_AT45D3
#define SPI_RATE_AT45D3 33000000
#endif

#ifndef AT45_WRITE_POLLS
#define AT45_WRITE_POLLS 1000
#endif

#ifndef FLASH_CHIP_BASE
#define FLASH_CHIP_BASE 0x10000000
#endif

#ifndef FLASH_ERASE_WAIT
#define FLASH_ERASE_WAIT 3000
#endif

#ifndef FLASH_CHIP_ERASE_WAIT
#define FLASH_CHIP_ERASE_WAIT 50000
#endif

#ifndef FLASH_WRITE_POLLS
#define FLASH_WRITE_POLLS 1000
#endif


#endif
