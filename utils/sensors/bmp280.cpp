#include "bmp280.hpp"
#include <math.h>
#include <stdio.h>

static float time = 0.0;

bmp280::bmp280() {}

bool bmp280::begin(uint8_t addr, uint8_t chipid) {
    vTaskDelay(pdMS_TO_TICKS(200)); 
    return true;
}

void bmp280::bmp280_init() {
    printf("BMP280 Initialized\n");
}

float bmp280::readPressure() {
    float pressure = 1013.25 + 10 * sin(time);
    time += 0.1; 
    return pressure;
}

float bmp280::readTemperature() {
    float temperature = 25.0 + 5 * sin(time);
    return temperature;
}

float bmp280::readAltitude(float seaLevelhPa) {
    float altitude = 44330 * (1 - pow(readPressure() / seaLevelhPa, 0.1903));
    return altitude;
}