

#ifndef DHTManager_h
#define DHTManager_h

#if defined(ARDUINO) && ARDUINO >= 100

#include "Arduino.h"

#else

#include "WProgram.h"

#endif
#include <DHT.h>
#include "BaseManager.h"




class DHTManager : public DHT , public BaseManager
{

  public:


    DHTManager(unsigned char pinDHT,unsigned char pinLed);

    String toString(boolean bJson);

    float getTemperature();
    float getHumidity();
    float getHumidityTrend() {return m_Humidity.m_trend;};
    float getTemperatureTrend(){return m_Temperature.m_trend;};
    float getLastTemperature(){return m_Temperature.m_value;};
    float getLastHumidity(){return m_Humidity.m_value;};

    String getClassName(){return "DHTManager";}

  //private:
    //DHT  m_DHT;
    capteurValue  m_Humidity;
    capteurValue  m_Temperature;


    //int8_t read();

};

#endif
