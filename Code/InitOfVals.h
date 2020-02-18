// Import knihoven
    #import <Arduino.h>           // Základní knihovna bez které programy nejdou programovat v MC Visual Studio Code. V arduino ide není třeba.
    #include <AccelStepper.h>     // Knihovna pro ovládání motorů, zkoušel jsem i bez, přidává ovšem více funkcí.
    #include <WiFi.h>             // Knihovny na web server
    #include <WiFiClient.h>
    #include <WebServer.h>

// Údaje k AP
    const char* ssid = "ESP-hanusfi16";
    const char* password = "dmp20202";
    WebServer server(80);

// Piny motorů
    AccelStepper Yaxis1(1, 2, 15);         //1. místo = to, že jde o driver, 2. místo = step pin , 3. místo = direction pin  5  4
    AccelStepper Yaxis2(1, 5, 4);           //1. místo = to, že jde o driver, 2. místo = step pin , 3. místo = direction pin  19 18
    AccelStepper Xaxis(1, 19, 18);           //1. místo = to, že jde o driver, 2. místo = step pin , 3. místo = direction pin  2  15

// Enable piny k motorum
    #define enableY 16                      // Pin vypínající motor Y
    #define enableX 23                      // Pin vypínající motor X

// Piny koncových spínačů
    #define koncak1 34 
    #define koncak2 35
    #define koncak3 32
    #define koncak4 33

// Pin IRs
    #define senzor 21

// Hodnoty čistě pro testovací využití. Naměřené funkcí measureMax();
    long maxY = 26111;                              
    long maxX = 28886;

// Ochranná proměnná pro využití s tlačítky
    bool runallowed = false;

// Jak jemně krokuje (1000=1cm)
    int grid = 3000;  

// Směr krokování
    int smerX = 1;
    int smerMerCh = 1;

// Offsety umožňující správné najíždění v případě nerovnoměrného senzoru (IR)
    int offsetX = 0; 
    int offsetY = -1250; //upraveno z:-1100 

// Kombinační proměnné pro počítání středů
    int merX[2] = {0,0};                    //Pro uložení první a druhé souřadnice hran na jednotlivých osách          
    int merY[2] = {0,0};
    int lastPosSynch[2] = {0,0};            // Pro uložení pozice při přechodu do hledání chladiče
    int lastPos[2]={0,0};                   // Pro uložení pozice při přechodu do měření středu, pro následující návrat kde se skoncilo v oběhu
    int lastPosWD[2]={0,0};                 // Pro uložení poslední pozice kdy byl ještě otvor při měření středu

    int mathValX = 0;                       // Pro výpočty středů na jednotlivých osách
    int mathValY = 0;
    
    bool PovMereni = 1;                        // Jestli bylo povoleno měření (jestli je chladič správně umístěn, nebo není)

// Proměnné středů
    int strdporadi = 1;                                                                                      // Pořadí aktuálně měřeného středu. 1 protože 0 se jede mimo tento oběh a je to střed chladiče.
    int strd[13][2] = {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}};       // Inicializace pole s hodnotami středů
    String message = "Test";                                                                                 // Message je string zobrazovaný na webu v tabulce středů
    String mest;                                                                                             // Pomocná proměnná při načítání do stringu message
    
// Sekvenční proměnné pro měření
    int poradnik = 0;           // Sekvenční proměnná pro chod: inicializace/měření chladiče/vyhledávání středů/měření středů
    int phase = 0;              // S. proměnná pro rozkouskování měření středů
    int phase2 = 0;             // S. proměnná pro rozkouskování měření chladiče
    int phase3 = 0;             // S. proměnná pro rozkouskování vyhledávání děr 

// Proměnné časování
    unsigned long previousMillis = 0;
    unsigned long previousMillisS = 0;          
    unsigned long previousMicrosMain = 0;

// Proměnné pro chod tlačítek
    const int buttonPinG = 27;                      // Tlačítka
    const int buttonPinB = 26; 
    const int buttonPinR = 25; 

    const int ledPinG = 13;                         // Led tlačítek  
    const int ledPinB = 12; 
    const int ledPinR = 14; 

    boolean valG = 0;                               // Hodnoty virtuálních set/reset proměnných ovládaných web/hardware
    boolean valB = 1;
    boolean valR = 1;

    boolean buttonStateG = 0;                       // Aktuální hodnoty set/reset tlačítek pro porovnávání s poslední hodnotou
    boolean buttonStateB = 1;
    boolean buttonStateR = 0;

    boolean lastButtonStateG = 0;                   // Minulé hodnoty set/reset tlačítek pro porovnávání s poslední hodnotou
    boolean lastButtonStateB = 0;
    boolean lastButtonStateR = 0;

    int reset_count = 0;                            // Počítadlo pro hezké blikání resetu
    int unsigned long previousMillisTimer = 0;      // Další stopky

    bool RunToLastPos = 0;                          // Jestli má nebo nemá být najížděna poslední hodnota (Při přepnutí z pause na run pokud byl udělán nějaký krok manuálem)     

    String oldt_state;    

// Proměnné pro chod manuálu
    String desiredPos;                  // Načtení požaddovaného středu z web formu
    //String oldDesiredPos;               // Poslední požadovaný střed (při více příchozích hodnotách)
    int poradnikMan = 0;                // Sekvenční proměnná pro najíždění požadovaného středu
    String readString;                  // Proměnná pro konverzi ze stringu o požadovaném středu na integer
    int nume = 0;                       // 2. Proměnná pro konverzi ze stringu o požadovaném středu na integer
    int oldPos[2] = {0,0};              // Pro uložení poslední pozice před vstupem do manuálu, následné najetí zpět při přechodu z pause na run
    bool runM = 0;                      // Pro rozlišení a prioritizování najíždění požadovaného středu před manuláním ovládáním šipkami
    String KrokMan;                     // Pro přeložení stringu z webu říkajícího kam chceme manuálem krokovat
