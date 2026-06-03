/**
 * @file modbus_sync.c
 *
 * @brief Modbus data synchronization (mutex) implementation.
 *
 * Wraps a FreeRTOS mutex semaphore to serialize access to the shared Modbus
 * register arrays. The mutex is created once at system startup by the Modbus
 * Slave task (via modbus_sync_create()) and is then acquired/released by both
 * the Modbus Slave task and the Modbus Data Manager task whenever they need to
 * read or modify register data.
 *
 * @details
 *   - modbus_sync_lock() blocks for up to MODBUS_MUTEX_TIMEOUT_TICKS.
 *   - All three functions return distinct error codes so the caller can
 *     report the specific failure (not created, timeout, unlock fail) to the
 *     Error Handler task.
 *
 * @see modbus_sync.h for the public API and timeout configuration.
 */

#include "modbus_sync.h"
#include "semphr.h"

static SemaphoreHandle_t modbus_mutex = NULL;

error_t modbus_sync_create(void)
{
  error_t status = ERR_OK;

  modbus_mutex = xSemaphoreCreateMutex();

  if (modbus_mutex == NULL)
  {
    status = ERR_FAIL;
  }

  return status;
}

error_t modbus_sync_lock(void)
{
  error_t status = ERR_OK;

  if (modbus_mutex == NULL)
  {
    status = MODBUS_MUTEX_NOT_CREATED;
  }
  else if (xSemaphoreTake(modbus_mutex, MODBUS_MUTEX_TIMEOUT_TICKS) != pdTRUE)
  {
    status = MODBUS_MUTEX_TIMEOUT;
  }

  return status;
}

error_t modbus_sync_unlock(void)
{
  error_t status = ERR_OK;

  if (modbus_mutex == NULL)
  {
    status = MODBUS_MUTEX_NOT_CREATED;
  }
  else if (xSemaphoreGive(modbus_mutex) != pdTRUE)
  {
    status = MODBUS_MUTEX_UNLOCK_FAIL;
  }

  return status;
}






