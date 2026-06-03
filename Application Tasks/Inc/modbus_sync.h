/**
 * @file modbus_sync.h
 *
 * @brief Modbus data synchronization (mutex) interface.
 *
 * Provides a thin abstraction over a FreeRTOS mutex semaphore that serializes
 * access to the shared Modbus register arrays (coils, discrete inputs, holding
 * registers, and input registers). Both the Modbus Slave task and the Modbus
 * Data Manager task acquire this lock before reading or modifying register data,
 * preventing data races between concurrent Modbus master requests and internal
 * sensor-driven updates.
 *
 * @details
 * API overview:
 *   - modbus_sync_create()  – Allocates the mutex; must be called once at startup.
 *   - modbus_sync_lock()    – Acquires the mutex with a configurable timeout.
 *   - modbus_sync_unlock()  – Releases the mutex.
 *
 * All functions return typed error codes so callers can detect and report
 * mutex-related failures (e.g., timeout or uninitialized mutex) via the
 * centralized error handler.
 *
 * @dependencies
 *   - error.h    : Common error type definitions.
 *   - FreeRTOS.h : pdMS_TO_TICKS macro and semaphore primitives (in .c).
 */

#ifndef INC_MODBUS_SYNC_H_
#define INC_MODBUS_SYNC_H_

#include "error.h"
#include "FreeRTOS.h"

/**
 * Modbus mutex timeout in ms.
 */
#define MODBUS_MUTEX_TIMEOUT_MS     100

/**
 * Modbus mutex timeout in FreeRTOS ticks.
 */
#define MODBUS_MUTEX_TIMEOUT_TICKS  pdMS_TO_TICKS(MODBUS_MUTEX_TIMEOUT_MS)

/**
 * Creates the semaphore used for Modbus data synchronization.
 * @return ERR_OK if successful, ERR_FAIL otherwise.
 */
error_t modbus_sync_create(void);

/**
 * Locks the semaphore to safely access Modbus data.
 * Waits for up to MODBUS_MUTEX_TIMEOUT_TICKS for the semaphore to become available.
 * @return ERR_OK if successful, ERR_MUTEX_TIMEOUT if timed out, ERR_MUTEX_NOT_CREATED if the mutex was not created.
 */
error_t modbus_sync_lock(void);

/**
 * Unlocks the semaphore after accessing Modbus data.
 * @return ERR_OK if successful, ERR_MUTEX_NOT_CREATED if mutex is not created.
 */
error_t modbus_sync_unlock(void);


#endif /* INC_MODBUS_SYNC_H_ */
