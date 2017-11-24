

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
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
extern "C" {
  #include "user_interface.h"
}
#endif
#include "BaseManager.h"
#include "BaseSettingManager.h"

class WifiManager  : public BaseManager
{
  public:

    WifiManager(const uint8 pinLed, ESP8266WebServer *_server, BaseSettingManager *_smManager);
    wl_status_t begin(char *ssid, char *pass,
      IPAddress ip, const char *MODULE_NAME, const char *MODULE_MDNS, const char *MODULE_MDNS_AP);
    String toString(boolean bJson);
    //unsigned char connectSSID();
    wl_status_t connectSSID(char *ssid, char *pass, IPAddress ip, const char *MDNS_LABEL);
    unsigned char connectAP(const char *MDNS_LABEL);

    String getClassName(){return "WifiManager";}

    void restartESP();
    void displayCredentialCollection();
    void setCredential();
    void clearMemory();

  private:
    wl_status_t connecting(char *ssid, char *pass);
    ESP8266WebServer *server;
    ESP8266HTTPUpdateServer httpUpdater;
    BaseSettingManager *basesmManager;

};

#endif
