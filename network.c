//
// Created by janco on 25-2-16.
//
#include <dev/board.h>
#include <sys/timer.h>
#include <sys/confnet.h>

#include <dev/nicrtl.h>

#include <stdio.h>
#include <io.h>
#include <arpa/inet.h>
#include <pro/dhcp.h>
#include "network.h"

void NetworkInit() {
    /* Register de internet controller. */
    if (NutRegisterDevice(&DEV_ETHER, 0, 0)) {
        printf("Registering  failed.");
    }/* Netwerk configureren op dhcp */
    else if (NutDhcpIfConfig(DEV_ETHER_NAME, NULL, 0)) {
        /* Done. */
    }else {
        printf("Ik heb een internet connectie. Ip is: %s", inet_ntoa(confnet.cdn_ip_addr));
    }
}
