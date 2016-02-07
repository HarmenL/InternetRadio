/*
 * Copyright (C) 2012/2014 by Uwe Bonnes(bon@elektron.ikp.physik.tu-darmstadt.de)
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holders nor the names of
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
 * THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * For additional information see http://www.ethernut.de/
 */

/*!
 * \file dev/owibus_uartif.c
 * \brief Implementation of the One-Wire via Uart, run-time configuered
 *
 * \verbatim
 * $Id: owibus_uartif.c 5528 2014-01-07 18:17:58Z u_bonnes $
 * \endverbatim
 */

#include <cfg/arch.h>
#include <stdint.h>
#include <dev/owibus.h>
#include <dev/owibus_uart.h>
#include <stdlib.h>

/*!
 * \brief Register run time configurable One-Wire bus.
 *
 * \param bus         The returned NUTOWIBUS.
 * \param uart        The UART device to use.
 * \param mode        If != 0, requested to connect RX to TX internally,
 *                    multidrive and pull-up TX.
 *
 * \return OWI_SUCCESS on success, a negative value otherwise.
 */
int NutRegisterOwiBus_Uart(NUTOWIBUS *bus, NUTDEVICE *uart, int mode)
{
    NUTOWIINFO_UART *owcb;
    int res;

    if (NutRegisterDevice(uart, 0, 0)) {
        return OWI_INVALID_HW;
    }
    /* Allocate NUTOWIINFO_UART buffer */
    owcb = calloc(1, sizeof(*owcb));
    if (owcb == NULL) {
        return OWI_OUT_OF_MEM;
    }
    res = Uart_OwiInit(owcb, uart, mode);
    if (res) {
        free(owcb);
        return res;
    }

    bus->owibus_info = (uintptr_t) owcb;
    bus->OwiSetup = 0;
    bus->OwiTouchReset = Uart_OwiTouchReset;
    bus->OwiReadBlock = Uart_OwiReadBlock;
    bus->OwiWriteBlock = Uart_OwiWriteBlock;
    bus->mode = 0;

    return OWI_SUCCESS;
}

/*@}*/
