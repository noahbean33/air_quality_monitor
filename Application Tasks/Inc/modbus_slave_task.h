/**
 * @file modbus_slave_task.h
 *
 * @brief Modbus RTU Slave Task interface for the Air Quality Monitor system.
 *
 * This module implements the Modbus RTU slave endpoint that communicates with an
 * external Modbus master over UART (USART2). The task waits for a notification
 * from the UART ISR (triggered on IDLE line detection) indicating a complete
 * Modbus frame has been received, then validates the CRC and slave address,
 * dispatches the request by function code, and sends either a normal response
 * or an exception frame back to the master.
 *
 * @details
 * Key responsibilities:
 *   - Initializes UART2, holding registers, and input registers from FRAM on startup.
 *   - Validates incoming frames (CRC-16, minimum length, slave address match).
 *   - Handles all standard Modbus function codes: read/write coils, discrete inputs,
 *     holding registers, and input registers (FC 01–06, 0F, 10).
 *   - For write operations, delegates data-side processing to the Modbus Data Manager
 *     task and waits on a feedback queue before sending the response.
 *   - Protects shared register data with the Modbus synchronization mutex.
 *   - Signals the system_event_group (MODBUS_INITIALIZED_BIT) so the Sensors task
 *     knows it is safe to begin sampling.
 *
 * @dependencies
 *   - error.h            : Common error codes.
 *   - FreeRTOSTasks.h    : Stack size / priority definitions.
 *   - FreeRTOS queue.h   : Feedback queue handle.
 *   - modbus_slave.h (in .c) : Low-level Modbus frame parsing and response API.
 *   - modbus_sync.h (in .c)  : Shared-data mutex.
 *   - uart.h (in .c)         : UART initialization and interrupt control.
 *   - system_events.h (in .c): Event group for startup synchronization.
 */

#ifndef INC_MODBUS_SLAVE_TASK_H_
#define INC_MODBUS_SLAVE_TASK_H_

#include "error.h"
#include "FreeRTOSTasks.h"
#include "queue.h"

/**
 * Enumeration of Function Code definitions.
 */
/**
 * Enumeration of Function Code definitions.
 */
typedef enum
{
  READ_COILS            = 0x01,
  READ_DISCRETE_INPUTS  = 0x02,
  READ_HOLDING_REGS     = 0x03,
  READ_INPUT_REGS       = 0x04,
  WRITE_SINGLE_REG      = 0x06,
  WRITE_HOLDING_REGS    = 0x10,
  WRITE_SINGLE_COIL     = 0x05,
  WRITE_MULTI_COILS     = 0x0F
} modbus_function_codes_e;

/**
 * Handle for the feedback queue used to retrieve the satus of requests processed by the Modbus Data Manager.
 */
extern QueueHandle_t modbus_feedback_queue_handle;

/**
 * Sends a task notification to the Modbus Slave task from an ISR to signal
 * the receipt of a Modbus RTU frame (e.g., detected via UART IDLE line).
 * @param xHigherPriorityTaskWoken Pointer updated by the xTaskNotifyFromISR() to pdTRUE
 *        if sending the notification unblocks a higher-priority task.
 */
void modbus_slave_task_send_notification_from_isr(BaseType_t *xHigherPriorityTaskWoken);

/**
 * Starts the Modbus Slave tasks and related resources.
 */
void modbus_slave_tasks_start(void);


#endif /* INC_MODBUS_SLAVE_TASK_H_ */
