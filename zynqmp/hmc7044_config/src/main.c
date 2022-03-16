/*
 * Copyright (c) 2012 Xilinx, Inc.  All rights reserved.
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <stdio.h>
#include "spi.h"
#include "command_line_parser.h"

int debug_print_on = 0;

uint32_t get_product_id( void )
{
    // read product ID
    uint8_t data[4] = {0,0,0,0};
    uint8_t txbuf[2];
    for(uint16_t addr = 0x78, k = 0; addr < 0x7B; addr++, k++)
    {
        // byte swap (MSB first)
        txbuf[0] = ((addr >> 8) & 0x1F);
        txbuf[1] = addr & 0xFF;
        if( HAL_spiRead(SPI0_SS_HMC7044, txbuf, 2, &data[k]) < 0 ) {
            printf("failed to read address [0x%X]\n", addr);
            return 0x0;
        }
    }
    return *(uint32_t*)data;
}

int main(int argc, char *argv[])
{
    int rc, ret = 0;

    rc = HAL_initSpi(SPI0_SS_HMC7044, 0, 10000000);
    if( rc < 0 ){
        printf("failed to initialize SPI.. aborting\n");
        return 1;
    }

    //! @note The HMC7044 returns an invalid product ID after power-up

    // verify product ID
    int retry = 5;
    uint32_t pid = 0;
    while( retry > 0 ){
        pid = get_product_id();
        if( pid == 0x045201 || pid == 0x301651  ) {
            break;
        }
        retry--;
    }

    if( retry < 0 ){
        printf("failed verify product ID.. aborting\n");
        return 1;
    }

    printf("product ID found: [0x%X]\n", pid);
	if( argc > 1 ){
		command_line_parser(argc, argv);
	}
    return 0;
}
