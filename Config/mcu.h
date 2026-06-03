/**
 * @file mcu.h
 *
 * @brief Centralized MCU header for the STM32F446xx peripheral access layer.
 *
 * This lightweight wrapper exists so that every module in the project can
 * include a single, project-scoped header to obtain the CMSIS device
 * definitions (register structures, bit-field masks, IRQ numbers, etc.)
 * for the STM32F4 series. Routing all inclusions through this file makes
 * it trivial to retarget the project to a different STM32 variant—only
 * the include inside this file needs to change.
 *
 * @dependencies
 *   - stm32f4xx.h : CMSIS device header provided by STMicroelectronics.
 */

#ifndef MCU_H_
#define MCU_H_

#include "stm32f4xx.h"

#endif /* MCU_H_ */
