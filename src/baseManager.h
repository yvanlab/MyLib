

#ifndef BaseManager_h
#define BaseManager_h

#if defined(ARDUINO) && ARDUINO >= 100

#include "Arduino.h"

#else

#include "WProgram.h"

#endif

#include <TimeLib.h>

#include "ylabconfig.h"

#ifdef MCPOC_TELNET
#include "RemoteDebug.h"
extern RemoteDebug Debug;
#endif

#define JSON_TEXT true
#define STD_TEXT false

#define STATUS_PERIPHERIC_DOWN 0
#define STATUS_PERIPHERIC_PARTIAL 1
#define STATUS_PERIPHERIC_WORKING 2

#ifdef MCPOC_TELNET
#define DBG_PORT Debug
#else
#define DBG_PORT Serial
#endif

#ifdef MCPOC_TEST
#define DEBUGLOG(...) DBG_PORT.println(__VA_ARGS__)
#define DEBUGLOGF(...) DBG_PORT.printf(__VA_ARGS__)
#else
#define DEBUGLOG(...)
#define DEBUGLOGF(...)
#endif

class capteurValue {
public:
  capteurValue(){}

  void set(float value) {
    if (m_time==0) m_trend = 0 ;
    else m_trend = (100*(value - m_value))( millis() - m_time);
    m_time  = millis();
    m_value = value;
  }

  uint32_t m_time = 0;
  float m_value = 0;
  float m_trend = 0;
};

class BaseManager
{
  public:
    BaseManager(unsigned char pinLed);
    void switchOn();
    void switchOff();
    void setStatus(unsigned char codeStatus, String description) {
       setStatus(now(), codeStatus,description); }
    void setStatus(unsigned long timeStampStatus, unsigned char codeStatus, String description) {
        m_timeStampStatus = timeStampStatus; m_changed = m_changed || m_codeStatus != codeStatus || m_description != description;
        m_codeStatus = codeStatus; m_description = description; }
    boolean  newLog() {return m_changed;}
    void clearLog() {m_changed = false;};

    virtual String toString(boolean bJson){return "";}
    String log(boolean bJson);
    virtual String getClassName(){ return "BaseManager";}
    unsigned long getLastUpdate(){ return m_timeStampStatus;}
  private:
    unsigned char m_pinLed;
    unsigned long m_timeStampStatus;
    unsigned char m_codeStatus;
    String m_description;
    boolean m_changed;
  };

#endif
