
#include "WifiManagerV2.h"

//#include <WiFiClient.h>
//#include "context.h"

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


void WifiManager::restartESP() {
  ESP.restart();
}

void WifiManager::displayCredentialCollection() {
	//digitalWrite ( pinLed, LOW );

  String message =  "<html>\
    <head>\
      <title>Credentials page</title>\
      <style>\
        body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
      </style>\
    </head>\
    <body>";
  message += "<p>";
  message +="<ul>";
  int n = WiFi.scanNetworks();
  for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      message += "<li>";
      message +=i + 1;
      message += ": ";
      message += WiFi.SSID(i);
      message += " (";
      message += WiFi.RSSI(i);
      message += ")";
      message += (WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*";
      message += "</li>";
    }
  message += "</ul>";
  message += "<form method='get' action='set'>";
  message += "<label>SSID:</label><input name='ssid' test length=32 value=\""+String(_basesmManager->m_ssid) +"\"><br>";
  message += "<label>Pass:</label><input name='pass' length=64 value=\""+String(HIDDEN_KEY) +"\"><br>";
  message += "<label>Channel number:</label><input name='privateKey' length=64 value=\""+String(HIDDEN_KEY) +"\"><br>";
  message += "<label>PublicKey:</label><input name='publicKey' length=64 value=\""+String(_basesmManager->m_publicKey) +"\"><br>";
  message += "<input type='submit'></form>";
  message += "</body></html>";

  _server->send ( 200, "text/html", message );

  //digitalWrite ( pinLed, HIGH );

}

void WifiManager::setCredential(){
  String str = _server->arg("ssid");
  if (str.length()>0)
    strcpy(_basesmManager->m_ssid, str.c_str());
  str = _server->arg("pass");
  if (str.length()>0 && str != HIDDEN_KEY)
    strcpy(_basesmManager->m_password,str.c_str());
  str = _server->arg("privateKey");
  if (str.length()>0 && str != HIDDEN_KEY)
      strcpy(_basesmManager->m_privateKey,str.c_str());
  str = _server->arg("publicKey");
  if (str.length()>0)
      strcpy(_basesmManager->m_publicKey,str.c_str());
  _server->send ( 200, "text/html", "data recorded.restart board");
  _basesmManager->writeData();
  restartESP();
}

void WifiManager::clearMemory(){
  _basesmManager->clearData();
  _server->send ( 200, "text/html", "data cleared");
}

void WifiManager::wifiReset(){
  _server->send ( 200, "text/html", "reseting...");
  WiFi.disconnect();
  restartESP();
}


WifiManager::WifiManager(unsigned char pinLed,  BaseSettingManager *smManager) : BaseManager(pinLed){
  _server = new ESP8266WebServer(80);
  _hrManager = new HourManager(2390,pinLed);
  _basesmManager = smManager;
}

wl_status_t WifiManager::begin( IPAddress ip, const char *MODULE_NAME, const char *MODULE_MDNS, const char *MODULE_MDNS_AP){
  wl_status_t connection = connectSSID(_basesmManager->m_ssid,_basesmManager->m_password,ip, MODULE_MDNS );
  if (connection==WL_CONNECTED) {
    Serial.println("connected");
    setStatus(WiFi.status(), "ssid");
    _hrManager->begin("pool.ntp.org", 1, true);
    #ifdef MCPOC_TEST
    WiFi.softAP(MODULE_MDNS,MODULE_AP_WPA);
    #else
    WiFi.softAP(MODULE_MDNS,MODULE_AP_WPA,1,true);
    #endif
  } else {
    Serial.println("Not connected");
    connectAP(MODULE_MDNS_AP);
    setStatus(WiFi.status(), "ap");
    WiFi.softAP(MODULE_MDNS_AP,MODULE_AP_WPA);
    _server->on ( "/", std::bind(&WifiManager::displayCredentialCollection, this) );
    _server->onNotFound ( std::bind(&WifiManager::displayCredentialCollection, this) );
  }


  MDNS.begin (MODULE_MDNS);
  MDNS.addService("http", "tcp", 80);

  #ifdef MCPOC_TELNET
  MDNS.addService("telnet", "tcp", 23); // Telnet server RemoteDebug
  #endif

  WiFi.hostname(MODULE_NAME);
  _server->on ( "/clear", std::bind(&WifiManager::clearMemory, this) );
  _server->on ( "/restart", std::bind(&WifiManager::restartESP, this) );
  _server->on ( "/set", std::bind(&WifiManager::setCredential, this) );
  _server->on ( "/credential", std::bind(&WifiManager::displayCredentialCollection, this) );
  _server->on ( "/reset", std::bind(&WifiManager::wifiReset, this) );

  _httpUpdater.setup(_server, ((const char *)"/firmware"), MODULE_UPDATE_LOGIN, MODULE_UPDATE_PASS);
  #ifdef OTA_FOR_ATOM
  setOTAForAtom();
  #endif

  _server->begin();
  return connection;
  }


void WifiManager::handleClient() {
  _server->handleClient();
  #ifdef MCPOC_TELNET
  Debug.handle();
  #endif
  #ifdef OTA_FOR_ATOM
  ArduinoOTA.handle();
  #endif

}



String WifiManager::toString(boolean bJson = STD_TEXT){
  return "Mode["+String(WiFi.getMode())+\
  "] SSID["+WiFi.SSID()+\
  "] LocalIP["+WiFi.localIP().toString()+\
  "] softIP[" + WiFi.softAPIP().toString() + \
  "] status[" + String(WiFi.status(),DEC) + "]" ;
}

wl_status_t WifiManager::connecting(char *ssid, char *pass) {
  if (strlen(ssid)==0) {
      if (!WiFi.SSID()) return WL_NO_SSID_AVAIL;
      Serial.println ( "Quick" );
      ETS_UART_INTR_DISABLE();
      wifi_station_disconnect();
      ETS_UART_INTR_ENABLE();
      WiFi.begin();
  } else {
    Serial.println ( "Long" );
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
  if (connecting ((char*)"",(char*)"") != WL_CONNECTED)
    connecting ( ssid, pass );
  switchOff();
  return WiFi.status();
}

unsigned char WifiManager::connectAP(const char *MDNS_LABEL){
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  return WiFi.status();
}

#ifdef OTA_FOR_ATOM
void WifiManager::setOTAForAtom() {
  Serial.println(F("ArduinoOTA conf"));
  ArduinoOTA.onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH) {
        type = "sketch";
      } else { // U_SPIFFS
        type = "filesystem";
      }

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      Serial.println("Start updating " + type);
    });
    ArduinoOTA.onEnd([]() {
      Serial.println("\nEnd");
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    });
    ArduinoOTA.onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) {
        Serial.println(F("Auth Failed"));
      } else if (error == OTA_BEGIN_ERROR) {
        Serial.println(F("Begin Failed"));
      } else if (error == OTA_CONNECT_ERROR) {
        Serial.println(F("Connect Failed"));
      } else if (error == OTA_RECEIVE_ERROR) {
        Serial.println(F("Receive Failed"));
      } else if (error == OTA_END_ERROR) {
        Serial.println(F("End Failed"));
      }
    });
    ArduinoOTA.begin();
    Serial.println(F("ArduinoOTA Ready"));
}
#endif
