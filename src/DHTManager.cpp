
#include "DHTManager.h"

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <DHT.h>

DHTManager::DHTManager( unsigned char pinDHT,unsigned char pinLed)
  : BaseManager(pinLed) {
  //m_pinDHT=pinDHT;
  setup(pinDHT,DHT::AUTO_DETECT);
}


String DHTManager::toString(boolean bJson = STD_TEXT) {
  if (bJson==JSON_TEXT)
    return  "\"dhtTemp\":\""+String (getLastTemperature()) +
            "\", \"dhtTempTrend\":\"" + String(getTemperatureTrend())+"\""+
            ", \"dhtHum\":\"" + String(getLastHumidity())+"\""+
            ", \"dhtHumTrend\":\"" + String(getHumidityTrend())+"\""+
            ", \"dhtStatus\":\"" + getStatusString() +"\"";// - Status ["+getStatusString()+"]";
  else
    return "Temperature["+String (getLastTemperature()) + "][" +String(getTemperatureTrend()) + "] - Humidity[" + String(getLastHumidity())+"][" +String(getHumidityTrend()) +"] - Status ["+getStatusString()+"]";
}

float DHTManager::mesureTemperature(){
  switchOn();
  #if defined(MCPOC_MOCK)
  float res = random(40);
  setStatus( getStatus(),"mocking");
  #else
  float res = DHT::getTemperature();
  setStatus( getStatus(),getStatusString());
  #endif

  m_Temperature.mesure(res);
  switchOff();
  return res;

}


float DHTManager::getTemperature() {
  if (m_Temperature.m_nbreMeasure == 0) mesureTemperature();
  m_Temperature.set();
  return m_Temperature.m_value;
}




float DHTManager::mesureHumidity(){
  switchOn();
  #if defined(MCPOC_MOCK)
  float res = random(100);
  setStatus( getStatus(),"mocking");
  #else
  float res = DHT::getHumidity();
  setStatus( getStatus(),getStatusString());
  #endif

  m_Humidity.mesure(res);
  switchOff();
  return res;
}

float DHTManager::getHumidity(){
  if (m_Humidity.m_nbreMeasure == 0) mesureHumidity();
  m_Humidity.set();
  return m_Humidity.m_value;
}
