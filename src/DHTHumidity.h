

#ifndef DHTHumidity_h
#define DHTHumidity_h

#if defined(ARDUINO) && ARDUINO >= 100

#include "Arduino.h"

#else

#include "WProgram.h"

#endif
//#include "BaseManager.h"

#include "DHTBase.h"

#include <DHT.h>

class DHTHumidity : public DHTBase
{

  public:

    DHTHumidity() : DHTBase() {;};
    DHTHumidity(uint8_t pinLed,DHT *dht):DHTBase(pinLed,dht){

    };

    

    float mesure(){
      switchOn();
      #if defined(MCPOC_MOCK)
      float res = random(40);
      setStatus( getStatus(),"mocking");
      #else
      float res = m_DHT->getHumidity();
      setStatus( m_DHT->getStatus(),m_DHT->getStatusString());
      #endif

      m_capteurValue.mesure(res);
      DEBUGLOGF("DHT Humidity : %d\n", (int)res );
      switchOff();
      return res;
    }

    String getClassName(){return "DHTHumidity";}


};

#endif
