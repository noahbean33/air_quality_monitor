/**
 * @file modbus_data_mgr_task.h
 *
 * @brief Modbus Data Manager Task interface for the Air Quality Monitor system.
 *
 * The Modbus Data Manager is a FreeRTOS task that acts as the single point of
 * authority for modifying Modbus register data (coils, holding registers, and
 * input registers). All write operations—whether originating from the Modbus
 * master (via the Modbus Slave task) or from internal sensor updates (via the
 * Sensors task)—are serialized through this task's message queue.
 *
 * @details
 * Key responsibilities:
 *   - Receives processing messages describing which registers changed and how.
 *   - Acquires the Modbus synchronization mutex before touching shared data.
 *   - Delegates to per-register-type handlers (coils, holding regs, input regs).
 *   - Evaluates alarm thresholds for sensor readings (VOC, temperature, humidity)
 *     and updates discrete input alarm flags and FRAM-backed alarm counters.
 *   - Persists configuration and alarm data to FRAM via modbus_data_update_nvs_*().
 *   - Sends feedback messages back to the Modbus Slave task when the master's
 *     write request requires a synchronous acknowledgement before responding.
 *
 * @dependencies
 *   - error.h            : Common error type definitions.
 *   - FreeRTOSTasks.h    : Task stack size and priority macros.
 *   - modbus_data.h      : Register read/write and NVS persistence API.
 *   - modbus_sync.h (in .c) : Mutex for shared Modbus data protection.
 *   - sensors_task.h (in .c) : For forwarding sampling interval updates.
 *   - error_handler_task.h (in .c) : For reporting processing failures.
 *
 * @note Expand the processing switch-cases when new coils or holding registers
 *       are added to the Modbus register map.
 */

#ifndef INC_MODBUS_DATA_MGR_TASK_H_
#define INC_MODBUS_DATA_MGR_TASK_H_

#include <stdbool.h>
#include "error.h"
#include "FreeRTOSTasks.h"
#include "modbus_data.h"

/**
 * Modbus Data Manager message IDs enum.
 */
typedef enum
{
  COIL_COMMAND,
  HOLDING_REGS_UPDATE,
  INPUT_REGS_UPDATE
} modbus_data_mgr_msg_e;

/**
 * Modbus Data Manager message queue structure.
 */
typedef struct
{
  modbus_data_mgr_msg_e msg_type;
  void *data;
  uint16_t address;
  uint16_t quantity;
  bool requires_feedback;
} modbus_data_mgr_processing_msg_t;

/**
 * Feedback Message for communication from the Modbus Data Manager task to the Modbus Slave task.
 */
typedef struct
{
  error_t status;
} modbus_data_mgr_feedback_msg_t;

/**
 * Enqueues a Modbus data message for processing by the Modbus Data Manager task.
 *
 * @param msg_type Message ID from the modbus_data_mgr_msg_e enum indicating the type of update.
 * @param data Pointer to data associated with the message. Can be NULL.
 * @param addr The starting address for the Modbus data operation.
 * @param qty The number of registers or coils involved in the operation.
 * @param req_feedback Indicates whether feedback is required from the Modbus Data Manager.
 *
 * @return ERR_OK if the message was successfully enqueued to the queue, otherwise ERR_FAIL.
 */
error_t modbus_data_mgr_send_processing_msg(modbus_data_mgr_msg_e msg_type,
                                            void *data,
                                            uint16_t addr,
                                            uint16_t qty,
                                            bool req_feedback);

/**
 * Enqueues a modbus feedback message for the Modbus Slave task to receive.
 *
 * @param feedback_status Status of the operation (e.g., ERR_OK, ERR_FAIL).
 * @return ERR_OK if the message was successfully sent/enqueued to the queue, otherwise ERR_FAIL.
 */
error_t modbus_data_mgr_send_feedback_msg(error_t feedback_status);

/**
 * Starts the Modbus Data Manager task.
 */
void modbus_data_mgr_start(void);


#endif /* INC_MODBUS_DATA_MGR_TASK_H_ */
