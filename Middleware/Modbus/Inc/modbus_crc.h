/**
 * @file modbus_crc.h
 *
 * @brief CRC-16/Modbus checksum calculation interface.
 *
 * Declares the function used to compute the CRC-16 checksum required by the
 * Modbus RTU protocol. Every request and response frame carries a trailing
 * 2-byte CRC that is validated on reception and appended on transmission.
 *
 * @details
 * The implementation in modbus_crc.c uses a table-driven algorithm with two
 * 256-byte lookup tables (high and low CRC bytes) for maximum throughput,
 * conforming to the "Modbus over Serial Line Specification and Implementation
 * Guide V1.02" by the Modbus Organization.
 *
 * @dependencies
 *   - <stdint.h> : Fixed-width integer types.
 */

#ifndef INC_MODBUS_CRC_H_
#define INC_MODBUS_CRC_H_

#include <stdint.h>

/**
 * Computes the CRC-16 checksum for a given buffer based on the Modbus protocol standard.
 * The function utilizes a pre-calculated lookup table to efficiently compute the checksum
 * for error detection in Modbus frame data.
 *
 * @param buffer Pointer to the data buffer for which the CRC-16 checksum is to be computed.
 * @param buffer_length Length of the data buffer in bytes.
 * @return The computed CRC-16 checksum as a 16-bit unsigned integer.
 */
uint16_t modbus_crc16(uint8_t *buffer, uint16_t buffer_length);


#endif /* INC_MODBUS_CRC_H_ */

