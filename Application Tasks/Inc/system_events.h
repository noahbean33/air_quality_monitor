/**
 * @file system_events.h
 *
 * @brief FreeRTOS Event Group definitions for inter-task startup synchronization.
 *
 * This header declares a global FreeRTOS Event Group and the bit masks used to
 * coordinate the initialization order of application tasks. For example, the
 * Sensors task waits for MODBUS_INITIALIZED_BIT before it begins sampling, so
 * that the Modbus register map is guaranteed to be ready when the first sensor
 * data arrives.
 *
 * @details
 * Usage pattern:
 *   1. The startup task creates `system_event_group`.
 *   2. Each subsystem sets its corresponding bit after initialization completes
 *      (e.g., the Modbus Slave task sets MODBUS_INITIALIZED_BIT).
 *   3. Dependent tasks call xEventGroupWaitBits() to block until prerequisites
 *      are met.
 *
 * @dependencies
 *   - FreeRTOS.h / event_groups.h : Event group API.
 *
 * @note Expand the bit definitions as new subsystems require ordered startup.
 */

#ifndef INC_SYSTEM_EVENTS_H_
#define INC_SYSTEM_EVENTS_H_

#include "FreeRTOS.h"
#include "event_groups.h"

extern EventGroupHandle_t system_event_group;

#define MODBUS_INITIALIZED_BIT  (1 << 0)
#define SENSORS_INITIALIZED_BIT (1 << 1)  // Example for further use
#define OTHER_INITIALIZED_BIT   (1 << 2)  // Example for further use


#endif /* INC_SYSTEM_EVENTS_H_ */
