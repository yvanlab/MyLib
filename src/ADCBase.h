

#ifndef ADCBase_h
#define ADCBase_h

#if defined(ARDUINO) && ARDUINO >= 100

#include "Arduino.h"

#else

#include "WProgram.h"

#endif
#include "BaseManager.h"

#include "sensorBase.h"

#include <ADS1115.h>

class ADCBase : public SensorBase
{

  public:
    ADS1115   *m_adc;
    uint8_t   m_address;

    ADCBase(uint8_t pinLed,ADS1115 *adc, uint8_t address=0);
    void setADCStatus() {
      if (m_adc->testConnection())
        setStatus(1,"OK");
      else
        setStatus(1,"KO");
    }


  protected:

    float readAnalog();


};

#endif
