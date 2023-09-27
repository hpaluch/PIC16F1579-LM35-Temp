/**
 * ADC1 Generated Driver API Header File
 *
 * @file adc1.h
 *  
 * @defgroup adc1 ADC1
 *
 * @brief This file contains the API prototypes and data types for the ADC1 driver.
 *
 * @version ADC1 Driver Version 2.1.3
 */
/*
© [2023] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#ifndef ADC1_H
#define ADC1_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

/**
 @ingroup adc1
 @typedef adc_result_t
 @brief Used for the result of the Analog-to-Digital (A/D) conversion.
 */

typedef uint16_t adc_result_t;

/**
 * @ingroup adc1
 * @typedef adc_sync_double_result_t
 * @struct Used for the result for a Double ADC1 conversion value.
 */
typedef struct
{
    adc_result_t adcResult1;
    adc_result_t adcResult2;
} adc_sync_double_result_t;


/**
 * @ingroup adc1
 * @enum adc_channel_t
 * @brief Contains the available ADC channels.
 */
typedef enum
{
    channel_Temp =  0x1d,
    channel_DAC =  0x1e,
    channel_FVR =  0x1f,
    channel_AN8 =  0x8
} adc_channel_t;

/**
  Section: ADC Module APIs
 */

/**
 * @ingroup adc1
 * @brief Initializes the ADC1 module. This routine is called before any other ADC1 routine.
 * @param None.
 * @return None.
 */
void ADC_Initialize(void);

/**
 * @ingroup adc1
 * @brief Selects the channel for the A/D conversion.
 * @param channel - Analog channel number on which the A/D conversion will be applied.
 *                  Refer to adc_channel_t  for the available channels.
 * @return None.
 */
void ADC_SelectChannel(adc_channel_t channel);

/**
 * @ingroup adc1
 * @brief Starts A/D conversion.
 * @param None.
 * @return None.
 */
void ADC_StartConversion(void);
 
/**
 * @ingroup adc1
 * @brief Checks if ongoing A/D conversion is complete.
 * @param None.
 * @retval True - A/D conversion is complete.
 * @retval False - A/D conversion is ongoing.
 */
bool ADC_IsConversionDone(void);
 
/**
 * @ingroup adc1
 * @brief Retrieves the result of the latest A/D conversion.
 * @param None.
 * @return The result of A/D conversion. Refer to the adc_result_t.
 */
adc_result_t ADC_GetConversionResult(void);

/**
 * @ingroup adc1
 * @brief Retrieves the result of a single A/D conversion on any given channel.
 * @param channel - Analog channel number on which the A/D conversion will be applied.
 *                  Refer to adc_channel_t  for the available channels.
* @return The result of A/D conversion. Refer to the adc_result_t.
 */
adc_result_t ADC_GetConversion(adc_channel_t channel);
 
/**
 * @ingroup adc1
 * @brief Adds the acquisition delay for the temperature sensor.
 * @pre This function is called when temperature sensor is used.
 * @param None.
 * @return None.
 */
void ADC_TemperatureAcquisitionDelay(void);

#endif	//ADC1_H
