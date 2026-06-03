/**
 * @file fram.h
 *
 * @brief Driver interface for the Fujitsu MB85RS64V 64-Kbit SPI FRAM.
 *
 * This module abstracts the SPI + DMA communication with the external
 * Ferroelectric RAM (FRAM) used for non-volatile storage in the Air Quality
 * Monitor. FRAM provides virtually unlimited write endurance (~10^13 cycles)
 * and instant writes, making it ideal for persisting Modbus configuration
 * (holding registers) and alarm counters (input registers) across power cycles.
 *
 * @details
 * Hardware connection:
 *   - SPI1 (master, CPOL=0/CPHA=0)
 *   - CS pin: FRAM_CS_PORT / FRAM_CS_PIN (active-low, controlled via macros).
 *   - DMA2 Stream 2 (RX) / Stream 3 (TX) for bulk transfers.
 *
 * Supported FRAM commands (opcodes):
 *   - WREN / WRDI : Write enable / disable.
 *   - READ / WRITE: Random-address byte read / write with 16-bit address.
 *   - RDSR / WRSR : Read / write status register.
 *   - RDID        : Read device ID.
 *
 * Public API:
 *   - fram_init()  : Enables SPI1 and the FRAM CS pin.
 *   - fram_write() : Writes an arbitrary-length byte buffer starting at a
 *                    16-bit FRAM address (uses DMA for the data phase).
 *   - fram_read()  : Reads an arbitrary-length byte buffer from a 16-bit
 *                    FRAM address (uses DMA for the data phase).
 *
 * @dependencies
 *   - spi.h / dma.h : Low-level SPI and DMA drivers.
 *   - gpio.h        : CS pin control (via FRAM_CS_LOW / FRAM_CS_HIGH macros).
 *   - error.h       : Common error return type.
 */

#ifndef INC_FRAM_H_
#define INC_FRAM_H_

#include "error.h"
#include "gpio.h"

/**
 * FRAM chip select macros to control the CS line of the FRAM module.
 */
#define FRAM_CS_HIGH()              GPIO_SET_PIN(FRAM_CS_PORT, FRAM_CS_PIN)
#define FRAM_CS_LOW()               GPIO_RESET_PIN(FRAM_CS_PORT, FRAM_CS_PIN)

/**
 * Opcode commands for the MB85RS64V FRAM.
 */
#define FRAM_CMD_WREN               (0x06) // Write Enable
#define FRAM_CMD_WRDI               (0x04) // Write Disable
#define FRAM_CMD_RDSR               (0x05) // Read Status Register
#define FRAM_CMD_WRSR               (0x01) // Write Status Register
#define FRAM_CMD_READ               (0x03) // Read Data
#define FRAM_CMD_WRITE              (0x02) // Write Data
#define FRAM_CMD_RDID               (0x9F) // Read Device ID

/**
 * Lengths of various command components in bytes.
 */
#define FRAM_CMD_LENGTH             ((uint8_t) 1)
#define FRAM_ADDRESS_LENGTH         ((uint8_t) 2)
#define FRAM_CMD_AND_ADDRESS_LENGTH (FRAM_CMD_LENGTH + FRAM_ADDRESS_LENGTH)
#define FRAM_DEVICE_ID_LENGTH       ((uint8_t) 4)

/**
 * Address range definitions for FRAM memory.
 */
#define FRAM_ADDR_START             ((uint16_t)0x0000)  // Start address of the FRAM memory
#define FRAM_ADDR_END               ((uint16_t)0x1FFF)  // End address of the FRAM memory

/**
 * Initializes the FRAM module and SPI communication.
 * Configures the chip select line and ensures SPI is initialized if not already active.
 */
void fram_init(void);

/**
 * Writes data to FRAM at the specified address using DMA.
 *
 * @param address Starting address in FRAM for writing.
 * @param write_buffer Pointer to the data buffer to write.
 * @param data_length Number of bytes to write.
 * @return ERR_OK on success, ERR_FAIL if command transmission fails, or ERR_TIMEOUT on timeout.
 */
error_t fram_write(uint16_t address, uint8_t *write_buffer, uint16_t data_length);

/**
 * Reads data from FRAM at the specified address using DMA.
 *
 * @param address Starting address in FRAM for reading.
 * @param read_buffer Pointer to the buffer to store read data.
 * @param data_length Number of bytes to read.
 * @return ERR_OK on success, ERR_FAIL if command transmission fails, or ERR_TIMEOUT on timeout.
 */
error_t fram_read(uint16_t address, uint8_t *read_buffer, uint16_t data_length);


#endif /* INC_FRAM_H_ */





