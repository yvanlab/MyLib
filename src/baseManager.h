

#ifndef BaseManager_h
#define BaseManager_h

#if defined(ARDUINO) && ARDUINO >= 100

#include "Arduino.h"

#else

#include "WProgram.h"

#endif

#include <TimeLib.h>

#include "ylabconfig.h"

#define JSON_TEXT true
#define STD_TEXT false


#define DBG_PORT Serial

#ifdef MCPOC_TEST
#define DEBUGLOG(...) DBG_PORT.println(__VA_ARGS__)
#else
#define DEBUGLOG(...)
#endif


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
