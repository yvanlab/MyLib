
#include "WifiManager.h"

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

  char temp[400];

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
  message += "<label>SSID:</label><input name='ssid' test length=32 value=\""+String(basesmManager->m_ssid) +"\"><br>";
  message += "<label>Pass:</label><input name='pass' length=64 value=\""+String(HIDDEN_KEY) +"\"><br>";
  message += "<label>PrivateKey:</label><input name='privateKey' length=64 value=\""+String(HIDDEN_KEY) +"\"><br>";
  message += "<label>PublicKey:</label><input name='publicKey' length=64 value=\""+String(basesmManager->m_publicKey) +"\"><br>";
  message += "<input type='submit'></form>";
  message += "</body></html>";

  server->send ( 200, "text/html", message );

  //digitalWrite ( pinLed, HIGH );

}

void WifiManager::setCredential(){
  String str = server->arg("ssid");
  if (str.length()>0)
    strcpy(basesmManager->m_ssid, str.c_str());
  str = server->arg("pass");
  if (str.length()>0 && str != HIDDEN_KEY)
    strcpy(basesmManager->m_password,str.c_str());
  str = server->arg("privateKey");
  if (str.length()>0 && str != HIDDEN_KEY)
      strcpy(basesmManager->m_privateKey,str.c_str());
  str = server->arg("publicKey");
  if (str.length()>0)
      strcpy(basesmManager->m_publicKey,str.c_str());
  server->send ( 200, "text/html", "data recorded.restart board");
  basesmManager->writeData();
  restartESP();
}

void WifiManager::clearMemory(){
  basesmManager->clearData();
  server->send ( 200, "text/html", "ok");
}


WifiManager::WifiManager(unsigned char pinLed, ESP8266WebServer *_server, BaseSettingManager *_smManager) : BaseManager(pinLed){
  server = _server;
  basesmManager = _smManager;
}


wl_status_t WifiManager::begin(char *ssid, char *pass,
  IPAddress ip, const char *MODULE_NAME, const char *MODULE_MDNS, const char *MODULE_MDNS_AP){
  wl_status_t connection = connectSSID(ssid,pass,ip, MODULE_MDNS );
  if (connection==WL_CONNECTED) {
    Serial.println("connected");
    setStatus(WiFi.status(), "ssid");
    /*server->on ( "/", dataSummaryPage );
    server->onNotFound ( dataSummaryPage );*/
    //hrManager.begin("pool.ntp.org", 1, true);
  } else {
    Serial.println("Not connected");  
    connectAP(MODULE_MDNS_AP); // std::bind(&myClass::handleRoot, this)
    setStatus(WiFi.status(), "ap");
    server->on ( "/", std::bind(&WifiManager::displayCredentialCollection, this) );
    server->onNotFound ( std::bind(&WifiManager::displayCredentialCollection, this) );
  }

  WiFi.softAP(MODULE_MDNS);
  MDNS.begin (MODULE_MDNS);
  MDNS.addService("http", "tcp", 80);

  #ifdef MCPOC_TELNET
  MDNS.addService("telnet", "tcp", 23); // Telnet server RemoteDebug
  #endif

  WiFi.hostname(MODULE_NAME);
  server->on ( "/clear", std::bind(&WifiManager::clearMemory, this) );
  server->on ( "/restart", std::bind(&WifiManager::restartESP, this) );
  server->on ( "/set", std::bind(&WifiManager::setCredential, this) );
  server->on ( "/credential", std::bind(&WifiManager::displayCredentialCollection, this) );

  httpUpdater.setup(server, ((const char *)"/firmware"), MODULE_UPDATE_LOGIN, MODULE_UPDATE_PASS);

  server->begin();
  return connection;
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
  /*WiFi.softAP(MDNS_LABEL);
  MDNS.begin ( MDNS_LABEL);//, WiFi.softAPIP() );
  MDNS.addService("http", "tcp", 80);*/
  return WiFi.status();
}
