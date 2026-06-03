/**
 * @file error.h
 *
 * @brief Centralized error type and error code definitions for the Air Quality Monitor.
 *
 * Every module in the project returns an `error_t` value to indicate success
 * or the specific failure that occurred. This header is the single point of
 * definition for all such codes, grouped by subsystem:
 *
 *   - General  : ERR_OK, ERR_FAIL, ERR_TIMEOUT, ERR_INVALID_PARAM
 *   - Sensirion: Probe failures for SHT sensor and SGP40 VOC sensor.
 *   - Modbus   : Invalid register/coil addresses, counts, values, and mutex errors.
 *
 * @note When adding a new peripheral or subsystem, append its error codes
 *       to the error_e enumeration so that existing numeric values remain stable.
 */

#ifndef INC_ERROR_H_
#define INC_ERROR_H_

/**
 * Return type to be used for functions that require an error status returned.
 */
typedef int error_t;

/**
 * Enumeration of error constants (to be expanded as required).
 */
typedef enum
{
  ERR_OK                          = 0,
  ERR_FAIL                        = -1,
  ERR_TIMEOUT                     = -2,
  ERR_INVALID_PARAM               = -3,
  SENSIRION_SHT_PROBE_FAILED      = -4,
  SENSIRION_GET_RHT_SIGNAL_FAILED = -5,
  SENSIRION_SGP_PROBE_FAILED      = -6,
  SENSIRION_GET_SGP_SIGNAL_FAILED = -7,
  SENSIRION_SET_RHT_SIGNAL_FAILED = -8,
  MODBUS_INVALID_REG_COUNT        = -9,
  MODBUS_INVALID_REG_ADDRESS      = -10,
  MODBUS_INVALID_END_ADDRESS      = -11,
  MODBUS_INVALID_COIL_COUNT       = -12,
  MODBUS_INVALID_COIL_ADDRESS     = -13,
  MODBUS_INVALID_COIL_VALUE       = -14,
  MODBUS_INVALID_DISC_COUNT       = -15,
  MODBUS_INVALID_DISC_ADDRESS     = -16,
  MODBUS_INVALID_DISC_VALUE       = -17,
  MODBUS_MUTEX_NOT_CREATED        = -18,
  MODBUS_MUTEX_TIMEOUT            = -19,
  MODBUS_MUTEX_UNLOCK_FAIL        = -20
} error_e;

#endif /* INC_ERROR_H_ */
