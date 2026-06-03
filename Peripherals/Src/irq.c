/**
 * @file irq.c
 *
 * @brief NVIC interrupt priority initialization implementation.
 *
 * Implements irq_set_priorities(), which programs the NVIC priority register
 * for every peripheral interrupt used in the system, using the constants
 * defined in irq.h. Called once from main() before the FreeRTOS scheduler
 * starts.
 *
 * @see irq.h for the priority definitions and rationale.
 */

#include "irq.h"

void irq_set_priorities(void)
{
  // Internal temperature sensor
  NVIC_SetPriority(ADC_IRQn, IRQ_ADC_PRIORITY);

  // Button EXTI
  NVIC_SetPriority(EXTI15_10_IRQn, IRQ_EXTI15_10_PRIORITY);

  // Sensirion sensors & related timer
  NVIC_SetPriority(I2C1_EV_IRQn, IRQ_I2C1_EV_PRIORITY);
  NVIC_SetPriority(TIM5_IRQn, IRQ_TIM5_PRIORITY);

  // Modbus
  NVIC_SetPriority(USART2_IRQn, IRQ_USART2_PRIORITY);

  // FRAM
  NVIC_SetPriority(SPI1_IRQn, IRQ_SPI1_PRIORITY);
  NVIC_SetPriority(DMA2_Stream2_IRQn, IRQ_DMA2_STREAM2_PRIORITY);
  NVIC_SetPriority(DMA2_Stream3_IRQn, IRQ_DMA2_STREAM3_PRIORITY);
}
