/**
 * \file fpga_axi.c
 * \brief Contains source code to read and write FPGA AXI register space from user space using mmap()
 * JLS
 * \date 02.01.2017
 */

#include "fpga_axi.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>

/**
 * \brief fgpaAxiReadWrite function for reading from or writing to FPGA space in PL
 * @param uiod is a char pointer to the UIO device string for mapping
 * @param map_size is the unsigned map size
 * @param count is the number of uint32_t wide reads or writes requested
 * @param offset is the FPGA space (byte) offset address
 * @param rw is the read-write flag where rw=0=read, rw=1=write
 * @param data is a uint32_t pointer for read capture or write source
 * @return returns EXIT_FAILURE if failure, EXIT_SUCCESS if successful
 */
int32_t fpgaAxiReadWrite(char *uiod, uint32_t map_size, uint32_t count, uint32_t offset, uint8_t rw, uint32_t *data)
{
    uint32_t i;
    int fd;
    void *ptr;

    /* Open the UIO device file for reading */
    fd = open(uiod, O_RDWR);

    if (fd < 1)
    {
        perror("Invalid UIO device file ");
        close(fd);
        return(EXIT_FAILURE);
    }

    /* offset must be page aligned */
    ptr = mmap(NULL, map_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

    if (ptr == MAP_FAILED)
    {
        munmap(ptr, map_size);
        close(fd);
        perror("Error mapping the file ");
        return(EXIT_FAILURE);
    }
    else
    {
        for(i = 0; i < count; i++)
        {
            if (rw)
            {
                *((uint32_t *)(ptr + offset)) = data[i];
            }
            else
            {
                data[i] = *((uint32_t *)(ptr + offset));
            }
            offset += 0x00000004;
        }

        /* clean up */
        munmap(ptr, map_size);
        close(fd);
    }

    return(EXIT_SUCCESS);
}

/////////////////////////////////
// New


/**
 * \brief fgpaAxiReadPhysicalMemory function for reading from or writing to FPGA space in PL
 * @param physical_address is the unsigned physical memory base address
 * @param regCount is the number of uint32_t wide reads, effectively, the number or registers to read
 * @param reg_addr_offset is the FPGA space (byte) offset address
 * @param data is a uint32_t pointer for write source, ideally a pointer to uint32_t array or struct
 * @return returns EXIT_FAILURE if failure, EXIT_SUCCESS if successful
 */
int32_t fpgaAxiReadPhysicalMemory(uint32_t physical_address_base, uint32_t regCount, uint32_t reg_addr_offset, uint32_t *data)
	{
		int 		fd;
		unsigned long int	x;
		void 		*ptr;
		// volatile void 		*ptr;
		unsigned 	page_addr;
		unsigned 	page_size = sysconf(_SC_PAGESIZE);
		uint32_t	regData;
		int 		regCnt = 0;



		for (x=0;x<regCount;(++x))
		{
			fpgaAxiRegRead(physical_address_base, (reg_addr_offset+regCnt), &(data[x]));
			// printf("x=0x%04X, addr 0x%X = 0x%08X\n", x, (physical_address_base+reg_addr_offset+regCnt), data[x]);
			regCnt += 4;
		}

		return(EXIT_SUCCESS);
	}

/**
 * \brief fgpaAxiReadPhysicalMemory function for reading from or writing to FPGA space in PL
 * @param physical_address is the unsigned physical memory base address
 * @param regCount is the number of uint32_t wide reads, effectively, the number or registers to read
 * @param reg_addr_offset is the FPGA space (byte) offset address
 * @param data is a uint32_t pointer for write source, ideally a pointer to uint32_t array or struct
 * @return returns EXIT_FAILURE if failure, EXIT_SUCCESS if successful
 */
int32_t fpgaAxiReadPhysicalMemoryPage(uint32_t page_addr, uint32_t *data)
{
	int fd;
	unsigned long int x;
	void *ptr;
	unsigned page_size = sysconf(_SC_PAGESIZE);

	fd = open("/dev/mem",O_RDWR | O_SYNC);
	if (fd < 1)
	{
		perror("Error opening /dev/mem ");
		close(fd);
		return(EXIT_FAILURE);
	}

	ptr = mmap(NULL,page_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,(page_addr & ~(page_size-1)));
	if (ptr == MAP_FAILED)
	{
		perror ("Error mmap returned error");
		close(fd);
		return(EXIT_FAILURE);
	}

	uint32_t page_reg_count = page_size / sizeof(uint32_t);
	for (int x = 0; x < page_reg_count; x++)
	{
		uint32_t reg_num = x * 4;
		data[x] = *((uint32_t *)(ptr + reg_num));
	}

	close(fd);
	munmap(ptr, page_size);

	return(0);
}

/**
 * \brief fgpaAxiWritePhysicalMemory function for reading from or writing to FPGA space in PL
 * @param physical_address is the unsigned physical memory base address
 * @param range is the number of uint32_t wide reads
 * @param reg_addr_offset is the FPGA space (byte) offset address
 * @param data is a uint32_t pointer for read capture, ideally a pointer to uint32_t array or struct
 * @return returns EXIT_FAILURE if failure, EXIT_SUCCESS if successful
 */
int32_t fpgaAxiWritePhysicalMemory(uint32_t physical_address, uint32_t range, uint32_t reg_addr_offset, uint32_t *data)
{
	int 		fd;
	void 		*ptr;
	uint32_t 	page_addr;
	uint32_t 	page_size = sysconf(_SC_PAGESIZE);
	uint32_t i;

    /* Open the UIO device file for reading */
	fd = open("/dev/mem",O_RDWR | O_SYNC);
	if (fd < 1)
	{
		perror("Error opening /dev/mem ");
		close(fd);
		return(EXIT_FAILURE);
	}

    /* reg_addr_offset must be page aligned */
	// calculate base and reg_addr_offset, base address must be on page boundary of page_size (typically=0x1000)
	page_addr	= (physical_address & ~(page_size-1));
	reg_addr_offset = reg_addr_offset + (physical_address&(page_size-1));
	ptr = mmap(NULL,page_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,page_addr);

    if (ptr == MAP_FAILED)
    {
        munmap(ptr, page_size);
        close(fd);
        perror("Error mapping the file ");
        return(EXIT_FAILURE);
    }
    else
    {
        for(i = 0; i < range; i++)
        {
            *((uint32_t *)(ptr + reg_addr_offset)) = data[i];  // write data register
			// data[i] = *((uint32_t *)(ptr + reg_addr_offset));  // read data register
			// printf("reg addr 0x%08X = 0x%08X\n", (ptr + reg_addr_offset), data[i]);
            reg_addr_offset += 0x00000004;
        }

        /* clean up */
        munmap(ptr, page_size);
        close(fd);
    }

    return(EXIT_SUCCESS);
}

/**
 * \brief fpgaAxiRegRead function for reading from AXI mapped FPGA space in PL
 * @param physical_address is the absolute address in the ARM PS physical memory space
 * @param reg_addr_offset is the FPGA space (byte) offset address
 * @param data is a uint32_t pointer for read capture or write source
 * @return returns EXIT_FAILURE if failure, EXIT_SUCCESS if successful
 */
	///////////////////////////////////////////////
	// Read physical AXI PL memory
	uint32_t fpgaAxiRegRead(uint32_t physical_address,uint32_t reg_addr_offset, uint32_t *regData)
	{
		int 		fd;
		unsigned long int	x;
		void 		*ptr;
		uint32_t 	page_addr;
		uint32_t 	page_size = sysconf(_SC_PAGESIZE);
		//uint32_t	regData;

		fd = open("/dev/mem",O_RDWR | O_SYNC);
		if (fd < 1)
		{
			perror("Error opening /dev/mem ");
			close(fd);
			return(EXIT_FAILURE);
		}

		// calculate base and offset, base address must be on page boundary of page_size (typically=0x1000)
		page_addr	= (physical_address & ~(page_size-1));
		reg_addr_offset = reg_addr_offset + (physical_address&(page_size-1));
		ptr = mmap(NULL,page_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,(page_addr & ~(page_size-1)));

		if (ptr == MAP_FAILED)
		{
			perror ("Error mmap returned error");
			close(fd);
			return(EXIT_FAILURE);
		}

		*regData = *((uint32_t *)(ptr+reg_addr_offset));

		munmap(ptr, page_size);
		close(fd);
		return(EXIT_SUCCESS);
	}


	///////////////////////////////////////////////
	// Write physical AXI PL reg memory
	int32_t fpgaAxiRegWrite(uint32_t physical_address,uint32_t reg_addr_offset, uint32_t w_data)
	{
		int 		fd;
		unsigned long int	x;
		void 		*ptr;		// volatile void 		*ptr;
		uint32_t 	page_addr;
		uint32_t 	page_size = sysconf(_SC_PAGESIZE);
		uint32_t	regData;

		fd = open("/dev/mem",O_RDWR | O_SYNC);
		if (fd < 1)
		{
			perror("Error opening /dev/mem ");
			close(fd);
			return(EXIT_FAILURE);
		}

		// calculate base and offset, base address must be on page boundary of page_size (typically=0x1000)
		page_addr	= (physical_address & ~(page_size-1));
		reg_addr_offset = reg_addr_offset + (physical_address&(page_size-1));

		//printf("page_size = 0x%X\n", page_size);
		//printf("w_data = 0x%X\n", w_data);

		ptr = mmap(NULL,page_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,page_addr);
		if (ptr == MAP_FAILED)
		{
			perror ("Error mmap returned error");
			close(fd);
			return(EXIT_FAILURE);
		}

		*((uint32_t *)(ptr+reg_addr_offset))= w_data;	// write the axi register
		//regData = *((uint32_t *)(ptr+reg_addr_offset));
		//printf("w_data = 0x%08X, addr 0x%X = 0x%08X\n", w_data, (page_addr+reg_addr_offset), regData);

		munmap(ptr, page_size);
		close(fd);
		return(EXIT_SUCCESS);
	}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////
	// Simple Axi reads PHY registers
	void dumpFPGA_JESD_PHY_registers(uint32_t jesd_phy_physical_address_base)
	{
		int x;
		uint32_t	data[0x1000];
		uint32_t	regData;

		printf("JESD PHY Base Regs:\n");
		fpgaAxiReadPhysicalMemory(jesd_phy_physical_address_base, 16, 0, data);
		for (x=0;x<16;++x)
		{
			printf("reg addr 0x%08X = 0x%08X,	%d\n", (jesd_phy_physical_address_base + (x*4)), data[x], data[x]);
			data[x] = x;
		}
		printf("JESD PHY PLL Status:\n");
		fpgaAxiReadPhysicalMemory((jesd_phy_physical_address_base), 1, 0x80, data);
			printf("reg addr 0x%08X = 0x%08X,	%d\n", (jesd_phy_physical_address_base + 0x80), data[0], data[0]);
		printf("JESD PHY Clocks:\n");
		fpgaAxiReadPhysicalMemory((jesd_phy_physical_address_base), 21, 0x90, data);
		for (x=0;x<21;++x)
		{
			printf("reg addr 0x%08X = 0x%08X,	%d\n", (jesd_phy_physical_address_base + 0x90 + (x*4)), data[x], data[x]);
			data[x] = x;
		}
		printf("JESD PHY Common DRP Control:\n");
		fpgaAxiReadPhysicalMemory(jesd_phy_physical_address_base, 7, 0x104, data);
		for (x=0;x<7;++x)
		{
			printf("reg addr 0x%08X = 0x%08X,	%d\n", (jesd_phy_physical_address_base + 0x104 + (x*4)), data[x], data[x]);
			data[x] = x;
		}
		printf("JESD PHY Transceiver DRP Control:\n");
		fpgaAxiReadPhysicalMemory(jesd_phy_physical_address_base, 7, 0x204, data);
		for (x=0;x<7;++x)
		{
			printf("reg addr 0x%08X = 0x%08X,	%d\n", (jesd_phy_physical_address_base + 0x204 + (x*4)), data[x], data[x]);
			data[x] = x;
		}
		printf("JESD PHY Common QPLL Control:\n");
		fpgaAxiReadPhysicalMemory(jesd_phy_physical_address_base, 2, 0x304, data);
		for (x=0;x<2;++x)
		{
			printf("reg addr 0x%08X = 0x%08X,	%d\n", (jesd_phy_physical_address_base + 0x304 + (x*4)), data[x], data[x]);
			data[x] = x;
		}
		printf("JESD PHY Transceiver Control Bank 1:\n");
		fpgaAxiReadPhysicalMemory(jesd_phy_physical_address_base, 9, 0x404, data);
		for (x=0;x<9;++x)
		{
			printf("reg addr 0x%08X = 0x%08X,	%d\n", (jesd_phy_physical_address_base + 0x404 + (x*4)), data[x], data[x]);
			data[x] = x;
		}
		printf("JESD PHY Transceiver Control Bank 2:\n");
		fpgaAxiReadPhysicalMemory((jesd_phy_physical_address_base+0x400), 4, 0x104, data);
		for (x=0;x<4;++x)
		{
			printf("reg addr 0x%08X = 0x%08X,	%d\n", (jesd_phy_physical_address_base + 0x504 + (x*4)), data[x], data[x]);
			data[x] = x;
		}
		printf("JESD PHY Transceiver Control Bank 3:\n");
		fpgaAxiReadPhysicalMemory(jesd_phy_physical_address_base, 4, 0x604, data);
		for (x=0;x<4;++x)
		{
			printf("reg addr 0x%08X = 0x%08X,	%d\n", (jesd_phy_physical_address_base + 0x604 + (x*4)), data[x], data[x]);
			data[x] = x;
		}
		
		return;
	}

	///////////////////////////////////////////////
	// dumpFPGA_JESD_TXRX_registers
	void dumpFPGA_JESD_TXRX_registers(uint32_t jesd_tx_physical_address_base)
	{
		int x;
		uint32_t	data[0x1000];
		uint32_t	regData;

		printf("JESD TXRX Base Regs:\n");
		fpgaAxiReadPhysicalMemory(jesd_tx_physical_address_base, 16, 0, data);
		for (x=0;x<16;++x)
		{
			printf("reg addr 0x%08X = 0x%08X\n", (jesd_tx_physical_address_base + (x*4)), data[x]);
			data[x] = x;
		}
		printf("JESD TXRX Lane 0-3 IDs:\n");
		fpgaAxiReadPhysicalMemory((jesd_tx_physical_address_base), 4, 0x400, data);
		for (x=0;x<4;++x)
		{
			printf("reg addr 0x%08X = 0x%08X\n", (jesd_tx_physical_address_base + 0x400 + (x*4)), data[x]);
			data[x] = x;
		}
		printf("JESD TXRX Lane 0 ILA Config Data:\n");
		fpgaAxiReadPhysicalMemory(jesd_tx_physical_address_base, 13, 0x800, data);
		for (x=0;x<13;++x)
		{
			printf("reg addr 0x%08X = 0x%08X\n", (jesd_tx_physical_address_base + 0x800 + (x*4)), data[x]);
			data[x] = x;
		}
		printf("JESD TXRX Lane 1 ILA Config Data:\n");
		fpgaAxiReadPhysicalMemory(jesd_tx_physical_address_base, 13, 0x840, data);
		for (x=0;x<13;++x)
		{
			printf("reg addr 0x%08X = 0x%08X\n", (jesd_tx_physical_address_base + 0x840 + (x*4)), data[x]);
			data[x] = x;
		}
		printf("JESD TXRX Lane 2 ILA Config Data:\n");
		fpgaAxiReadPhysicalMemory(jesd_tx_physical_address_base, 13, 0x880, data);
		for (x=0;x<13;++x)
		{
			printf("reg addr 0x%08X = 0x%08X\n", (jesd_tx_physical_address_base + 0x880 + (x*4)), data[x]);
			data[x] = x;
		}
		printf("JESD TXRX Lane 3 ILA Config Data:\n");
		fpgaAxiReadPhysicalMemory(jesd_tx_physical_address_base, 13, 0x8C0, data);
		for (x=0;x<13;++x)
		{
			printf("reg addr 0x%08X = 0x%08X\n", (jesd_tx_physical_address_base + 0x8C0 + (x*4)), data[x]);
			data[x] = x;
		}
		printf("\n");
		
		return;
	}



