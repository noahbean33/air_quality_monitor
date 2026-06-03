/**
 * @file flash.c
 *
 * @brief Internal flash memory configuration implementation.
 *
 * Implements flash_config_wait_states(), which is called early in rcc_init()
 * to set the correct flash access latency before the system clock is ramped
 * up to 180 MHz. It also enables the instruction cache, data cache, and
 * prefetch buffer for optimal execution performance.
 *
 * @see flash.h for the public API.
 */

#include "flash.h"

void flash_config_wait_states(uint8_t hclk)
{
  // Reset the Flash Access Control Register to the default value after reset
  FLASH->ACR &= ~(FLASH_ACR_LATENCY | FLASH_ACR_PRFTEN | FLASH_ACR_ICEN |
                  FLASH_ACR_DCEN | FLASH_ACR_ICRST | FLASH_ACR_DCRST);

  FLASH->ACR |= (FLASH_ACR_DCEN | FLASH_ACR_ICEN | FLASH_ACR_PRFTEN);

  // Calculate the latency based on the hclk value
  uint32_t latency = (hclk - 1) / 30; // Rounds up to the nearest multiple integer of 30

  // Set the FLASH_ACR_LATENCY based on the latency calculated
  FLASH->ACR |= (latency << FLASH_ACR_LATENCY_Pos);
}
