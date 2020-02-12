// Načtení stánky při F5
void handleRoot() {
 String s = MAIN_page; 
 // Pošle webovou stránku serveru
 server.send(200, "text/html", s); 
}
// Obstarávání ajax kódu pro načítání do tabulky, načtení všech souřadnic do jednoho stringu
void handlevalues() {
  message = (String(strd[0][0]) + "," + String(strd[0][1])); 
  for(int i=1; i<13;i++){
    for(int d=0; d<2;d++){
      if((strd[i][d])!=0){
        mest = String(strd[i][d]);         
      }
      else{
        mest = ("N/A"); 
      } 
      message = (message + "," + mest); 
    }
  }
  server.send(200, "text/plane", message); 
}
// Obstarání všech tlačítek (START/PAUSE + Manuál)
void handleLED() {
 String led0State = "OFF";
 String led1State = "OFF";

 // Odkazuje na xhttp.open("GET", "setLED?LEDstate="+led, true); v index.h
 String t_state = server.arg("LEDstate"); 
 // START
 if(t_state == "0"){
    led0State = "ON";
    led1State = "OFF";
    valG = 1;
    valB = 0;
    digitalWrite(ledPinG, valG);
    digitalWrite(ledPinB, valB);   
    poradnikMan=1;
    runM=0;
    runallowed = true;
 }
 // PAUSE
 if(t_state == "1"){
    led0State = "OFF";
    led1State = "ON";
    valG = 0;
    valB = 1; 


    RunToLastPos=1; 

    oldPos[0]=Xaxis.currentPosition();
    oldPos[1]=Yaxis1.currentPosition();


    runM=0;
    poradnikMan=1;
    digitalWrite(ledPinG, valG);
    digitalWrite(ledPinB, valB);
    runallowed = false;  
 }
 // Jednotlivé směry při manuálu
 if(t_state == "2"){
   KrokMan = "Yp";
 }
 if(t_state == "3"){
    KrokMan = "Xm";
 }
 if(t_state == "4"){
   KrokMan = "S";
 }
 if(t_state == "5"){
    KrokMan = "Xp";
 }
 if(t_state == "6"){
    KrokMan = "Ym";
 }

 // Pošle webovou stránku serveru
 server.send(200, "text/plane", led0State);
 server.send(200, "text/plane", led1State);  
}
// Obstarávání formu pro načítání požadovaných hodnot z html form
void handleForm() { 
 desiredPos = server.arg("position"); 
 runM = 1;

 server.sendHeader("Location", "/");
 server.send(302, "text/plain", "Updated-- Press Back Button"); 	
}
