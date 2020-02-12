// Funkce pro vypnutí X motorů, Y motoru či všech zároveň
void motorStop(char axis) {
    if (axis == 'Y'){
        Yaxis1.stop();
        Yaxis2.stop();
        Yaxis1.disableOutputs(); 
        Yaxis2.disableOutputs();
        digitalWrite(enableY, HIGH);
    }
    if (axis == 'X'){
        Xaxis.stop();
        Xaxis.disableOutputs(); 
        digitalWrite(enableX, HIGH);
    }
    if (axis == 'Z'){
        Yaxis1.stop();
        Yaxis2.stop();
        Xaxis.stop();
        Yaxis1.disableOutputs(); 
        Yaxis2.disableOutputs();
        Xaxis.disableOutputs(); 
        digitalWrite(enableY, HIGH);
        digitalWrite(enableX, HIGH);
    }
}
// Funkce pro zapnutí X motorů, Y motoru či všech zároveň
void motorStart(char axis) {
    if (axis == 'Y'){
        Yaxis1.enableOutputs(); 
        Yaxis2.enableOutputs(); 
        digitalWrite(enableY, LOW);
    }
    if (axis == 'X'){
        Xaxis.enableOutputs(); 
        digitalWrite(enableX, LOW);
    }
    if (axis == 'Z'){
        Yaxis1.enableOutputs(); 
        Yaxis2.enableOutputs(); 
        Xaxis.enableOutputs(); 
        digitalWrite(enableY, LOW);  
        digitalWrite(enableX, LOW);        
    }
}
// Funkce pro krokování
void motorStep(char axis,long int position, long acceleration) {
    if (axis == 'Y') {
      if(Yaxis1.currentPosition() != position) {
        if((Yaxis1.currentPosition() < position) && (not digitalRead(koncak4))){
          motorStart('Y');
          Yaxis1.moveTo(position);
          Yaxis2.moveTo(position);

          Yaxis1.setSpeed(acceleration);
          Yaxis2.setSpeed(acceleration);
        //Yaxis1.setAcceleration(acceleration);
        //Yaxis2.setAcceleration(acceleration);

          Yaxis1.run();
          Yaxis2.run(); 
        }
        if((Yaxis1.currentPosition() > position) && (not digitalRead(koncak3))){
          motorStart('Y');
          Yaxis1.moveTo(position);
          Yaxis2.moveTo(position);

          Yaxis1.setSpeed(-1*(acceleration));
          Yaxis2.setSpeed(-1*(acceleration));
        //Yaxis1.setAcceleration(acceleration);
        //Yaxis2.setAcceleration(acceleration);

          Yaxis1.run();
          Yaxis2.run(); 
        }
      }
      else {
        motorStop('Y');
      }        
    }
    if (axis == 'X') {
      if(Xaxis.currentPosition() != position) {
        if((Xaxis.currentPosition() > position) && (not digitalRead(koncak1))){
          motorStart('X');
          Xaxis.moveTo(position);

          Xaxis.setSpeed(-1*(acceleration));
          //Xaxis.setAcceleration(acceleration);

          Xaxis.run();
        }
        if((Xaxis.currentPosition() < position) && (not digitalRead(koncak2))){
          motorStart('X');
          Xaxis.moveTo(position);

          Xaxis.setSpeed(acceleration);
          //Xaxis.setAcceleration(acceleration);

          Xaxis.run();
        }
      }
      else {
        motorStop('X');
      }        
    }
}
// Funkce pro najetí nulového bodu X, Y, XY
bool initializeLocation(char axis){
  if(runallowed == 1) {
    // Y //
    if (axis == 'Y'){
      // Za jaké podmínky jdou X motory do záporu
      if(not digitalRead(koncak3)) {
        motorStep('Y',-100000,3500);
      }
      // Podmínka pro moment, kdy narazí na koncový spínač
      else if (digitalRead(koncak3)) {
        motorStop('Y');
        Yaxis1.setCurrentPosition(0);
        Yaxis2.setCurrentPosition(0);
        return (0);
      }  
    }
    // X
    if (axis == 'X'){
      // Za jaké podmínky jde Y motor do záporu
      if(not digitalRead(koncak1)) {
        motorStep('X',-100000,3500);
      }
      // Podmínka pro moment, kdy narazí na koncový spínač
      if (digitalRead(koncak1)) {
        motorStop('X');
        Xaxis.setCurrentPosition(0);
        return (1);
      }        
    }
    // BOTH X AND Y
    if (axis == 'Z'){
      // Za jaké podmínky vyhodnotí jako splněno a tudíž automaticky opouští tuto funkci
      if((digitalRead(koncak3) == 1) && (digitalRead(koncak1) == 1)) {
        return (0);
      }
      // Za jaké podmínky jdou Y motory do záporu
      if(not digitalRead(koncak3)) {
        motorStep('Y',-100000,3500);
      }
      // Podmínka pro moment, kdy narazí na koncový spínač
      if (digitalRead(koncak3)) {
        motorStop('Y');
        Yaxis1.setCurrentPosition(0);
        Yaxis2.setCurrentPosition(0);
        
      }
      // Za jaké podmínky jde X motor do záporu
      if((not digitalRead(koncak1)) && (digitalRead(koncak3))) {
        motorStep('X',-100000,3500);
      }
      // Podmínka pro moment, kdy narazí na koncový spínač
      if (digitalRead(koncak1)) {
        motorStop('X');
        Xaxis.setCurrentPosition(0);
      }       
    }
  }
}
// Funkce pro naměření a vypsání maximálního počtu kroků v dané ose
int measureMax(char axis){
  if(runallowed == 1) {
    // Y //
    if (axis == 'Y'){
      // Za jaké podmínky jdou X motory do záporu
      if(not digitalRead(koncak4)) {
        motorStart('Y');
        motorStep('Y',350000,1000);
      }
      // Podmínka pro moment, kdy narazí na koncový spínač
      if (digitalRead(koncak4)) {
        motorStop('Y');
        return(0);
      }      
    }
    // X //
    if (axis == 'X'){
      // Za jaké podmínky jde X motor do záporu
      if(not digitalRead(koncak2)) {
        motorStep('X',350000,3000);
      }
      // Podmínka pro moment, kdy narazí na koncový spínač
      else if (digitalRead(koncak2)) {
        motorStop('X');
        return(0);
      }        
    }
    // BOTH X AND Y //
    if (axis == 'Z'){
      // Za jaké podmínky vyhodnotí hodnotu "1" jako splněno a tudíž automaticky opouští tuto funkci
      if((digitalRead(koncak4) == 1) && (digitalRead(koncak2) == 1)) {
        return(0);
      }
      // Za jaké podmínky jdou Y motory do záporu
      if(not(digitalRead(koncak4))) {
        motorStep('Y',100000,1500);
      }
      // Podmínka pro moment, kdy narazí na koncový spínač
      if (digitalRead(koncak4)) {
        motorStop('Y');
      }
      // Za jaké podmínky jde X motor do záporu
      if((not digitalRead(koncak2)) && (digitalRead(koncak4))) {
        motorStep('X',100000,2000);
      }
      // Podmínka pro moment, kdy narazí na koncový spínač
      if (digitalRead(koncak2)) {
        motorStop('X');
      }        
    }
  }
}
// Funkce pro ovládání tlačítek
void tlacitka(){
  // Zelené tlačítko
    buttonStateG = digitalRead(buttonPinG);
    if ( (buttonStateG == 1) && (lastButtonStateG == 0) ){
      valG = 1;
      valB = 0;
      poradnikMan=1;
      runM=0;
      runallowed = true;
    } 
    digitalWrite(ledPinG, valG);
    lastButtonStateG = buttonStateG;

  // Modré tlačítko
    buttonStateB = digitalRead(buttonPinB);
    if ((buttonStateB == 1) && (lastButtonStateB == 0)){
      valB = 1;
      valG = 0;

      RunToLastPos=1; 

      oldPos[0]=Xaxis.currentPosition();
      oldPos[1]=Yaxis1.currentPosition();

      poradnikMan=1;
      runM=0;
      runallowed = false;
    } 
    digitalWrite(ledPinB, valB);
    lastButtonStateB = buttonStateB;

  // Červené tlačítko
    buttonStateR = digitalRead(buttonPinR);                                         
    if (( buttonStateR == HIGH ) and (reset_count < 10) and (valB == 1)){
      if(previousMillisTimer+150<=millis()){
        valR = 1;
        digitalWrite(ledPinR, valR);
      }
      if(previousMillisTimer+300<=millis()){
        valR = 0;
        digitalWrite(ledPinR, valR);
        reset_count = reset_count + 1; 
        previousMillisTimer = millis();
      }
    }
    else{
      valR = HIGH;
      digitalWrite(ledPinR, valR);
    }
    if (( (lastButtonStateR == HIGH) and (buttonStateR == LOW) and (reset_count < 10)) or ( (valB != 1) ) ){
      reset_count = 0;
    }
    if ( (lastButtonStateR == HIGH) and (buttonStateR == LOW) and (reset_count == 10) and (valB == 1)){
      reset_count = 0;
      poradnik = 0;
      phase = 0;
      phase2 = 0;
      phase3 = 0;
      merX[0] = 0;   
      merX[1] = 0;               
      merY[0] = 0;   
      merY[1] = 0;   
      lastPos[0] = 0;   
      lastPos[1] = 0;   
      lastPosWD[0] = 0;   
      lastPosWD[1] = 0;   
      mathValX = 0;
      mathValY = 0;
      strdporadi = 1;
      runM=0;
      oldPos[0] = 0;
      oldPos[1] = 0;
      nume = 0;
      poradnikMan = 0;
      for(int i=0;i<17;i++){
        for(int d=0;d<2;d++){
          strd[i][d]= 0;   
        }
      }
    }
    lastButtonStateR = buttonStateR; 
}
