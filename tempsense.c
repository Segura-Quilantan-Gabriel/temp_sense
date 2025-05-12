#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

#define LM35_PIN 0  // ADC0 (GP26 en Raspberry Pi Pico)
#define VOLTAGE_REF 3.3f // Voltaje de referencia de la Pico
#define ADC_RESOLUTION (1 << 12) // 12 bits = 4096 niveles

int main() {
    stdio_init_all();
    sleep_ms(2000); // Espera a que el monitor serial se inicie

    adc_init();  // Inicializa el ADC
    adc_select_input(LM35_PIN);  // Selecciona la entrada ADC0 (GP26)

    while (1) {
        uint16_t raw = adc_read(); // Leer valor del ADC (0 - 4095)
        float voltage = (raw * VOLTAGE_REF*10) / ADC_RESOLUTION; // Convertir a voltaje
        float temperature = voltage * 100; // Convertir voltaje a temperatura (10mV/°C)

        // Imprimir valores en el Monitor Serial
        printf("Raw ADC: %d, Voltage: %.3fV, Temperature: %.2f°C\n", raw, voltage, temperature);
        fflush(stdout); // Forzar impresión inmediata

        sleep_ms(1000); // Espera 1 segundo antes de la siguiente lectura
    }
}

