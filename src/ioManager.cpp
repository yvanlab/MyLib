
#include "ioManager.h"

//#include <WiFiClient.h>


#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                                // use 8883 for SSL


/************ Global State (you don't need to change this!) ******************/


// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.



ioManager::ioManager( unsigned char pinLed) : BaseManager(pinLed)  {
  m_index  = 0;

}

void ioManager::addVariable(String name, String value) {
  m_variables[m_index].Name=name;
  m_variables[m_index].Value=value;
  m_index++;

}

unsigned char ioManager::sendKPIsToIO(String privateKey/*AIO_KEY*/, String publicKey /*AIO_USERNAME*/) {
  switchOn();

  Adafruit_MQTT_Client mqtt (&m_client, MQTT_SERVER, AIO_SERVERPORT,publicKey.c_str(),privateKey.c_str()) ;
  MQTT_connect(&mqtt);

  unsigned char i = 0;
  while (i < m_index) {
    String sPublishedVariabel = publicKey+"/feeds/"+m_variables[i].Name;

    int res = mqtt.publish(sPublishedVariabel.c_str(), m_variables[i].Value.c_str());
    i++;
  }
  m_index = 0;
  switchOff();
  return 0;
}

String ioManager::toString(boolean bJson = false) {

  //String res = "public key [" + m_publicKey +"] - Private key["+m_privateKey +"] " ;
  String res = "variables :";
  unsigned char i=0;
  while (i < m_index) {
    res += "\""+m_variables[i].Name + "\" : \"" + String(m_variables[i].Value+"\"");
    i++;
  }
  return res;

}

void ioManager::MQTT_connect(Adafruit_MQTT_Client *mqtt){

  if (mqtt->connected()) { return; }                     // Stop and return to Main Loop if already connected to Adafruit IO
  DEBUGLOG("Connecting to MQTT... ");

  uint8_t ret = mqtt->connect();//publicKey.c_str(),privateKey.c_str());//publicKey.c_str(),privateKey.c_str());
  if ( ret != 0 ) {
    DEBUGLOG(mqtt->connectErrorString(ret));
    setStatus(ret, mqtt->connectErrorString(ret));
    mqtt->disconnect();
  } else {
    DEBUGLOG("MQTT Connected!");
    setStatus(ret, "Connected");
    delay(500);
  }
}
