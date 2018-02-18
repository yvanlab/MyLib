

#ifndef DHTManager_h
#define DHTManager_h

#if defined(ARDUINO) && ARDUINO >= 100

#include "Arduino.h"

#else

#include "WProgram.h"

#endif
#include <DHT.h>
#include <DHTHumidity.h>
#include <DHTTemperature.h>
//#include "BaseManager.h"




class DHTManagerV2 : public DHT , public SensorBase
{

  public:


    DHTManagerV2(uint8_t pinLed,uint8_t pinDHT) : SensorBase(pinDHT) {

      m_DHT.setup(pinDHT,DHT::AUTO_DETECT);
      m_Humidity.setup(pinLed, &m_DHT);//  = new DHTHumidity
      m_Temperature.setup(pinLed, &m_DHT);
    };

    String toString(boolean bJson)  {
      String res;
      if (bJson == JSON_TEXT) {
        res = "\"humidity\":{"+m_Humidity.toString(bJson)+"}," +
            "\"temperature\":{"+m_Temperature.toString(bJson)+"}";
      } else {
        res = "humidity : "+m_Humidity.toString(bJson)+" , temperature : "+m_Temperature.toString(bJson);
      }
      return res;
    };

    /*String log(boolean bJson) {

      return m_Humidity.log(bJson);
    }-*/

    float mesure() {
      m_Humidity.mesure();
      m_Temperature.mesure();
      setStatus( m_Humidity.getStatusCode(),m_Humidity.getStatusDescription());
    };

    void clear() {
        m_Humidity.clear();
        m_Temperature.clear();
    }

    DHTHumidity* getHumiditySensor() {return &m_Humidity;};
    DHTTemperature* getTemperatureSensor() {return &m_Temperature;};

    String getClassName(){return "DHTManagerV2";}

  //private:
    DHT  m_DHT;

    DHTHumidity     m_Humidity;
    DHTTemperature  m_Temperature;


    //int8_t read();

};

#endif
