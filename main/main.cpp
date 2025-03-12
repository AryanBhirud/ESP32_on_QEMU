#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "bmp280.hpp"

extern "C" void app_main() {
    bmp280 bmp;

    if (!bmp.begin()) {
        printf("Failed to initialize BMP280\n");
        return;
    }
    printf("BMP280 Ready!\n");

    while (1) {
        float temperature = bmp.readTemperature();
        printf("Temperature = %.2f *C\n", temperature);

        float pressure = bmp.readPressure();
        printf("Pressure = %.2f hPa\n", pressure);

        float altitude = bmp.readAltitude();
        printf("Altitude = %.2f m\n", altitude);

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}