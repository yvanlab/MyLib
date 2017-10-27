

#ifndef HourManager_h
#define HourManager_h

#if defined(ARDUINO) && ARDUINO >= 100

#include "Arduino.h"

#else

#include "WProgram.h"

#endif

#include <NtpClientLib.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266WiFiType.h>

#include <Wire.h>
//#include <RTClib.h>
#include "BaseManager.h"

class HourManager : /*public NTPClient, */public BaseManager
{

  public:
    const unsigned char NTP_PACKET_SIZE = 48;
    const char* HM_NTP_SERVER_NAME = "time.nist.gov";

    HourManager(unsigned int localPort, unsigned char pinLed);
    bool begin(String ntpServerName, int timeOffset, bool daylight);
    String toDTString(boolean bJson);
    String toUTString();
    //static String toUTString(unsigned long epochMS);

    //unsigned long  getCurrentEpoch();
    boolean  isNextDay();

    String getClassName(){return "HourManager";}
  private:

    unsigned int m_localPort = 2390;      // local port to listen for UDP packets
    void NTPsyncEvent(NTPSyncEvent_t ntpEvent);
    void onWifiConnectonEvent(WiFiEventStationModeGotIP ipInfo);
    void onWifiDeConnectonEvent(WiFiEventStationModeGotIP ipInfo);


    /* IPAddress timeServerIP;

    byte m_packetBuffer[48];
    WiFiUDP m_udp;*/


    unsigned long m_epoch=0;
    unsigned long m_timeReference=0;
    unsigned char m_today=0;

  /*unsigned long sendNTPpacket(IPAddress& address);
    unsigned long readNTPDateHour();*/


};

#endif
