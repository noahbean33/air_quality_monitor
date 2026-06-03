/**
 * @file button.h
 *
 * @brief USER button driver interface for IWDG reset acknowledgement.
 *
 * After an Independent Watchdog (IWDG) reset, the system requires the operator
 * to press the Nucleo board's USER button (PC13) before normal operation
 * resumes. This module manages the EXTI interrupt for that button press and
 * provides the blocking acknowledgement routine.
 *
 * @details
 * Workflow:
 *   1. button_init() creates a binary semaphore and configures EXTI line 13
 *      (falling edge) on GPIO port C for the USER button.
 *   2. button_check_and_acknowledge_iwdg_event() checks the RCC IWDG reset
 *      flag. If set, it blinks the LED and blocks until the semaphore is
 *      given by the EXTI15_10 ISR (i.e., the user presses the button).
 *   3. After acknowledgement, the IWDG flag is cleared and the EXTI is
 *      disabled until the next reset event.
 *
 * @dependencies
 *   - exti.h / gpio.h : EXTI and GPIO configuration (in .c).
 *   - rcc.h (in .c)   : IWDG reset flag query.
 *   - FreeRTOS semphr.h (in .c) : Binary semaphore for ISR synchronization.
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include <stdint.h>

/**
 * Time interval in milliseconds for LED blinking while waiting for button acknowledgement.
 */
#define BUTTON_ACK_BLINK_INTERVAL   ((uint32_t) 500)

/**
 * Sets up the semaphore and configures external interrupts for the Nucleo Board USER button.
 */
void button_init(void);

/**
 * Handles an Independent Watchdog (IWDG) reset event.
 * It checks for the event, requires user acknowledgement through button press, and clears the IWDG flags.
 */
void button_check_and_acknowledge_iwdg_event(void);


#endif /* INC_BUTTON_H_ */
