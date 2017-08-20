
#include "WifiManager.h"

//#include <WiFiClient.h>


#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


WifiManager::WifiManager(unsigned char pinLed) : BaseManager(pinLed){

  }

String WifiManager::toString(boolean bJson = STD_TEXT){
  return "Mode["+String(WiFi.getMode())+\
  "] SSID["+WiFi.SSID()+\
  "] LocalIP["+WiFi.localIP().toString()+\
  "] softIP[" + WiFi.softAPIP().toString() + \
  "] status[" + String(WiFi.status(),DEC) + "]" ;
}



unsigned char WifiManager::connectSSID(char *ssid, char *pass, IPAddress ip, const char *MDNS_LABEL){
  if (!ssid[0] || !pass[0])
    return WL_NO_SSID_AVAIL;

    //IPAddress ip(VMC_METEO_IP);               // desired static IP address
    IPAddress gateway(192,168,0,254);          // IP address of the router
    IPAddress subnet(255,255,255,0);
    WiFi.config(ip, gateway, subnet);

  WiFi.begin ( ssid, pass );
  unsigned char inbTest = 0;
  // Wait for connection
  while ( WiFi.status() != WL_CONNECTED && inbTest < 20) {
    switchOn();
    delay ( 500 );
    Serial.print ( "." );
    Serial.print (WiFi.status());
    inbTest++;
    switchOff();
  }

  WiFi.softAP(MDNS_LABEL);
  MDNS.begin (MDNS_LABEL);
  MDNS.addService("http", "tcp", 80);

  setStatus(WiFi.status(), "ssid");
  return WiFi.status();
}

unsigned char WifiManager::connectAP(const char *MDNS_LABEL){
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  WiFi.softAP(MDNS_LABEL);
  MDNS.begin ( MDNS_LABEL);//, WiFi.softAPIP() );
  MDNS.addService("http", "tcp", 80);
  setStatus(WiFi.status(), "ap");
  return WiFi.status();
}
