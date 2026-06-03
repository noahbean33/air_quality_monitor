/**
 * @file flash.h
 *
 * @brief Internal flash memory configuration interface.
 *
 * Provides the function to configure the flash access latency (wait states)
 * and caching features based on the target HCLK frequency. This must be
 * called during clock tree initialization (rcc_init) before switching to
 * higher system clock speeds.
 *
 * @details
 * flash_config_wait_states() enables the instruction cache, data cache, and
 * prefetch buffer, then calculates the required number of wait states from
 * the HCLK frequency (latency = (hclk - 1) / 30 for 2.7-3.6 V operation).
 *
 * @dependencies
 *   - mcu.h : CMSIS device definitions (FLASH register access).
 */

#ifndef INC_FLASH_H_
#define INC_FLASH_H_

#include "mcu.h"

/**
 * Configures the number of wait states for accessing the internal flash memory based on the CPU clock frequency (HCLK).
 * @param hclk The CPU clock frequency in MHz.
 */
void flash_config_wait_states(uint8_t hclk);

#endif /* INC_FLASH_H_ */
