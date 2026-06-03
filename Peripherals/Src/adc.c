/**
 * @file adc.c
 *
 * @brief ADC peripheral driver implementation for the Air Quality Monitor.
 *
 * Configures ADC1 for periodic internal temperature sensor readings triggered
 * by TIM2 and provides the Analog Watchdog (AWD) setup for threshold monitoring.
 *
 * @details
 * adc1_config() (static):
 *   - Clears CR1/CR2 to a known state.
 *   - Enables EOC interrupt for end-of-conversion notification.
 *   - Selects TIM2 TRGO (rising edge) as the external trigger.
 *   - Sets EOCS so EOC fires after each single conversion.
 *   - Configures channel 18 (temp sensor) with 112-cycle sample time
 *     (~11 us at 11.25 MHz ADC clock).
 *   - Enables ADC1.
 *
 * adc_awd_init():
 *   - Programs the HTR/LTR threshold registers.
 *   - Selects the monitored channel and enables single-channel AWD on
 *     regular conversions with an interrupt.
 *
 * @see adc.h for the public API and channel enumeration.
 */

#include "adc.h"
#include "rcc_clock_defs.h"

/**
 * Configures ADC1 for the internal temperature sensor measurements.
 * Configures the following settings:
 * - Enable the EOC interrupt.
 * - External trigger from TIM2 (rising edge).
 * - End Of Conversion (EOC) flag set at the end of each regular conversion.
 * - Sampling time for the temperature sensor set to 112 cycles.
 * - Conversion sequence set to Channel 18 (Temperature Sensor).
 * - ADC enabled.
 */
static void adc1_config(void)
{
  // Clear any previous configurations by setting CR1 and CR2 to zero
  ADC1->CR1 = 0;
  ADC1->CR2 = 0;

  // Enalbe the EOC interrupt
  ADC1->CR1 |= (ADC_CR1_EOCIE);

  // Configure trigger detection on the rising edge and timer 2 external trigger
  ADC1->CR2 |= (ADC_CR2_EXTEN_0 | ADC_CR2_EXTSEL_1 | ADC_CR2_EXTSEL_2);

  // Set the EOC flag at the end of each regular conversion
  ADC1->CR2 |= (ADC_CR2_EOCS);

  // Set the sampling time for temperature sensor: 112 + 12 / 11.25 MHz = 11 microseconds
  ADC1->SMPR1 |= (ADC_SMPR1_SMP18_0 | ADC_SMPR1_SMP18_2);

  // Set the sequence to convert Channel 18 (Temperature Sensor)
  ADC1->SQR3 |= (ADC_CH18 << ADC_SQR3_SQ1_Pos);

  // Enable the ADC
  ADC1->CR2 |= (ADC_CR2_ADON);
}

void adc_init(void)
{
  RCC_ADC1_CLK_ENABLE();

  // APB2 running @45 MHz, so divide by 4 = 11.25 MHz
  ADC->CCR |= (ADC_CCR_ADCPRE_0);

  // Enable the temperature sensor
  ADC->CCR |= (ADC_CCR_TSVREFE);

  // ADC1 Configuration
  adc1_config();

  // Enable ADC interrupts
  NVIC_EnableIRQ(ADC_IRQn);
}

void adc_awd_init(ADC_TypeDef *ADCx, adc_channels_e channel, uint16_t high_threshold, uint16_t low_threshold)
{
  // Set the high and low threshold raw ADC values
  ADCx->HTR = high_threshold;
  ADCx->LTR = low_threshold;

  // Analog watchdog channel 18 (temperature sensor)
  ADCx->CR1 |= channel;

  // Enable the Analog watchdog on a single channel in regular channels
  ADCx->CR1 |= (ADC_CR1_AWDSGL | ADC_CR1_AWDEN);

  // Enable Analog watchdog interrupts
  ADCx->CR1 |= (ADC_CR1_AWDIE);
}




