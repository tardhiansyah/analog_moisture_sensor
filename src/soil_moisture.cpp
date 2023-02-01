#include "soil_moisture.h"

uint32_t Soil_Moisture::readADC_Cal(int ADC_Raw)
{
  esp_adc_cal_characteristics_t adc_chars;
  
  esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 1100, &adc_chars);
  return(esp_adc_cal_raw_to_voltage(ADC_Raw, &adc_chars));
}

uint32_t Soil_Moisture::readADC_Avg(uint16_t ADC_Raw)
{
  uint32_t sum = 0;

  analogFilterBuff[counter++] = ADC_Raw;

  if (counter == FILTER_LEN)
  {
    counter = 0;
  }

  for (uint8_t i = 0; i < FILTER_LEN; i++)
  {
    sum += analogFilterBuff[counter];
  }

  return (sum/FILTER_LEN);
}

void Soil_Moisture::begin(uint8_t analogPin, uint8_t powerPin)
{
  pinMode(analogPin, INPUT);
  pinMode(powerPin, OUTPUT);
  digitalWrite(powerPin, LOW);

  sensorAnalogPin = analogPin;
  sensorPowerPin = powerPin;
}

uint16_t Soil_Moisture::readMoisture()
{
  uint16_t analogRaw = analogRead(sensorAnalogPin);
  uint16_t analogFiltered = readADC_Avg(analogRaw);

  return analogFiltered;
}