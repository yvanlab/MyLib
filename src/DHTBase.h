

#ifndef DHTBase_h
#define DHTBase_h

#if defined(ARDUINO) && ARDUINO >= 100

#include "Arduino.h"

#else

#include "WProgram.h"

#endif
//#include "BaseManager.h"

#include "SensorBase.h"

#include <DHT.h>

class DHTBase : public SensorBase
{

  public:
    DHT * m_DHT;

    DHTBase() : SensorBase() {;};
    DHTBase(uint8_t pinLed,DHT *dht):SensorBase(pinLed){
      //m_pinDHT = pinLed;
      m_DHT = dht;
    };

    void setup(uint8_t pinLed,DHT *dht) {
      m_DHT = dht;
      SensorBase::setup(pinLed);
    }
    uint8_t getStatus() { return m_DHT->getStatus(); };

};

#endif
