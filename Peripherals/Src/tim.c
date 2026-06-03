/**
 * @file tim.c
 *
 * @brief Timer peripheral driver implementation for the Air Quality Monitor.
 *
 * Implements initialization routines for TIM2, TIM3, and TIM5, plus the
 * TIM5 microsecond-delay utility function.
 *
 * @details
 * Timer configurations:
 *   - TIM2 (tim2_init): Prescaler and ARR set for 1 Hz update events. MMS
 *     configured to output the update event as TRGO, which triggers ADC1
 *     conversions for the internal temperature sensor.
 *   - TIM3 (tim3_init): Prescaler and ARR set for 10 kHz update interrupts,
 *     used by FreeRTOS run-time statistics. The ISR is in main.c.
 *   - TIM5 (tim5_init): Prescaler set for 1 MHz (1 us resolution). One-Pulse
 *     Mode enabled so the counter stops automatically after a single update.
 *     tim5_delay_microseconds() loads the ARR, clears counter/flag, enables
 *     the update interrupt, and starts the counter. The ISR is in
 *     sensirion_hw_i2c_implementation.c.
 *
 * @see tim.h for the public API and detailed function documentation.
 */

#include "tim.h"
#include "rcc_clock_defs.h"

void tim2_init(void)
{
  // Enable the clock for TIM2
  RCC_TIM2_CLK_ENABLE();

  // Timer frequency = APB1 TIM2 clock frequency /(1 + PSC) = 90 MHz/(1 + 8999) = 10 KHz
  // Trigger frequency = 10,000 Hz / (1 + ARR) = 10,000 Hz/(1 + 9999) = 1 Hz
  TIM2->PSC = 8999;
  TIM2->ARR = 9999;

  // Set the MMS bits to "Update" mode
  TIM2->CR2 |= (TIM_CR2_MMS_1);

  // Set the UG bit to generate an update event
  TIM2->EGR |= (TIM_EGR_UG);

  // Enable the TIM2 counter
  TIM2->CR1 |= (TIM_CR1_CEN);
}

void tim3_init(void)
{
  // Enable clock for TIM3
  RCC_TIM3_CLK_ENABLE();

  // Timer frequency = APB1 TIM3 clock frequency /(1 + PSC) = 90 MHz/(1 + 899) = 100 kHz
  // Trigger  frequency = 100 kHz / (1 + ARR) = 100 kHz/10 = 10 kHz
  TIM3->PSC = 899;
  TIM3->ARR = 9;

  // Enable update interrupts
  TIM3->DIER |= TIM_DIER_UIE;

  // Enable TIM3 interrupt in NVIC
  NVIC_EnableIRQ(TIM3_IRQn);

  // Enable the counter
  TIM3->CR1 |= TIM_CR1_CEN;
}

void tim5_init(void)
{
  // Enable clock for TIM5
  RCC_TIM5_CLK_ENABLE();

  // Timer 5 setup
  TIM5->CR1 &= ~(TIM_CR1_CEN);
  TIM5->SR = 0;
  TIM5->CNT = 0;

  // Set the prescaler for 1 MHz frequency
  TIM5->PSC = 89;

  // Force an update event to apply prescaler immediately
  TIM5->EGR |= (TIM_EGR_UG);

  // Clear the update flag after forcing update
  TIM5->SR &= ~(TIM_SR_UIF);

  // One pulse mode
  TIM5->CR1 |= (TIM_CR1_OPM);

  // Enable TIM5 interrupt in NVIC
  NVIC_EnableIRQ(TIM5_IRQn);
}

void tim5_delay_microseconds(uint32_t microseconds)
{
  // Disable the counter to ensure proper configuration
  TIM5->CR1 &= ~(TIM_CR1_CEN);

  // Set the auto-reload value for the desired delay
  TIM5->ARR = microseconds - 1;

  // Clear counter and update flag
  TIM5->CNT = 0;
  TIM5->SR &= ~(TIM_SR_UIF);

  // Enable update interrupts
  TIM5->DIER |= (TIM_DIER_UIE);

  // Enable the counter
  TIM5->CR1 |= (TIM_CR1_CEN);
}




