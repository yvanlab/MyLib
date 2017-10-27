
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

wl_status_t WifiManager::begin(char *ssid, char *pass) {
  if (strlen(ssid)==0) {
      if (!WiFi.SSID()) return WL_NO_SSID_AVAIL;
      Serial.println ( "Quick" );
      ETS_UART_INTR_DISABLE();
      wifi_station_disconnect();
      ETS_UART_INTR_ENABLE();
      WiFi.begin();
  } else {
    Serial.println ( "SSID" );
    WiFi.begin ( ssid, pass );
  }
  unsigned char inbTest = 0;
  // Wait for connection
  while ( WiFi.status() != WL_CONNECTED && inbTest < 20) {
      delay ( 500 );
      Serial.print ( "." );
      Serial.print (WiFi.status());
      inbTest++;
  }
  return WiFi.status();
}

wl_status_t WifiManager::connectSSID(char *ssid, char *pass, IPAddress ip, const char *MDNS_LABEL){
  if (!ssid[0] || !pass[0])
    return WL_NO_SSID_AVAIL;


  IPAddress gateway(192,168,0,254);          // IP address of the router
  IPAddress subnet(255,255,255,0);
  WiFi.config(ip, gateway, subnet);
  Serial.println ( "" );
  switchOn();
  if (begin ((char*)"",(char*)"") != WL_CONNECTED)
    begin ( ssid, pass );
  switchOff();

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
