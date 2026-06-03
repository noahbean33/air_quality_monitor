/**
 * @file iwdg.h
 *
 * @brief Independent Watchdog (IWDG) driver interface.
 *
 * Provides initialization and control functions for the STM32F4 IWDG. The
 * IWDG is clocked from the 32 kHz LSI oscillator and operates independently
 * of the main system clock, ensuring a system reset even if the CPU or the
 * main oscillator fails.
 *
 * @details
 * Configuration:
 *   - Prescaler: /128  (32 kHz / 128 = 250 Hz tick).
 *   - Reload value: calculated for a ~4 s timeout (IWDG_TIMEOUT).
 *   - iwdg_init() enables the LSI, unlocks the IWDG registers, sets the
 *     prescaler and reload, then starts the watchdog.
 *
 * Inline helpers:
 *   - iwdg_enable()             : Starts the watchdog (write 0xCCCC to KR).
 *   - iwdg_enable_write_access(): Unlocks PR/RLR registers (write 0x5555).
 *   - iwdg_reset()              : Kicks the watchdog (write 0xAAAA to KR).
 *
 * The System Health Monitor task calls iwdg_reset() each cycle only when all
 * monitored tasks are healthy.
 *
 * @dependencies
 *   - mcu.h : CMSIS IWDG register definitions.
 */

#ifndef INC_IWDG_H_
#define INC_IWDG_H_

#include "mcu.h"

/**
 * Independent Watchdog key definitions.
 */
#define IWDG_KEY_ENABLE           (0x0000CCCCU)
#define IWDG_KEY_WR_ACCESS_ENABLE (0x00005555U)
#define IWDG_KEY_RELOAD           (0x0000AAAAU)

/**
 * IWDG timeout in ms - adjust as necessary.
 */
#define IWDG_TIMEOUT              ((uint16_t) 4000)

/**
 * Enumeration for the IWDG prescalers.
 */
typedef enum
{
  IWDG_PRESCALER_4   = 0x00,
  IWDG_PRESCALER_8   = 0x01,
  IWDG_PRESCALER_16  = 0x02,
  IWDG_PRESCALER_32  = 0x03,
  IWDG_PRESCALER_64  = 0x04,
  IWDG_PRESCALER_128 = 0x05,
  IWDG_PRESCALER_256 = 0x06
} iwdg_prescaler_e;

/**
 * Starts the IWDG.
 */
static inline void iwdg_enable(void)
{
  IWDG->KR = IWDG_KEY_ENABLE;
}

/**
 * Enables write access to the IWDG registers.
 */
static inline void iwdg_enable_write_access(void)
{
  IWDG->KR = IWDG_KEY_WR_ACCESS_ENABLE;
}

/**
 * Resets the IWDG with the value previously set in the reload register.
 */
static inline void iwdg_reset(void)
{
  IWDG->KR = IWDG_KEY_RELOAD;
}

/**
 * Initializes the Independent Watchdog for 4 second timeouts.
 */
void iwdg_init(void);


#endif /* INC_IWDG_H_ */
