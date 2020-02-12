// Základní jednoduchý oběh od načtení chladiče pro oběh nad ním
void basicRoute(){
  // Inicializuje zda nebyla zmáčklá nějaká ta tlačítka
  tlacitka();
  // Pokud svítí zelené tlačítko - Oběh
  if(runallowed){ 
    // Pokud je před oběhem třeba najet poslední pozice před uvedením do pause 
    if(RunToLastPos==1){
      // Pokud se po něm sice chce aby něco najížděl, ale není co, nebo ještě ani nevyjel.. rovnou skok do runu
      if((oldPos[0]==0)&&(oldPos[1]==0)){
        RunToLastPos=0;
      }
      // V případě požadavku na najetí zpět na pozici před uvedením do runu
      if((oldPos[0]!=0)or(oldPos[1]!=0)){
        if((Xaxis.currentPosition()!=oldPos[0])or(Yaxis1.currentPosition()!=oldPos[1])){
          motorStep('X',oldPos[0],3489);
          motorStep('Y',oldPos[1],2889);
          previousMillis = millis();
        }
        if((Xaxis.currentPosition()==oldPos[0])&&(Yaxis1.currentPosition()==oldPos[1])){
          motorStop('Z');
          RunToLastPos=0;       
        }
      }
    }
    // Oběh při zaplém zeleném tlačítku START
    if(RunToLastPos==0){ 
      // 0 - Načtení výchozího bodu
      if(poradnik == 0){
        // Najetí nuly pokud ještě nebylo měřeno
       // if((oldPos[0]==0)&&(oldPos[1]==0)){
          if(initializeLocation('Z') == 1){
            initializeLocation('Z');
            previousMillis = millis();
          }
          if((initializeLocation('Z') == 0)&&(digitalRead(koncak1))&&(digitalRead(koncak3))){
            motorStop('Z');
            if(previousMillis+200 < millis()){
              phase2 = 0;
              poradnik = 1;
            }
          }
        }
       /* // Pokud již bylo
        if((oldPos[0]!=0)or(oldPos[1]!=0)){
          if((Xaxis.currentPosition()!=oldPos[0])or(Yaxis1.currentPosition()!=oldPos[1])){
            motorStep('X',oldPos[0],3489);
            motorStep('Y',oldPos[1],2889);
            previousMillis = millis();
          }
          if((Xaxis.currentPosition()==oldPos[0])&&(Yaxis1.currentPosition()==oldPos[1])){
            motorStop('Z');
            if(previousMillis+200 < millis()){
              if((strd[0][0] != 0)&&(strd[0][1] != 0)){
                phase3 = 1;
                poradnik = 2;
              }
              if((strd[0][0] == 0)or(strd[0][1] == 0)){
                phase2 = 0;
                poradnik = 1;
              }        
            }
          }
        }
      }*/
      // 1 - Nalezení kruhového chladiče
      if(poradnik == 1){
        // Inicializace, zda byl chladič již měřen. Pokud ne, nájezd do výchozí pozice pro osu X.
        if (phase2==0){
          if((strd[0][0] != 0)&&(strd[0][1] != 0)){
            poradnik = 2;
          }
          if(Yaxis1.currentPosition()!=3500){
            motorStep('Y',3500,3489);
          }
          if(Yaxis1.currentPosition()==3500){
            motorStop('Z');
            phase2=1;
          }
        }
        // Pokud je v této výchozí pozici měřič již nad chladičem, přesune se na opačnou stranu po ose Y.
        if (phase2==1){
          if(digitalRead(senzor)==0){
            phase2 = 2;
          }
          if(digitalRead(senzor)==1){
            phase2 = 3;       
          }
        }
        // Přesun na opačnou stranu (jen pokud byla minulá kontrola pozitivní)
        if (phase2==2){
          if(Yaxis1.currentPosition()!=25000){
            motorStep('Y',25000,3489);
          }
          if(Yaxis1.currentPosition()==25000){
            motorStop('Y');
            phase2=1;
          }
        }
        // Jede dokud nezaznamená hranu, ta bude prvním bodem pro osu X
        if (phase2==3){
          if(digitalRead(senzor)==1){
            motorStep('X',Xaxis.currentPosition()+(100),4122);
            previousMillis=millis();
          }
          if(digitalRead(senzor)==0){
            if(previousMillis+50<millis()){
              merX[0] = Xaxis.currentPosition();
              phase2=4;  
            }
          }
        } 
        // Přejede na opačnou stranu na ose X
        if (phase2==4){
          if((digitalRead(koncak2)==0) && (Xaxis.currentPosition()<(27500))){
            motorStep('X',207500,4122);
          }
          if((digitalRead(koncak2)==1) or (Xaxis.currentPosition()>=(27500))){
            motorStop('X');
            phase2 = 5;
          }      
        }
        // Vrací se do zaznamenání hrany = druhý bod pro X a dopočítá střed pro osu X
        if (phase2==5){
          if(digitalRead(senzor)==1){
            motorStep('X',Xaxis.currentPosition()-(100),4122);
            previousMillis=millis();
          }
          else if(digitalRead(senzor)==0){
            if(previousMillis+50<millis()){
              merX[1] = Xaxis.currentPosition();
              if((merX[1] - merX[0])<500){
                phase2=35;
              }
              strd[0][0] =merX[0] + ((merX[1] - merX[0])/2);
              phase2=6;
            }  
          }
        }
        // Vynulování Y
        if (phase2==6){
          if(initializeLocation('Y') == 1){
            initializeLocation('Y');
          }

          if(initializeLocation('Y') == 0){
            phase2=7;
          }
        }
        // Nájezd do výchozího bodu pro osu Y. MOŽNÉ ZAPNOUT - ZPOMALUJE CHOD
        if (phase2==7){/*
          if(Xaxis.currentPosition()!=(27500)){
            motorStep('X',27500,4122);
          }
          if((Xaxis.currentPosition()==(27500))or(digitalRead(koncak4)==1)){
            motorStop('X');*/
            phase2=8;
          //}
        }
        // Rozcestník, pokud již je nad chladičem, přejede po ose X na opačnou stranu.
        if (phase2==8){
          if(digitalRead(senzor)==0){
            phase2 = 9;
          }
          if(digitalRead(senzor)==1){
            phase2 = 10;       
          }
        }
        // Příjezd na opačnou stranu po X (jen pokud byla minulá podmínka splněna)
        if (phase2==9){
          if(Xaxis.currentPosition()!=6000){
            motorStep('X',6000,4122);
          }
          if(Xaxis.currentPosition()==6000){
            motorStop('X');
            phase2=8;
          }
        }
        // Jede po Y dokud nenarazí na hranu = první měřící bod pro osu Y
        if (phase2==10){
          if(digitalRead(senzor)==1){
            motorStep('Y',Yaxis1.currentPosition()+(100),3489);
            previousMillis=millis();
          }
          if(digitalRead(senzor)==0){
            if(previousMillis+50<millis()){
              merY[0] = Yaxis1.currentPosition();
              phase2=11;
            }  
          }          
        }
        // Přejede na druhou stranu po ose Y
        if (phase2==11){
          if(Yaxis1.currentPosition()!=26100){
            motorStep('Y',26100,3489);
          }
          if(Yaxis1.currentPosition()==26100){
            motorStop('Y');
            phase2 = 12;
          }      
        }
        // Vrací se po ose Y dokud nenarazí na hranu což je druhým bodem pro osu Y, z něhož dopočítá střed na Y.
        if (phase2==12){
          if(digitalRead(senzor)==1){
            motorStep('Y',Yaxis1.currentPosition()-(100),3489);
            previousMillis=millis();
          }
          if(digitalRead(senzor)==0){
            if(previousMillis+50<millis()){
              merY[1] = Yaxis1.currentPosition();
              strd[0][1] =merY[0] + ((merY[1] - merY[0])/2);
              phase2=13; 
            } 
          }    
        }
        // Najede na ose X na změřený střed
        if (phase2==13){
          if(Xaxis.currentPosition()!=(strd[0][0]-(offsetX))){
            motorStep('X',(strd[0][0]-(offsetX)),4122);
          }
          if(Xaxis.currentPosition()==(strd[0][0]-(offsetX))){
            motorStop('X');
            phase2=14;
          }
        }
        // Najede na ose Y na změřený střed (+offset z důvodu posunutí senzoru) a po pauze pokračuje dál.
        if (phase2==14){
          if(Yaxis1.currentPosition()!=(strd[0][1]-(offsetY))){
            motorStep('Y',(strd[0][1]-(offsetY)),3489);
            previousMillis = millis();
          }
          if(Yaxis1.currentPosition()==(strd[0][1]-(offsetY))){
            motorStop('Y');
            if(previousMillis + 1000 < millis()){
              
              /*Serial.print("\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
              Serial.print("X otvoru ");
              Serial.print("0");
              Serial.print(": ");
              Serial.println(strd[0][0]);
              Serial.print("Y otvoru ");
              Serial.print("0");
              Serial.print(": ");
              Serial.println(strd[0][1]);
              Serial.print("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");*/
              
              poradnik = 2;
            }
          }
        }
      } 
      // 2 - Měřicí oběh nad chladičem
      if(poradnik == 2){
        // Najetí nulového bodu
        if(phase3 == 0){
          if(initializeLocation('Z') == 1){
            initializeLocation('Z');
          }
          if(initializeLocation('Z') == 0){
            phase3 = 1;
          }
        }
        // Krokování do bodu kdy nalezne otvor ve chladiči
        if(phase3 == 1){
          // Krokování + měření v ose X
          if((not digitalRead(koncak1)) or (not digitalRead(koncak2))){
            if(digitalRead(senzor)==0){
              motorStep('X',Xaxis.currentPosition()+((smerX)*(grid)),3500);
            }
            if(digitalRead(senzor)==1){
              if((sq((Xaxis.currentPosition())-(strd[0][0]))) + (sq((Yaxis1.currentPosition())-(strd[0][1])))<=(sq(14400))){
                if(digitalRead(senzor)==1){// to tu prostě muselo být znovu, asi se kód zadrhne při počítání na moc dlouhou dobu a hodnota se změní
                  phase = 0;
                  poradnik = 3;
                }
              }
              if((sq((Xaxis.currentPosition())-(strd[0][0]))) + (sq((Yaxis1.currentPosition())-(strd[0][1])))>(sq(14400))){
                motorStep('X',Xaxis.currentPosition()+((smerX)*(grid)),3500);
              }           
            }
          }
          // Krok dále v ose Y a otočení směru při naražení hrany v ose X
          if((digitalRead(koncak2)) && (smerX == 1)){
            motorStep('Y',Yaxis1.currentPosition()+(grid),2500);
            if(((Yaxis1.currentPosition()%(grid)) == 0)or(digitalRead(koncak4))){
              motorStop('Y');
              smerX = -1;
            }
          }
          // Krok dále v ose Y a otočení směru při naražení hrany v ose X
          if((digitalRead(koncak1)) && (smerX == -1)){
            motorStep('Y',Yaxis2.currentPosition()+(grid),2500);
            if(((Yaxis1.currentPosition()%(grid)) == 0)or(digitalRead(koncak4))){
              motorStop('Y');
              smerX = 1;
            }
          } 
          // Koncový bod, konec oběhu 
          if((digitalRead(koncak4)) && (digitalRead(koncak2))){
            motorStop('Z');
            valG = 0;
            valB = 1; 

            poradnik = 0;
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

            oldPos[0]=Xaxis.currentPosition();
            oldPos[1]=Yaxis1.currentPosition();


            runM=0;
            poradnikMan=1;
            digitalWrite(ledPinG, valG);
            digitalWrite(ledPinB, valB);
            runallowed = false;  
          }
        }
      }
      // 3 - Měřicí oběh nad otvorem
      if(poradnik == 3){
        // Načtení výchozího bodu a inicializace.
        if(phase == 0){
          motorStop('Z'); 
          lastPos[0] = Xaxis.currentPosition();
          lastPos[1] = Yaxis1.currentPosition();
          phase = 1;  
        }
        // Najetí kousek od kraje což bude využíváno jako výchozí bod.
        if(phase == 1){
          if(Xaxis.currentPosition()!=(lastPos[0]+((smerX)*1000))){             
            motorStep('X',Xaxis.currentPosition()+((smerX)*1000),1800);
          }
          else{
            phase=2;
          }       
        } 
        // Pokud je mimo otvor, tento průjezd byl příliž krátký a bude ignorován. Pokud nad otvorem, začne měřit.
        if(phase == 2){
          if(digitalRead(senzor)==0){
            poradnik = 2;
          }
          if(digitalRead(senzor)==1){
            phase = 3;
          }
        }
        // Jede ve směru dokud nenarazí na hranu = Bod 1 na X.
        if(phase == 3){
          if(digitalRead(senzor)==1){
            motorStep('X',Xaxis.currentPosition()+((smerX)*(100)),1800);
            lastPosWD[0]=Xaxis.currentPosition();    
            previousMillis=millis();  
          }
          if(digitalRead(senzor)==0){
            if(previousMillis+10<millis()){
              for(int i=0; i<12; i++){
                mathValX = sq((lastPos[0]+((smerX)*1000))-strd[i][0]);
                mathValY = sq(lastPos[1]-strd[i][1]);
                if(mathValX + mathValY<=(sq(1950))){
                  poradnik = 2;
                }
              }
              merX[0] = lastPosWD[0]; 
              lastPosWD[0]=0;    
              phase=4;
            }
          }
        }
        // Jede zpět proti směru až na výchozí bod měření.
        if(phase == 4){
          if(Xaxis.currentPosition()!=(lastPos[0]+((smerX)*1500))){
            motorStep('X',(lastPos[0]+((smerX)*1500)),1800);
          }
          else{
            phase=5;
          }        
        }
        // Jede ve směru dokud nenarazí na hranu = Bod 2 na X.
        if(phase == 5){
          if(digitalRead(senzor)==1){
            motorStep('X',Xaxis.currentPosition()-((smerX)*(100)),1800);
            lastPosWD[0]=Xaxis.currentPosition();  
            previousMillis=millis();    
          }
          if(digitalRead(senzor)==0){
            if(previousMillis+10<millis()){
              merX[1] = lastPosWD[0]; 
              phase=6;
            }   
          }     
        }
        // Dopočítání středu na ose X.   
        if(phase == 6){
          if((merX[0]!=0) && (merX[1]!=0) && (merX[0]!=merX[1])){
            if((abs(merX[1] - merX[0])) <= 500){
              poradnik =2;
            }
            if((abs(merX[1] - merX[0])) > 500){
              strd[strdporadi][0]=merX[0] + ((merX[1] - merX[0])/2);
              phase = 7; 
            } 
          }
          else{

            poradnik = 2;
          }       
        }
        // Najetí středu na ose X.
        if(phase == 7){
          if(Xaxis.currentPosition()!=(strd[strdporadi][0]-(offsetX))){
            motorStep('X',(strd[strdporadi][0]-(offsetX)),1800);
            previousMillis = millis();
          }
          if(Xaxis.currentPosition()==(strd[strdporadi][0]-(offsetX))){
            if(previousMillis + 10 < millis()){
              phase = 8;
            }
          }
        }
        // Jede dolů ve směru Y až po hranu, nalezení prvního bodu pro osu Y.
        if(phase == 8){
          if(digitalRead(senzor)==1){
            motorStep('Y',Yaxis1.currentPosition()-(100),1800);
            lastPosWD[1] = Yaxis1.currentPosition();
            previousMillis = millis();
          }
          if(digitalRead(senzor)==0){
            if(previousMillis + 10 < millis()){
              merY[0] = lastPosWD[1];
              lastPosWD[1] = 0;
              phase=9;
            }
          }
          else if(digitalRead(koncak3)==1){
              merY[0] = lastPosWD[1];
              lastPosWD[1] = 0;
              phase=9;
          }        
        }
        // Návrat na pomyslný výchozí bod v Y.
        if(phase == 9){
          if(Yaxis1.currentPosition()!=lastPos[1]){
            motorStep('Y',lastPos[1],1800);
          }
          if(Yaxis1.currentPosition()==lastPos[1]){
            phase=10;  
          }        
        }
        // Nalezení druhého bodu pro osu Y a dopočítání středu.
        if(phase == 10){
          if(digitalRead(senzor)==1){
            motorStep('Y',Yaxis1.currentPosition()+(100),1800);
            lastPosWD[1] = Yaxis1.currentPosition();
            previousMillis = millis();
          }
          if((digitalRead(senzor)==0)or(digitalRead(koncak1)==1)){
            if(previousMillis + 10 < millis()){
              merY[1] = lastPosWD[1];
              strd[strdporadi][1]=merY[0] + ((merY[1] - merY[0])/2);
              phase=12;
            }
          }       
        }
        // Návrat na Y na opačnou hranu výchozímu bodu.
        if(phase == 12){
          if(Yaxis1.currentPosition()!=lastPos[1]){
            motorStep('Y',lastPos[1],1800);
          }
          if(Yaxis1.currentPosition()==lastPos[1]){
            phase=13;
          }          
        }
        // Návrat na X do výchozího bodu.
        if(phase == 13){
          if(Xaxis.currentPosition()!=merX[0]+(smerX*500)){
            motorStep('X',merX[0]+(smerX*2000),1800);
          }
          if(Xaxis.currentPosition()==merX[0]+(smerX*500)){
            phase=14;
          }
        }
        // Vynulování a ukončení měření.
        if(phase == 14){
          lastPos[0] = 0;
          lastPos[1] = 0;
          merX[0] = 0;
          merX[1] = 0;
          merY[0] = 0; 
          merY[1] = 0;
          strdporadi = strdporadi + 1;
          poradnik = 2;
        }
      }
    }
  }
  // Pokud svítí modré tlačítko - Pause - prostor pro manuální ovládání
  else if(not runallowed){
    // Pokud najíždí nějaký střed
    if(runM==1){
      // První část - převedení stringu o požadovaném středu na číslo
      if(poradnikMan==1){
        readString = desiredPos;        // Přečte si string co mu přišel z web formu a převede na integer
        if (readString.length() >0) {  
          nume = readString.toInt();  
          readString="";
          poradnikMan = 2;
        }
      }
      // Druhá část - najetí čísla
      if(poradnikMan==2){
        if((Yaxis1.currentPosition()==strd[nume][1]-offsetY)&&(Xaxis.currentPosition()==strd[nume][0])){
          motorStop('Z');
          runM=0;
        }
        else{
          motorStep('X',strd[nume][0],3489);
          motorStep('Y',strd[nume][1]-offsetY,2889);
        }
      }
    }
    // Pokud pouze stojí a dává prostor ovládání pozice manuálně
    if(runM==0){
      // Vynulování minulého krokování pro možnost opětovného zavolání funkce a najetí dalšího středu
      poradnikMan=1;
      
      // Jednotlivé krokování tlačítky manuálního ovládání, pokud není žádné - stojí a čeká
      if(KrokMan == "Yp"){
        motorStep('Y',Yaxis1.currentPosition()+100,1200);
        motorStop('X');   
      }
      if(KrokMan == "Ym"){
        motorStep('Y',Yaxis1.currentPosition()-100,1200); 
        motorStop('X'); 
      }
      if(KrokMan == "Xp"){
        motorStep('X',Xaxis.currentPosition()+100,1200);     
        motorStop('Y');
      }
      if(KrokMan == "Xm"){
        motorStep('X',Xaxis.currentPosition()-100,1200);
        motorStop('Y');
      }
      if(KrokMan == "S"){
        motorStop('Z');  
      }
      else{
        motorStop('Z');
      }
    }
  }   
}
