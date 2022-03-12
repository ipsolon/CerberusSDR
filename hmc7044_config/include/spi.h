/*
 * spi.h
 *
 *  Created on: Nov 20, 2019
 *      Author: jpierce
 */

#ifndef SRC_SPI_H_
#include <stdint.h>
#define SRC_SPI_H_

#define		SPI0_SS_HMC7044		1

int32_t HAL_initSpi(uint8_t chipSelectIndex, uint8_t spiMode, uint32_t spiClk_Hz);

int HAL_spiWrite(uint8_t chipSelectIndex, const unsigned char *txbuf, uint32_t n_tx);
int HAL_spiRead(uint8_t chipSelectIndex, unsigned char *txbuf, uint8_t n_tx, unsigned char *readdata);

#endif /* SRC_SPI_H_ */
