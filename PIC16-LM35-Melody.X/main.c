 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.0
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
#include "mcc_generated_files/system/system.h"


#define APP_FVR_TIMEOUT_MS 100

#define APP_VERSION 101 // 123 = 1.23

typedef enum {
    APP_ERROR_FVR_NOT_READY
} app_error_t;

int8_t gErrorCode=-1;
void app_fatal_error(app_error_t err){
    IO_RB7_SetLow(); // RED LED on (we use inverted logic)
    gErrorCode = err;
    // loop forever on error
    while(1){
       NOP(); // may put breakpoint here
    }
}

/*
    Main application
*/

uint16_t gCount = 0;
adc_result_t gAdcmv = 0; // Value from ADC, in mili-volts [mV]

int main(void)
{
    uint8_t i;
    SYSTEM_Initialize();

    // Manually remap RA5 to TX output from UART
    // see https://forum.microchip.com/s/topic/a5C3l000000MdMJEA0/t381350
    RA5PPS = 0x9;
    
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts 
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts 
    // Use the following macros to: 

    // Enable the Global Interrupts 
    //INTERRUPT_GlobalInterruptEnable(); 

    // Disable the Global Interrupts 
    //INTERRUPT_GlobalInterruptDisable(); 

    // Enable the Peripheral Interrupts 
    //INTERRUPT_PeripheralInterruptEnable(); 

    // Disable the Peripheral Interrupts 
    //INTERRUPT_PeripheralInterruptDisable(); 

    printf("\r\nL%d: App v%d.%02d\r\n",__LINE__,APP_VERSION/100,APP_VERSION%100);
    // wait for FVR (Fixed Voltage Reference for ADC) to be ready
    for(i=0;i<APP_FVR_TIMEOUT_MS;i++){
        if(FVR_IsOutputReady())
            break;
        __delay_ms(1);
    }
    if (i==APP_FVR_TIMEOUT_MS){
        printf("ERROR: L%d FVR not READY after %u [ms]\r\n",
             __LINE__,i);
        app_fatal_error(APP_ERROR_FVR_NOT_READY);
    } else {
        printf("L%d FVR ready in %u [ms]\r\n",
                __LINE__,i);
    }
    while(1)
    {
        gCount++;
        // ADC range is 10-bits => 1024
        // Positive Vref = 1024 [mV]
        // So ADC output is directly in [mV]
        gAdcmv = ADC_GetConversion(channel_AN8);
        printf("L%d: #%u Temp=%u.%01u [^C] V=%u [mV]\r\n",
                __LINE__,gCount,gAdcmv/10,gAdcmv%10,gAdcmv);
        __delay_ms(2000);
        IO_RB7_Toggle();
    }    
}