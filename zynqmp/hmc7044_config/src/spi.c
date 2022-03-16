/*
 * spi.c
 *
 *  Created on: Nov 20, 2019
 *      Author: jpierce
 */

#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <linux/spi/spidev.h>
#include "spi.h"

#define NUM_SPI_CHIP_SELECTS 1  /*valid range 1-6*/
int spifd[NUM_SPI_CHIP_SELECTS] = {0};

extern int debug_print_on;

/***************************************************************************//**
 * @brief spidev_init
*******************************************************************************/
int32_t HAL_initSpi(uint8_t chipSelectIndex, uint8_t spiMode, uint32_t spiClk_Hz)
{
 	unsigned char spiAddrData[] = {0x00};  // device SPI value to select 4 wire mode
    int ret = 0;
    int fd = 0;
    char *device = NULL;
	static int firstInitCall[7] = {1,1,1,1,1,1,1};

    uint8_t bits = 8;

    uint32_t speed = spiClk_Hz;

	if (debug_print_on)
		printf("HAL_initSpi(): chipSelectIndex = %d\n", chipSelectIndex);

	// These go to ZU9 fpga IO
	char spi0dev[] = "/dev/spidev0.0";	// SPI0_SS_HMC7044 // confirm this is true???
//	char spi1dev[] = "/dev/spidev32766.1";	// SPI0_SS1_AD9528
//	char spi2dev[] = "/dev/spidev32766.2";	// FMCHP0_SPI0_SS2_AD9379_2		R1463, SPI_CS0_B
//	// // These go to FMC1
//	// char spi3dev[] = "/dev/spidev32765.0";	// undefined
//	// char spi4dev[] = "/dev/spidev32765.1";	// undefined
//	// char spi5dev[] = "/dev/spidev32765.2";	// undefined


    if ((chipSelectIndex > NUM_SPI_CHIP_SELECTS) || (chipSelectIndex == 0))
    {
        perror("SPI chipSelectIndex is invalid. Valid range = (1-6)");
        return -1;
    }

    if (spifd[chipSelectIndex - 1] > 0)
    {
        fd = spifd[chipSelectIndex - 1];
    }
    else
    {
        switch (chipSelectIndex)
        {
            case 1 :
               device = spi0dev;	// FMCHP0_SPI0_SS_AD9379_1
               break;
           default:
                perror("SPI chipSelectIndex is invalid. Valid range = (1-6)");
                device = spi0dev;
                break;
        }

        /* Open SpiDev and save fd */
        fd = open(device, O_RDWR);
        if (fd < 0)
        {
            perror("Cannot open desired SPI device.");
            return errno;
        }
        else
        {
            spifd[chipSelectIndex-1] = fd;
        }
    }

    /*
    * spi mode
    */
    ret = ioctl(fd, SPI_IOC_WR_MODE, &spiMode);
    if (ret == -1)
    {
        perror("Error settings requested SPI mode");
        return errno;
    }

    /*
    * bits per word
    */
    ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
    if (ret == -1)
    {
        perror("Error setting the number of Bits per SPI word");
        return errno;
    }

    /*
    * max speed hz
    */
    ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
    if (ret == -1)
    {

        perror("Error Setting max SPI clock frequency for current chip select index.");
        return errno;
    }

//	// Following a reset each device to 4 wire mode. Only done once per device.
//   switch (chipSelectIndex)
//	{
//		case 1 :
//			if (firstInitCall[1])
//				HAL_spiWrite(SPI0_SS_HMC7044, spiAddrData, 3);  // config SPI0_SS_AD9371_1 to 4-wire SPI mode
//			firstInitCall[1] = 0;
//			break;
//		case 2 :
//			if (firstInitCall[2])
//				HAL_spiWrite(SPI0_SS1_AD9528, spiAddrData, 3);  // config SPI0_SS1_AD9528 to 4-wire SPI mode
//			firstInitCall[2] = 0;
//			break;
//		case 3 :
//			if (firstInitCall[3])
//				HAL_spiWrite(SPI0_SS2_AD9379_2, spiAddrData, 3);  // config SPI0_SS2_AD9379_2 to 4-wire SPI mode
//			firstInitCall[3] = 0;
//			break;
//		default:
//			perror("SPI chipSelectIndex is invalid. Valid range = (1-6)");
//			device = spi0dev;
//			break;
//	}
    return ret;
}

/***************************************************************************
 * @brief Shift an array of bytes out the SPI
****************************************************************************/
int HAL_spiWrite(uint8_t chipSelectIndex, const unsigned char *txbuf, uint32_t n_tx)
{
    int fd = 0;
	char str[100];

    if (chipSelectIndex > NUM_SPI_CHIP_SELECTS)
    {
		sprintf(str, "HAL_spiWrite chip select out of range, chipSelectIndex=%d", chipSelectIndex);
        perror(str);
        return -1;
    }

	if (debug_print_on)
		printf("HAL_spiWrite: CS=%d, addr = 0x%02X%02X, data = 0x%02X \n", chipSelectIndex, txbuf[0], txbuf[1], txbuf[2]);  // DEBUG - JLS
    fd = spifd[chipSelectIndex-1];

    return write(fd, txbuf, n_tx);
}

/***************************************************************************
 * @brief Shift an array of tx bytes out the SPI,
 * and read one byte following last tx byte.
****************************************************************************/
int HAL_spiRead(uint8_t chipSelectIndex, unsigned char *txbuf, uint8_t n_tx,
                                                       unsigned char *readdata)
{
    /*perform a single SPI read operation:
     * write 8bit or 16bit instruction word followed
     * by 1 byte read
     */

    /*four bytes because it gets cast to a long below*/
    unsigned char tx[] = {0x00,0x00,0x00,0x00};
    unsigned char rx[] = {0x00,0x00,0x00,0x00};
    int ret = 0;
    int fd = 0;
	char str[100];

    /*Get Chips SPI Driver File Descriptor*/
    if (chipSelectIndex > NUM_SPI_CHIP_SELECTS)
    {
		sprintf(str, "HAL_spiWrite chip select out of range, chipSelectIndex=%d", chipSelectIndex);
        perror(str);
       return -1;
    }
    fd = spifd[chipSelectIndex-1];

    /*n_tx can be 1 or 2 bytes (8bit or 16bit instruction word)*/
    if (n_tx < 1 || n_tx > 2)
    {
        perror("HAL_spiRead had invalid tx data size. Valid size is 1 or 2 bytes.");
        return -1;
    }

    /*tx[0] =>read/writebar*/
    tx[0] = txbuf[0] | 0x80;
    tx[1] = txbuf[1];

    struct spi_ioc_transfer tr = {
        .tx_buf = (unsigned long)tx,
        .rx_buf = (unsigned long)rx,
        .len = n_tx + 1,
        .delay_usecs = 1,
    };

    ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
    if (ret == -1)
    {
        perror("can't send spi message");
        return -EIO;
    }

    //*readdata = rx[2];
    *readdata = rx[n_tx];

    return ret;
}
