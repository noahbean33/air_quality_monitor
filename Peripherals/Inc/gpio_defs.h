/**
 * @file gpio_defs.h
 *
 * @brief Board-level GPIO port and pin assignments for every hardware interface.
 *
 * Maps logical peripheral names (USER_LED, MODBUS_TX, FRAM_SCK, etc.) to their
 * physical STM32 GPIO port and pin. Centralizing these definitions here makes
 * it easy to adjust the PCB layout or pin assignments in a single place.
 *
 * @details
 * Peripheral groups defined:
 *   - User interface   : LED (PA5), button (PC13).
 *   - Test interface   : Debug/test output (PC7).
 *   - Sensirion I2C    : SCL (PB8), SDA (PB9).
 *   - Modbus UART      : TX (PA2), RX (PA3).
 *   - FRAM SPI         : SCK (PB3), MISO (PB4), MOSI (PB5), CS (PA10).
 *
 * @dependencies
 *   - mcu.h  : CMSIS GPIO port base addresses (GPIOA, GPIOB, etc.).
 *   - gpio.h : GPIO_PIN_* enumeration values.
 */

#ifndef INC_GPIO_DEFS_H_
#define INC_GPIO_DEFS_H_

#include "mcu.h"
#include "gpio.h"

// User interface
#define USER_LED_PORT       GPIOA
#define USER_LED_PIN        GPIO_PIN_5
#define USER_BUTTON_PORT    GPIOC
#define USER_BUTTON_PIN     GPIO_PIN_13

// Test interface
#define TEST_PORT           GPIOC
#define TEST_PIN            GPIO_PIN_7

// Sensirion sensors
#define SENSIRION_SCL_PORT  GPIOB
#define SENSIRION_SCL_PIN   GPIO_PIN_8
#define SENSIRION_SDA_PORT  GPIOB
#define SENSIRION_SDA_PIN   GPIO_PIN_9

// Modbus Communication Interface
#define MODBUS_TX_PORT      GPIOA
#define MODBUS_TX_PIN       GPIO_PIN_2
#define MODBUS_RX_PORT      GPIOA
#define MODBUS_RX_PIN       GPIO_PIN_3

// FRAM (External Memory) Interface
#define FRAM_SCK_PORT       GPIOB
#define FRAM_SCK_PIN        GPIO_PIN_3
#define FRAM_MISO_PORT      GPIOB
#define FRAM_MISO_PIN       GPIO_PIN_4
#define FRAM_MOSI_PORT      GPIOB
#define FRAM_MOSI_PIN       GPIO_PIN_5
#define FRAM_CS_PORT        GPIOA
#define FRAM_CS_PIN         GPIO_PIN_10


#endif /* INC_GPIO_DEFS_H_ */
