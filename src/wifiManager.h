

#ifndef WifiManager_h
#define WifiManager_h

#if defined(ARDUINO) && ARDUINO >= 100

#include "Arduino.h"

#else

#include "WProgram.h"

#endif

#ifdef ESP32
#include <WiFi.h>
#include <ESPmDNS.h>
#else
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
extern "C" {
  #include "user_interface.h"
}
#endif
#include "BaseManager.h"
class WifiManager  : public BaseManager
{
  public:

    WifiManager(unsigned char pinLed);
    String toString(boolean bJson);
    //unsigned char connectSSID();
    wl_status_t connectSSID(char *ssid, char *pass, IPAddress ip, const char *MDNS_LABEL);
    unsigned char connectAP(const char *MDNS_LABEL);

    String getClassName(){return "WifiManager";}

  private:
    wl_status_t begin(char *ssid, char *pass);


};

#endif
