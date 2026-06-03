/**
 * @file irq.h
 *
 * @brief NVIC interrupt priority definitions and initialization.
 *
 * Centralizes the numeric priority levels assigned to every peripheral
 * interrupt in the system. All priorities are expressed relative to
 * configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY so that they remain
 * compatible with FreeRTOS ISR-safe API calls.
 *
 * @details
 * Priority assignments (lower offset = higher urgency):
 *   - ADC (+0)          : Temperature sensor analog watchdog (critical).
 *   - EXTI15_10 (+0)    : USER button press.
 *   - I2C1_EV (+1)      : Sensirion sensor I2C bus events.
 *   - TIM5 (+2)         : Microsecond delay for Sensirion communication.
 *   - SPI1 (+3)         : FRAM SPI transfer completion.
 *   - USART2 (+4)       : Modbus RTU frame reception.
 *   - DMA2 Stream2/3 (+4): FRAM SPI DMA transfer complete.
 *
 * irq_set_priorities() must be called once during startup (from main())
 * before any peripheral interrupt is enabled.
 *
 * @dependencies
 *   - mcu.h            : CMSIS IRQn_Type definitions.
 *   - FreeRTOSConfig.h : configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY.
 */

#ifndef INC_IRQ_H_
#define INC_IRQ_H_

#include "mcu.h"
#include "FreeRTOSConfig.h"

// ADC interrupt priority, critical for temperature sensing
#define IRQ_ADC_PRIORITY              ((uint32_t) (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 0))

// External interrupt priority for the user button
#define IRQ_EXTI15_10_PRIORITY        ((uint32_t) (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 0))

// I2C event and timer interrupt priorities for Sensirion sensor operations.
#define IRQ_I2C1_EV_PRIORITY          ((uint32_t) (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 1))
#define IRQ_TIM5_PRIORITY             ((uint32_t) (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 2))

// USART2 interrupt priority for Modbus operations.
#define IRQ_USART2_PRIORITY           ((uint32_t) (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 4))

// SPI1 interrupt priority for FRAM operations, critical for data storage/retrieval.
#define IRQ_SPI1_PRIORITY             ((uint32_t) (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 3))

// DMA stream priorities for SPI1, used for efficient data transfer with FRAM.
#define IRQ_DMA2_STREAM2_PRIORITY     ((uint32_t) (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 4))
#define IRQ_DMA2_STREAM3_PRIORITY     ((uint32_t) (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 4))

/**
 * Configures the priority levels for various IRQs in the system by setting the
 * priority levels in the NVIC (Nested Vectored Interrupt Controller) for specific interrupts.
 */
void irq_set_priorities(void);


#endif /* INC_IRQ_H_ */
