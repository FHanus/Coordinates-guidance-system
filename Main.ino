#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
 
#include "index.h" 
 
#define LED0 2
#define LED1 26
#define LED2 25
 
// Údaje k AP
const char* ssid = "ESP";
const char* password = "123456789";
 
WebServer server(80);

//===============================================================
// Proměnné (Pro pozdější testování)
//===============================================================

int X1 = NULL;

 
//===============================================================
// Ovládání stránky
//===============================================================

// Zde bude později odkaz na algoritmus pro získání souřadnic, pro teď pouze náhodná hodnota X
void Coord()
{             
  X1 = random(300);
}

// Načte HTML hodnoty stránky
void handleRoot() 
{
 String s = MAIN_page; 
 // Pošle webovou stránku serveru
 server.send(200, "text/html", s); 
}
 
void handleValues()
{
 Coord();
 String X1value = String(X1);
 // Pošle hodnotu X na ajax požadavek
 server.send(200, "text/plane", X1value); 
}
 
void handleLED() {
 String led0State = "OFF";
 String led1State = "OFF";
 String led2State = "OFF";

 // Odkazuje na xhttp.open("GET", "setLED?LEDstate="+led, true); v index.h
 String t_state = server.arg("LEDstate"); 
 Serial.println(t_state);

 // Ovládání LED
 if(t_state == "0") // START BUTTON
 {
  digitalWrite(LED0,HIGH); 
  digitalWrite(LED1,LOW);
  led0State = "ON";
  led1State = "OFF";
 }
 if(t_state == "1") // PAUSE BUTTON
 {
  digitalWrite(LED0,LOW); 
  digitalWrite(LED1,HIGH); 
  led0State = "OFF";
  led1State = "ON";   
 }
 if(t_state == "2") // RESET BUTTON ///// POZDĚJI I FUNKCE RESET, SMAŽE HODNOTY SOUŘADNIC, bude třeba ji přesunout na stránce dolů a zmenšit, či nejdříve odemknout a poté mazat. Pro testování zůstane zatím takto. 
 {
  digitalWrite(LED0,LOW); 
  digitalWrite(LED1,LOW);
  digitalWrite(LED2,HIGH); 
  led0State = "OFF";
  led1State = "OFF"; 
  led2State = "ON"; 
 }
 // Pošle webovou stránku serveru (Ano, podruhé..?)
 server.send(200, "text/plane", led0State);
 server.send(200, "text/plane", led1State); 
 server.send(200, "text/plane", led2State);  
}

//==============================================================
// Setup
//==============================================================

void setup(void){
  Serial.begin(115200);

  WiFi.mode(WIFI_AP); 
  WiFi.softAP(ssid, password);
 
  pinMode(LED0,OUTPUT); 
  pinMode(LED1,OUTPUT); 
  pinMode(LED2,OUTPUT); 
  
  Serial.println("Connecting to ");
  Serial.print(ssid);
 
    
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
 
  server.on("/", handleRoot);      
  server.on("/setLED", handleLED);
  server.on("/readValues", handleValues);
 
  server.begin();                  
  Serial.println("HTTP server started");
}

//==============================================================
// Loop
//==============================================================

void loop(void)
{
  server.handleClient();       
}
