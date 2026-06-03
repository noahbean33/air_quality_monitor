/**
 * @file sensors_task.h
 *
 * @brief Sensors Task interface for the Air Quality Monitor system.
 *
 * The Sensors task is a periodic FreeRTOS task responsible for reading
 * environmental data from the Sensirion SGP40 (VOC index) and SHT3x
 * (temperature and humidity) sensor suite. After each successful measurement
 * cycle it forwards the data to the Modbus Data Manager task so that the
 * latest readings are reflected in the Modbus input registers and alarm
 * evaluation is triggered.
 *
 * @details
 * Key responsibilities:
 *   - Waits for the MODBUS_INITIALIZED_BIT event before starting measurements
 *     to guarantee that the register map is ready.
 *   - Initializes the Sensirion sensor drivers (SGP40 + SHT3x via sensirion API).
 *   - Periodically samples VOC index, ambient temperature, and humidity at an
 *     interval read from the Modbus holding registers (dynamically adjustable
 *     by the Modbus master via the SAMPLING_INTERVAL_UPDATE message).
 *   - Toggles the USER LED after the VOC sensor warm-up phase completes
 *     (voc_index != 0) to give a visual heartbeat.
 *   - Reports sensor read failures to the Error Handler task.
 *   - Sets the g_sensors_task_ok health flag each cycle so the System Health
 *     Monitor can verify this task is alive.
 *
 * @dependencies
 *   - error.h              : Common error type.
 *   - FreeRTOSTasks.h      : Stack size and priority macros.
 *   - sgp40_voc_index.h (in .c) : Sensirion VOC + RH/T measurement API.
 *   - modbus_data_mgr_task.h (in .c) : For posting input register updates.
 *   - system_events.h (in .c) : Event group for Modbus init synchronization.
 */

#ifndef INC_SENSORS_TASK_H_
#define INC_SENSORS_TASK_H_

#include "error.h"
#include "FreeRTOSTasks.h"

/**
 * Sensors data structure to be populated by the sensors task.
 */
typedef struct
{
  uint16_t voc_index;
  uint16_t amb_temp;
  uint16_t hum;
} sensors_task_data_t;

/**
 * Sensors task message IDs enum.
 * Note: expand this based on your needs.
 */
typedef enum
{
  SAMPLING_INTERVAL_UPDATE
} sensors_msg_e;

/**
 * Sensors task message queue structure.
 */
typedef struct
{
  sensors_msg_e msg_id;
  uint16_t sampling_interval;
} sensors_msg_t;

/**
 * Enqueues a message for the Sensors Task.
 * @param msg_id Message ID from the sensors_msg_e enum indicating the type of update.
 * @param sampling_interval The sampling interval of the sensors task.
 * @return ERR_OK if the message was successfully sent to the queue, otherwise ERR_FAIL.
 *         ERR_FAIL indicates that the queue is full, and the message cannot be enqueued at this time.
 */
error_t sensors_task_send_msg(sensors_msg_e msg_id, uint16_t sampling_interval);

/**
 * Starts the Sensors Task.
 */
void sensors_task_start(void);


#endif /* INC_SENSORS_TASK_H_ */
