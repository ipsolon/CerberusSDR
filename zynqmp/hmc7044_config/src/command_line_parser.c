/*
 * command_line_parser.c
 *
 *  Created on: Nov 20, 2019
 *      Author: jpierce
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <stdint.h>
#include <string.h>
#include "spi.h"
#include "timer.h"
#include "adi_hmc7044.h"
#include "hmc7044_hal.h"
#include "hmc7044_reg.h"
#include "adi_cms_api_common.h"
#include "adi_cms_api_config.h"
#include "adi_utils.h"
#include "fpga_axi.h"



int command_line_parser(int argc, char *argv[])
{
	uint32_t spiAddressOffset = 0;
	uint32_t axiAddress = 0;
	uint32_t addrCount = 0;
	uint32_t axiDataBuf[0x2000];
	unsigned 	page_size = sysconf(_SC_PAGESIZE);
	uint32_t axiData = 0;
	uint8_t byteValue = 0;
	uint8_t byteData=0;
	uint32_t addr;
	uint8_t	wrtData, rdData;
	int errorFlag;
	int x;
	unsigned long int iqSampleCount;
	int i;
	int flags;
	adi_hmc7044_device_t hmc7044_dev;

	if (argc > 1)	// decode command line argument
	{
        #if 0
		if ((strcmp("fpgaWriteReg", argv[1]) == 0)||(strcmp("fpgawritereg", argv[1]) == 0))
		{
			// This section assumes AD9371 is already in 4-wire SPI mode
			if (argc == 4)		// read fpga register
			{
				// change address and byteValue arguments to convert ascii hexidecimal
				sscanf( argv[3], "%x", &axiData);
				sscanf( argv[2], "%x", &axiAddress);
				if ( !((axiAddress >= 0x80000000) && (axiAddress < 0xC0000000)) )
				{
					printf("error: AXI address out of range\n");
					exit(0);;
				}
				fpgaAxiRegWrite(axiAddress, 0, axiData);
				printf("axiAddress 0x%08x = 0x%08x\n", axiAddress, axiData);
				exit(0);;
			}
			else
			{
				printf("\fpgaReadReg requires 2 argument\n");
				exit(0);;
			}
		}
		if ((strcmp("fpgaReadReg", argv[1]) == 0)||(strcmp("fpgareadreg", argv[1]) == 0))
		{
			// This section assumes AD9371 is already in 4-wire SPI mode
			if (argc == 3)		// read fpga register
			{
				// change address and byteValue arguments to convert ascii hexidecimal
				sscanf( argv[2], "%x", &axiAddress);
				if ( !((axiAddress >= 0x80000000) && (axiAddress < 0xC0000000)) )
				{
					printf("error: AXI address out of range\n");
					exit(0);;
				}
				fpgaAxiRegRead(axiAddress, 0, &axiData);
				printf("axiAddress 0x%08x = 0x%08x\n", axiAddress, axiData);
				exit(0);;
			}
			else
			{
				printf("\fpgaReadReg requires 1 argument\n");
				exit(0);;
			}
		}

        // HMC write command
		if (strcmp("hmc7044w", argv[1]) == 0)
        {
			if (argc == 4)		//
			{
				printf("argv[2] = %d\n", *(argv[2]));
				sscanf( argv[2], "%x", &spiAddressOffset);
				sscanf( argv[3], "%x", &byteValue);
				uint8_t buf[3];

				buf[0] = (uint8_t) ((spiAddressOffset >> 8) & 0x7f);
				buf[1] = (uint8_t) (spiAddressOffset & 0xff);
				buf[2] = (uint8_t) byteValue;
				printf("HMC7044 write ADDR=[0x%X], VAL=[0x%X]\n", spiAddressOffset, byteValue);
				HAL_spiWrite(SPI0_SS_HMC7044, buf, 3);
                return 0;
			}
			else{
				printf("error: hmc7044w requires 2 args\n");
				return -1;
			}
		}
		else if (strcmp("hmc7044r", argv[1]) == 0)
        {
			if (argc == 3)		//
			{
				printf("argv[2] = %d\n", *(argv[2]));
				sscanf( argv[2], "%x", &spiAddressOffset);

				HAL_wait_us(1000);

				unsigned char txbuf[] = {0x00,0x00,0x00};
				uint8_t data=0;
				int32_t retval;
		        txbuf[0] = (1 << 7) | ((spiAddressOffset >> 8) & 0x7F);
		        txbuf[1] = spiAddressOffset & 0xFF;
		        retval = HAL_spiRead(SPI0_SS_HMC7044, txbuf, 2, &data);

				printf("Read from HMC7044 addr %x = %x, %d\n", spiAddressOffset, data, data);

				exit(0);;
			}
			else
			{
				printf("\nhmc7044r requires 1 argument\n");
				exit(0);;
			}
		}
        #endif
		if (strcmp("clock_config", argv[1]) == 0)
        {
			if (argc >= 3 && argc <= 4)
            {
				FILE *fp;
				int x;
				char filename[120];
				char str[1000];
				char cmdOptionStr[80];
				uint32_t addr;
				uint32_t data;
                uint8_t rdata;

                // SPI readback
                int debug = 0;

				for (x=0; x<argc; x++)
				  printf("***%s***\n", argv[x]);  
				sscanf(argv[2], "%s", filename);
				if (argc == 4) {
					sscanf(argv[3], "%s", cmdOptionStr);
					if (strcmp(cmdOptionStr, "debug") == 0) {
						debug = 1;
					}
				}

				fp = fopen(filename, "r");
				if (fp == NULL){
					printf("Could not open file %s",filename);
					return -1;
				}
				while (fgets(str, 1000, fp) != NULL)
                {
					if (strncmp(str, "dut.write", 9) == 0)
                    {
						sscanf(str, "dut.write(%x, %x)" ,&addr, &data);
						hmc7044_spi_reg_set(&hmc7044_dev, addr, data);
						if (debug == 1) {
							// read data from addr
							hmc7044_spi_reg_get(&hmc7044_dev, addr, &rdata);
                            if( data != rdata ) {
                                printf("readback error: ADDR=[0x%04X], RVAL=[0x%02X] != VAL=[0x%02X]\n", addr, data, rdata);
                            }
						}
					}
				}
				fclose(fp);

                //https://ez.analog.com/clock_and_timing/f/q-a/19676/hmc7044-pll2-not-locking
                //https://ez.analog.com/clock_and_timing/f/q-a/19761/hmc7044-defaults-clock-outputs-after-reset

                // restart divider amd state machine
                hmc7044_spi_reg_get(&hmc7044_dev, 0x1, &rdata);
                rdata |= 0x2;
                hmc7044_spi_reg_set(&hmc7044_dev, 0x1, rdata);
                hmc7044_spi_reg_get(&hmc7044_dev, 0x1, &rdata);
                rdata &= ~0x2;
                hmc7044_spi_reg_set(&hmc7044_dev, 0x1, rdata);

                usleep(250000);
                hmc7044_spi_reg_get(&hmc7044_dev, 0x7D, &rdata);
                if( !(rdata & 0x1) ){
                    printf("PLL2 failed to lock: [0x%02X]\n", rdata);
                    return -1;
                }
                printf("PLL2 locked! [0x%02X]\n", rdata);
			}
			else if (argc == 2) {
				printf("Usage:\n");
				printf("./spi_test clock_config [filename]\n");
				printf("To take a configuration file from the HMC7044 GUI and program the HMC7044 OR\n");
				printf("./spi_test clock_config [filename] debug\n");
				printf("To do the same but print the writes and read back from the register\n");
			}
			else {
				printf("Incorrect num of arguments\n");
			}
		}
	}
	return 0;
}

