#include "initOfVals.h"       // Zde inicializuji všechny proměnné.
#include "index.h"            // Zde inicializuji všechny proměnné.
#include "webFunctions.h"     // Zde definuji funkce pro chod webu

TaskHandle_t Task1;           // Inicializování jádra 0 (jednička se využívá pro LOOP, proto neinicializuji tu, ale kód pro core 1 píšu do loopu)

////   Setup funkce:  ////
void setup() {
  Serial.begin(115200);      

  // Server inicializace (že je AP, údaje pro připojení, IP adresa, funkce které web obstarává)
  WiFi.mode(WIFI_AP); 
  WiFi.softAP(ssid, password);    
  IPAddress IP = WiFi.softAPIP();

  server.on("/", handleRoot);      
  server.on("/setLED", handleLED);
  server.on("/readValues", handlevalues);
  server.on("/form", handleForm);

  server.begin();                  

  // Připnutí funkce k jádru 0 s prioritou 1
  xTaskCreatePinnedToCore(Task1code,"Task1",10000,NULL,1,&Task1,0);                       

  // Nastavení motorů pro AccelStepper
  Yaxis2.setPinsInverted(true,false,false);   // Pro upravení správného směru
  Xaxis.setPinsInverted(true,false,false); 

  Yaxis1.setMaxSpeed(5000);                   // Nastavení maximálních rychlostí
  Yaxis2.setMaxSpeed(5000);
  Xaxis.setMaxSpeed(7500);

  Yaxis1.setSpeed(2500);                      // Nastavení rychlostí
  Yaxis2.setSpeed(2500);
  Xaxis.setSpeed(2500);

  // Nastavení pinů koncových spínačů
  pinMode(koncak1, INPUT);              
  pinMode(koncak2, INPUT);
  pinMode(koncak3, INPUT);
  pinMode(koncak4, INPUT);

  // Piny pro tlacitka
  pinMode(buttonPinR, INPUT);
  pinMode(buttonPinG, INPUT);
  pinMode(buttonPinB, INPUT);

  pinMode(ledPinR, OUTPUT);
  pinMode(ledPinG, OUTPUT);
  pinMode(ledPinB, OUTPUT);

  // Nastavení pinu senzoru IR
  pinMode(senzor, INPUT);

  // Nastavení enable pinu pro blokování chodu motorů "enable" a jeho okamžité zapnutí pro blokaci náhodného chodu po startu.
  pinMode(enableY, OUTPUT);
  pinMode(enableX, OUTPUT);
  digitalWrite(enableY, HIGH);
  digitalWrite(enableX, HIGH);
}

#include "basicFunctions.h"   // Zde inicializuji všechny vedlejší vytvořené funkce.
#include "Routes.h"           // Zde inicializuji hlavní oběhovou funkci.

////   Hlavní loopy:   ////
void Task1code( void * pvParameters ){   // Task1 na nultém jádru - handle client obsatrá všechny výše inicializované funkce pro server 
  for(;;){
    server.handleClient(); 
    delay(10);                          // Delay zabrání moc ryhclému průchodu co vyústí ve zhroucení programu
  }
}
void loop(){
  basicRoute();                          // Task2 na prvním jádru, obstará output a input piny, běžný chod. Delay pro zabránění zhroucení při rychlém oběhu
  delayMicroseconds(25);
}
