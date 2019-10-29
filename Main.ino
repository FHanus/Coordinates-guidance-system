#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
 
#include "index.h" //Our HTML webpage contents with javascripts
 
#define LED 2  //On board LED
 
//SSID and Password of your WiFi router
const char* ssid = "ESP";
const char* password = "123456789";
 
WebServer server(80); //Server on port 80

//===============================================================
// Declare variables
//===============================================================

int X1 = NULL;

 
//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================

void Coord(){
  X1 = random(300);
}

void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}
 
void handleValues() {
 Coord();
 String X1value = String(X1);
 Serial.print(X1);
 server.send(200, "text/plane", X1value); //Send ADC value only to client ajax request
}
 
void handleLED() {
 String ledState = "OFF";
 String t_state = server.arg("LEDstate"); //Refer  xhttp.open("GET", "setLED?LEDstate="+led, true);
 Serial.println(t_state);
 if(t_state == "1")
 {
  digitalWrite(LED,LOW); //LED ON
  ledState = "ON"; //Feedback parameter
 }
 else
 {
  digitalWrite(LED,HIGH); //LED OFF
  ledState = "OFF"; //Feedback parameter  
 }
 
 server.send(200, "text/plane", ledState); //Send web page
}
//==============================================================
//                  SETUP
//==============================================================
void setup(void){
  Serial.begin(115200);
  
  //ESP32 As access point
  WiFi.mode(WIFI_AP); //Access Point mode
  WiFi.softAP(ssid, password);
 
  //Onboard LED port Direction output
  pinMode(LED,OUTPUT); 
  
  Serial.println("Connecting to ");
  Serial.print(ssid);
 
    
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
 
  server.on("/", handleRoot);      //Which routine to handle at root location. This is display page
  server.on("/setLED", handleLED);
  server.on("/readValues", handleValues);
 
  server.begin();                  //Start server
  Serial.println("HTTP server started");
}
//==============================================================
//                     LOOP
//==============================================================
void loop(void){
  server.handleClient();          //Handle client requests
}
