
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
    return  "\"dhtTemp\":\""+String (getTemperature()) + "\", \"dhtHum\":\"" + String(getHumidity())+"\"";// - Status ["+getStatusString()+"]";
  else
    return "Temperature["+String (getTemperature()) + "] - Humidity[" + String(getHumidity())+"] - Status ["+getStatusString()+"]";
}

float DHTManager::getTemperature() {
  switchOn();
  float res = DHT::getTemperature();
  setStatus( getStatus(),getStatusString());
  switchOff();
  return res;
}

float DHTManager::getHumidity(){
  switchOn();
  float res = DHT::getHumidity();
  setStatus( getStatus(),getStatusString());
  switchOff();
  return res;
}
