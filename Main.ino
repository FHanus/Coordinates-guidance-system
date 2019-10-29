#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
 
#include "index.h" 
 
#define LED 2 
 
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
void Coord(){             
  X1 = random(300);
}

// Načte HTML hodnoty stránky
void handleRoot() {
 String s = MAIN_page; 
 // Pošle webovou stránku serveru
 server.send(200, "text/html", s); 
}
 
void handleValues() {
 Coord();
 String X1value = String(X1);
 Serial.print(X1);
 // Pošle hodnotu X na ajax požadavek
 server.send(200, "text/plane", X1value); 
}
 
void handleLED() {
 String ledState = "OFF";

 // Odkazuje na xhttp.open("GET", "setLED?LEDstate="+led, true); v index.h
 String t_state = server.arg("LEDstate"); 
 Serial.println(t_state);

 // Ovládání LED
 if(t_state == "1")
 {
  digitalWrite(LED,LOW); 
  ledState = "ON"; 
 }
 else
 {
  digitalWrite(LED,HIGH); 
  ledState = "OFF";   
 }
 // Pošle webovou stránku serveru (Ano, podruhé..?)
 server.send(200, "text/plane", ledState); 
}
//==============================================================
// Setup
//==============================================================
void setup(void){
  Serial.begin(115200);

  WiFi.mode(WIFI_AP); 
  WiFi.softAP(ssid, password);
 
  pinMode(LED,OUTPUT); 
  
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
void loop(void){
  server.handleClient();       
}

