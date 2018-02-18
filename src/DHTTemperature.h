

#ifndef DHTTemperature_h
#define DHTTemperature_h

#if defined(ARDUINO) && ARDUINO >= 100

#include "Arduino.h"

#else

#include "WProgram.h"

#endif
//#include "BaseManager.h"

#include "DHTBase.h"

#include <DHT.h>

class DHTTemperature : public DHTBase
{

  public:

    DHTTemperature() : DHTBase() {;};
    DHTTemperature(uint8_t pinLed,DHT *dht):DHTBase(pinLed,dht){
    ;
    };

    float mesure(){
      switchOn();
      #if defined(MCPOC_MOCK)
      float res = random(40);
      setStatus( getStatus(),"mocking");
      #else
      float res = m_DHT->getTemperature();
      setStatus( m_DHT->getStatus(),m_DHT->getStatusString());
      #endif

      m_capteurValue.mesure(res);
      DEBUGLOGF("DHT Temperature : %d\n", (int)res );
      switchOff();
      return res;
    }

    String getClassName(){return "DHTTemperature";}


};

#endif
