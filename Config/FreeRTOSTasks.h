/**
 * @file FreeRTOSTasks.h
 *
 * @brief Centralized FreeRTOS task stack-size and priority definitions.
 *
 * All application-level FreeRTOS tasks draw their stack sizes and priority
 * assignments from this single header. Centralizing these values ensures
 * consistent tuning and simplifies memory budgeting for the system.
 *
 * @details
 * Task priority guidelines used in this project:
 *   - Higher numeric value = higher priority (FreeRTOS convention).
 *   - The Error Handler runs at the highest application priority so that
 *     fault signalling is never starved.
 *   - Sensor acquisition runs above Modbus communication to ensure timely
 *     environmental readings.
 *   - The Modbus Data Manager runs at a lower priority since its work is
 *     deferred and non-time-critical relative to sensor sampling.
 *   - The System Health Monitor runs at idle+1 so the IWDG is only kicked
 *     when all higher-priority work has completed.
 *
 * Stack sizes are expressed in words (4 bytes each on Cortex-M4) and should
 * be validated with FreeRTOS stack high-water-mark utilities during testing.
 *
 * @dependencies
 *   - FreeRTOS.h : configMINIMAL_STACK_SIZE and tskIDLE_PRIORITY macros.
 */

#ifndef FREERTOSTASKS_H_
#define FREERTOSTASKS_H_

#include "FreeRTOS.h"
#include "task.h"

/**
 * The startup task is designed to initialize system components and
 * facilitate the transition to normal operational tasks. The stack size
 * of 512 is chosen for prototyping purposes and should be optimized based
 * on the actual requirements of the initialization routines. It is given
 * high priority (the highest among the tasks defined here) to ensure swift
 * system initialization. However, the task deletes itself upon completion.
 */
#define STARTUP_TASK_STACK_SIZE           (512)
#define STARTUP_TASK_PRIORITY             (configMAX_PRIORITIES - 1)

/**
 * The Handler Task handles system errors.
 * Messages are sent to this task for error handling actions, which can be expanded/customized as needed.
 * The task has a high priority due to the need for timely error detection.
 * Stack size is set at 256 for prototyping, optimize later based on usage.
 */
#define ERROR_HANDLER_TASK_STACK_SIZE     (256)
#define ERROR_HANDLER_TASK_PRIORITY       (configMAX_PRIORITIES - 2)

/**
 * The System Health Monitor Task oversees the overall health of the system.
 * Currently, this includes monitoring the MCU's internal temperature and
 * checking the status of critical tasks and resetting the watchdog timer if they are operational.
 * The task has a low priority to ensure that higher priority tasks get CPU time first,
 * preventing them from being starved and causing a system reset if they fail to update.
 * Stack size is set at 256 for prototyping; optimize later based on usage.
 */
#define SYS_HEALTH_MONITOR_TASK_STACK_SIZE  (256)
#define SYS_HEALTH_MONITOR_TASK_PRIORITY    (configMAX_PRIORITIES - 4)

/**
 * The Sensors Task is responsible for periodically acquiring data from
 * the sensors and updating the data manager. It operates at a relatively high
 * priority level to ensure timely data acquisition and processing.
 * The stack size is initially set to 512 for prototyping; optimize later based on usage.
 */
#define SENSORS_TASK_STACK_SIZE               (512)
#define SENSORS_TASK_PRIORITY                 (configMAX_PRIORITIES - 3)

/**
 * The Modbus Slave Task handles communication with the Modbus master,
 * including processing commands and managing data transfers. Its lower priority
 * ensures the sensors task and system health monitor take precedence for timely
 * data acquisition and watchdog updates. The stack size is set to 512 for
 * prototyping and can be optimized as needed.
 */
#define MODBUS_SLAVE_TASK_STACK_SIZE          (512)
#define MODBUS_SLAVE_TASK_PRIORITY            (configMAX_PRIORITIES - 5)

/**
 * This task processes data updates in the Modbus system, managing the
 * updates related to various registers based on inputs from the Modbus Slave
 * task or Sensors Task. It has a slightly lower priority compared to the
 * Modbus Slave task to allow the Slave task to promptly respond to new
 * commands from the master. The stack size is set to 512 for
 * prototyping and can be optimized as needed.
 */
#define MODBUS_DATA_MGR_TASK_STACK_SIZE       (512)
#define MODBUS_DATA_MGR_TASK_PRIORITY         (configMAX_PRIORITIES - 6)


#endif /* FREERTOSTASKS_H_ */
