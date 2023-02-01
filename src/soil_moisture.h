#ifndef SOIL_MOISTURE_H
#define SOIL_MOISTURE_H

#include <Arduino.h>
#include "esp_adc_cal.h"

class Soil_Moisture
{
  private:
    #define FILTER_LEN 10
    uint32_t analogFilterBuff[FILTER_LEN] = {0};
    uint8_t counter = 0;
    uint8_t sensorPowerPin;
    uint8_t sensorAnalogPin;

    /**
     * @brief 
     * 
     * @param ADC_Raw 
     * @return uint32_t 
     */
    uint32_t readADC_Avg(uint16_t ADC_Raw);

    /**
     * @brief 
     * 
     * @param ADC_Raw 
     * @return uint32_t 
     */
    uint32_t readADC_Cal(int ADC_Raw);

  public:
    /**
     * @brief 
     * 
     * @param analogPin 
     * @param powerPin 
     */
    void begin(uint8_t analogPin, uint8_t powerPin);

    /**
     * @brief 
     * 
     * @return uint16_t 
     */
    uint16_t readMoisture();
};

#endif