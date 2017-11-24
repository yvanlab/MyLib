

#include "BaseSettingManager.h"

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

BaseSettingManager::BaseSettingManager(unsigned char pinLed) : BaseManager(pinLed){
  m_iEEprom = 0;
  EEPROM.begin(512);
}

String BaseSettingManager:: toString(boolean bJson = false){
  return "SSID[" + String(m_ssid) + "] PASS[" + m_password + "] privateKey[" + m_privateKey + "] publicKey[" + m_publicKey + "]";
}

unsigned char BaseSettingManager::readData(){
  switchOn();
  m_iEEprom=0;
  readEEPROM(m_ssid);
  readEEPROM(m_password);
  readEEPROM(m_privateKey);
  readEEPROM(m_publicKey);
  setStatus(millis(), m_iEEprom, "read");
  switchOff();
}
unsigned char BaseSettingManager::writeData(){
  switchOn();
  m_iEEprom=0;
  writeEEPROM(m_ssid);
  writeEEPROM(m_password);
  writeEEPROM(m_privateKey);
  writeEEPROM(m_publicKey);
  EEPROM.commit();
  setStatus( m_iEEprom, "written");
  switchOff();
}

unsigned char BaseSettingManager::clearData(){
  switchOn();
  for (int i = 0; i < 512; ++i) {
    EEPROM.write(i, 0);
  }
  EEPROM.commit();
  switchOff();
}

unsigned char BaseSettingManager::writeEEPROM(char *str){
  for (int iString = 0; str[iString] != 0; iString++,m_iEEprom++ )  {
    EEPROM.write(m_iEEprom, str[iString]);
    delay(50);
    //Serial.print(m_iEEprom);Serial.print(":");DEBUGLOG(str[iString]);
  }
  delay(50);
  EEPROM.write(m_iEEprom,0);
  //Serial.print(m_iEEprom);DEBUGLOG(":--");
  m_iEEprom++;
}

unsigned char BaseSettingManager::readEEPROM(char *str){
  int iString = 0;

  while (iString < 512) {
    str[iString] = EEPROM.read(m_iEEprom);
    //Serial.print(m_iEEprom);Serial.print(":");
    m_iEEprom++;
    if (str[iString] == 0) {
      //DEBUGLOG("--");
      break;
    }/*else {
      DEBUGLOG(str[iString]);
    }*/
    iString++;
    delay(50);
  }

}
