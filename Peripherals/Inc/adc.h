/**
 * @file adc.h
 *
 * @brief ADC peripheral driver interface for the Air Quality Monitor.
 *
 * Provides the initialization routines for the STM32F4 ADC1 peripheral used to
 * read the internal temperature sensor (channel 18). The ADC is configured for
 * hardware-triggered conversions from TIM2 (rising edge) so that temperature
 * readings occur at a fixed 1 Hz rate without CPU intervention.
 *
 * @details
 * Features:
 *   - adc_init()     : Enables the ADC1 clock, sets the prescaler to ~11.25 MHz,
 *                      turns on the internal temperature sensor reference, and
 *                      calls the static adc1_config() to configure conversion
 *                      parameters and interrupts.
 *   - adc_awd_init() : Configures the Analog Watchdog on a single regular channel
 *                      with user-defined high/low thresholds. An AWD interrupt is
 *                      generated if the converted value falls outside this window.
 *
 * The end-of-conversion (EOC) and analog-watchdog (AWD) interrupts are handled
 * in sys_health_monitor_task.c (ADC_IRQHandler).
 *
 * @dependencies
 *   - mcu.h           : CMSIS device definitions (ADC_TypeDef, etc.).
 *   - rcc_clock_defs.h (in .c) : Clock enable macros for ADC1.
 */

#ifndef INC_ADC_H_
#define INC_ADC_H_

#include "mcu.h"

/**
 * Enumerates ADC channels for clear and easy reference throughout the code.
 */
typedef enum
{
  ADC_CH0 = 0,
  ADC_CH1,
  ADC_CH2,
  ADC_CH3,
  ADC_CH4,
  ADC_CH5,
  ADC_CH6,
  ADC_CH7,
  ADC_CH8,
  ADC_CH9,
  ADC_CH10,
  ADC_CH11,
  ADC_CH12,
  ADC_CH13,
  ADC_CH14,
  ADC_CH15,
  ADC_CH16,
  ADC_CH17,
  ADC_CH18
} adc_channels_e;

/**
 * Initializes ADC for the application by configuring the ADC clock, prescaler,
 * and temperature sensor channel and calls individual configuration functions
 * like adc1_config and enables ADC interrupts.
 * Sets ADC clock to ~11.25 MHz by dividing the APB2 clock (45 MHz) by 4.
 */
void adc_init(void);

/**
 * Sets up the Analog Watchdog (AWD) feature of the specified ADC.
 * AWD is used to monitor the ADC conversion result against set threshold values.
 *
 * @param ADCx          The ADC instance to configure.
 * @param channel       The ADC channel to monitor with AWD.
 * @param high_threshold The high threshold value for the AWD.
 * @param low_threshold  The low threshold value for the AWD.
 */
void adc_awd_init(ADC_TypeDef *ADCx, adc_channels_e channel, uint16_t high_threshold, uint16_t low_threshold);


#endif /* INC_ADC_H_ */
