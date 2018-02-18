
#include "ADCBase.h"

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif



ADCBase::ADCBase(uint8_t pinLed, ADS1115 *adc, uint8_t address)
  : SensorBase(pinLed) {
  m_adc = adc;
  m_address = address;


}


float ADCBase::readAnalog() {
  float value = 0;
  #ifdef MCPOC_MOCK
  value = random(65534);
  //DEBUGLOGF("readCapteurs MOCK: %d\n", value);
  #else

  m_adc->triggerConversion();
  //value =  m_adc->getConversionP0N3();
  //value =  m_adc->getConversion(true);

  value =  m_adc->getMilliVolts(true);
  //DEBUGLOGF("readCapteurs : %d\n", value);

  #endif

  return value;

}
