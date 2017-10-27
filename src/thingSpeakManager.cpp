
#include "thingSpeakManager.h"

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "BaseManager.h"

thingSpeakManager::thingSpeakManager( unsigned char pinLed) : BaseManager(pinLed)  {
  m_index  = 0;
  ThingSpeak.begin(m_client,"api.thingspeak.com", 80);
}

void thingSpeakManager::addVariable(uint8_t index, String value) {
  m_variables[m_index].Index=index;
  m_variables[m_index].Value=value;
  m_index++;
}

unsigned char thingSpeakManager::sendIoT(String privateKey/*ChannelNumber*/, String publicKey /*WriteAPIKey*/) {
  switchOn();

  uint8_t i = 0;
  while (i < m_index) {
    ThingSpeak.setField(m_variables[i].Index,m_variables[i].Value);
    //DEBUGLOGF(" %d : indes:%d variable:%s\n",i, m_variables[i].Index,m_variables[i].Value.c_str() );
    i++;
  }

  m_index = 0;
  //DEBUGLOGF("private:%d public:%s\n",atol(privateKey.c_str()),publicKey.c_str() );
  ThingSpeak.writeFields(atol(privateKey.c_str()), publicKey.c_str());
  switchOff();
  return 0;
}

String thingSpeakManager::toString(boolean bJson = false) {
  String res = "variables :";
  unsigned char i=0;
  while (i < m_index) {
    res += "\""+String(m_variables[i].Index) + "\" : \"" + String(m_variables[i].Value+"\"");
    i++;
  }
  return res;
}
