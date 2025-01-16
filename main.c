ADC 3 Timer tetiklemeli
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/adc.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "inc/tm4c123gh6pm.h"

void SetInitSettings();
uint32_t value[1];

// ADC kesme servis rutini
void ADC0Handler(void) {
    // ADC kesme bayra��n� temizle
    ADCIntClear(ADC0_BASE, 3);

    // ADC sonucunu al
    ADCSequenceDataGet(ADC0_BASE, 3, value);

    // Sonu� burada kullan�labilir
}

int main(void) {
    SetInitSettings();

    while (1) {
        // Ana d�ng�
    }
}

void SetInitSettings() {
    // Sistem saati ayar� (50 MHz)
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);

    // GPIOF ve ADC0 periferiklerini etkinle�tir
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

    // Timer0 yap�land�rmas�
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC); // Timer0'u periyodik modda ayarla

    // Timer 0A'n�n y�k de�eri (�rne�in, her 1 saniyede bir tetikleme yapmak i�in)
    uint32_t period = SysCtlClockGet();  // 50 MHz, bu da 1 saniyeye kar��l�k gelir
    TimerLoadSet(TIMER0_BASE, TIMER_A, period - 1);

    // Timer0A'y� etkinle�tir
    TimerControlTrigger(TIMER0_BASE, TIMER_A, true); // ADC tetikleme i�in Timer kullan�m� etkinle�tir
    TimerEnable(TIMER0_BASE, TIMER_A); // Timer 0A'y� ba�lat

    // ADC0 Sequence 3 yap�land�rmas� (Timer tetiklemeli)
    ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_TIMER, 0);

    // Sequence 3 i�in ad�mlar (1 �rnek CH0 �zerinden)
    ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_CH0 | ADC_CTL_IE | ADC_CTL_END);

    // Sequence 3'� etkinle�tir
    ADCSequenceEnable(ADC0_BASE, 3);

    // ADC kesmeleri etkinle�tir
    IntMasterEnable();
    ADCIntRegister(ADC0_BASE, 3, ADC0Handler);
    ADCIntEnable(ADC0_BASE, 3);
}
