

#ifndef BaseSettingManager_h
#define BaseSettingManager_h

#if defined(ARDUINO) && ARDUINO >= 100

#include "Arduino.h"

#else

#include "WProgram.h"

#endif

#include <EEPROM.h>
#include "BaseManager.h"

class BaseSettingManager : public BaseManager
{
  public:
    char m_ssid[32];
    char m_password[64];
    char m_privateKey[64];
    char m_publicKey[64];

    BaseSettingManager(unsigned char pinLed);
    String toString(boolean bJson);
    unsigned char readData();
    unsigned char writeData();
    unsigned char clearData();
    String getClassName(){return "BaseSettingManager";}
  protected:
    unsigned char writeEEPROM(char *str);
    unsigned char readEEPROM(char *str,uint8_t maxChar);
  private:
    int m_iEEprom = 0;
};

#endif
