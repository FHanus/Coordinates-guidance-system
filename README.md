# Coordinates guidance system
***Author: Filip Hanus - Stredni prumyslova skola na Proseku***

__Built as a long-term graduation project__     
__Contact: filiphanus1@gmail.com__

## Specs
Simplified 3D scanner.
Working coordinates system, that detects holes and their coordinates.
Used for cleaning clogged cooler pipes.

* Microcontroller: ESP32, programming in Arduino IDE. Using AccelStepper and Adafruit VL53L0X libraries.
* Sensor to detect distance: vl53l0x (ToF)
* Movement: NEMA16 and NEMA17 motors with GT2 belt pulleys and belt, controlled by A4988 motor drivers.
* Model: Aluminium frame with PLA parts

## Parts

* ***Main***    -> Split code to step and measure. More uncluttered. Includes main file.

* ***Inventor - DMP.zip***    -> 3D model.

* ***hanusfi16.doc***        -> Research document.

* ***SchemaDMP.brd***  -> PCB


## Development progress
* 21/01/2020
    * Split core usage between them and running web with measuring simultaneously.
 
* 19/01/2020
    * Measure route done.
 
* 05/01/2020
    * Main routes of the code done. Research document progress.
 
* 22/12/2019
    * Working functions in main code.
  
* 14/12/2019
    * Finished and soldered PCB.

* 22/11/2019
    * Research document added.

* 20/11/2019
    * PCB test done.
    * Button code is ready, web as well.

* 05/11/2019
    * Finished final 3D model of construction, ready to print it. 

* 30/10/2019
    * Finished last part of 3D model mechanism. 

* 29/10/2019
    * Finished WEB site with java script to show values and to control functions.
    
* < 10/2019
    * 90% of construction done.
    * Got ready basic motor code.




