/**
 * @file sys_health_monitor_task.h
 *
 * @brief System Health Monitor Task interface for the Air Quality Monitor system.
 *
 * This module implements a periodic supervisory task that monitors the overall
 * health of the embedded system. It runs at a lower priority than application
 * tasks so that only a genuinely healthy system (where all higher-priority tasks
 * complete their work on time) will reset the Independent Watchdog (IWDG).
 *
 * @details
 * Key responsibilities:
 *   - Configures the ADC Analog Watchdog (AWD) on the MCU internal temperature
 *     sensor channel (CH18) to detect over/under-temperature conditions.
 *   - Initializes the IWDG when the debugger is not connected.
 *   - Periodically checks health flags set by critical tasks (e.g., g_sensors_task_ok).
 *   - Kicks the IWDG only when all monitored tasks have reported in, thereby
 *     causing a system reset if any critical task stalls.
 *   - Optionally reads the latest ADC temperature conversion for diagnostics.
 *
 * The ADC IRQ handler (ADC_IRQHandler, in the .c file) handles Analog Watchdog
 * alerts, end-of-conversion readouts, and overrun flag clearing.
 *
 * @dependencies
 *   - FreeRTOSTasks.h : Stack size and priority macros.
 *   - adc.h, tim.h, iwdg.h (in .c) : Peripheral drivers for ADC, timers, watchdog.
 *   - error_handler_task.h (in .c)  : For reporting AWD threshold breaches.
 *
 * @note Add additional volatile bool flags (like g_sensors_task_ok) for every
 *       critical task that should be supervised.
 */

#ifndef INC_SYS_HEALTH_MONITOR_TASK_H_
#define INC_SYS_HEALTH_MONITOR_TASK_H_

#include <stdbool.h>
#include "FreeRTOSTasks.h"

/**
 * Temperature thresholds for the analog watchdog.
 */
#define ADC1_AWD_HT_TEMP_CELSIUS  80
#define ADC1_AWD_LT_TEMP_CELSIUS  -20

// Extern health flag for the sensors task
extern volatile bool g_sensors_task_ok;
//... add other flags as necessary

/**
 * Starts the System Health Monitor Task.
 */
void sys_health_monitor_task_start(void);


#endif /* INC_SYS_HEALTH_MONITOR_TASK_H_ */
