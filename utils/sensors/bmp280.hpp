#ifndef BMP280_HPP
#define BMP280_HPP

#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#ifdef __cplusplus
extern "C" {
#endif

class bmp280 {
public:
    bmp280();
    bool begin(uint8_t addr = 0x77, uint8_t chipid = 0x58); 
    void bmp280_init(); 
    float readPressure(); 
    float readTemperature(); 
    float readAltitude(float seaLevelhPa = 1013.25); 
};

#ifdef __cplusplus
}
#endif

#endif 