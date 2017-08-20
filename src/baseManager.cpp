

#include "BaseManager.h"

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

BaseManager::BaseManager(unsigned char pinLed){
  m_pinLed = pinLed;
  m_changed = true;
  pinMode ( m_pinLed, OUTPUT );
}

void BaseManager::switchOn(){
  digitalWrite ( m_pinLed, LOW );
}
void BaseManager::switchOff(){
  digitalWrite ( m_pinLed, HIGH );
}

/*
{
"nom" : "class name",
"code" : "10",
"description" : "blabla"
},
*/

String BaseManager::log(boolean bJson = STD_TEXT){
  if (bJson==JSON_TEXT)
    return "{\"nom\":\""+getClassName()+"\",\"code\":\"" + String(m_codeStatus) +"\",\"description\":\""+m_description+"\"}";
  else {
    return getClassName()+ "[" + String(m_codeStatus) + "]:" + m_description;
  }
}
