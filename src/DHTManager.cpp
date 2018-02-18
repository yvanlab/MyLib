
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
  DHT::setup(pinDHT,DHT::AUTO_DETECT);
}


String DHTManager::toString(boolean bJson = STD_TEXT) {
  if (bJson==JSON_TEXT)
    return  "\"dhtTemp\":\""+String (getTemperature()) +
            "\", \"dhtTempTrend\":\"" + String(getTemperatureTrend())+"\""+
            ", \"dhtHum\":\"" + String(getHumidity())+"\""+
            ", \"dhtHumTrend\":\"" + String(getHumidityTrend())+"\""+
            ", \"dhtStatus\":\"" + getStatusString() +"\"";// - Status ["+getStatusString()+"]";
  else
    return "Temperature["+String (getTemperature()) + "][" +String(getTemperatureTrend()) + "] - Humidity[" + String(getHumidity())+"][" +String(getHumidityTrend()) +"] - Status ["+getStatusString()+"]";
}

float DHTManager::getTemperature() {
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

float DHTManager::getHumidity(){
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
