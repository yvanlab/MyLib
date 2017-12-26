

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
    uint8_t writeEEPROM(int16_t value);
    uint8_t writeEEPROM(char *str);
    char* readEEPROM(char *str,uint8_t maxChar);
    int16_t readEEPROM();
    uint8_t m_version = 0;
  private:
    int m_iEEprom = 0;


};

#endif
