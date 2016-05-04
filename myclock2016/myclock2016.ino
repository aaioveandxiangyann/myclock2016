#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
 void displayTime(void); 
 int cd=2,Displacement=3,Adjustment=4,Bluetooth=6,clock=5,ampm=0;
 unsigned long previousMillis=0;
 const int interval=1000;
 int i=0,j=0;
 char preSw[10],nowSw[10];
 byte sec=0,minute=0,hour=0,hourDisplay;
 int clockCursor=0;
 LiquidCrystal_I2C lcd(0x27,16,2);
 
 void setup (){
 for(i=0;i<10;i++)preSw[i]=nowSw[i]=1;
 pinMode(cd,OUTPUT);
 pinMode(Displacement,INPUT_PULLUP);
 pinMode(Adjustment,INPUT_PULLUP);
 pinMode(clock,OUTPUT);
 lcd.init(); //LINK START!!!! 
 lcd.backlight();
 lcd.print("    :  :   AM");
 Serial.begin(9600);
}

void loop(){
 unsigned long currentMillis=millis();
 if(currentMillis - previousMillis >= interval) {
   previousMillis = previousMillis + interval;
   sec++;
   if(sec==60){
     minute++;
     sec=0;
     if(minute==60){
       hour++;
       minute=0;
       if(hour==12){
         if(ampm==0){lcd.setCursor(11,0);lcd.print("P");ampm=1;}
         else{lcd.setCursor(11,0);lcd.print("A");ampm=0;}
         hour=0;
       }
   }
  }
  displayTime();
 }
 nowSw[0]=digitalRead(Displacement);
 if(nowSw[0]!=preSw[0]){
   preSw[0]=nowSw[0];
   if(nowSw[0]==0){
     switch(clockCursor){
       case 0:
          clockCursor=3;
          Serial.println(clockCursor);
          lcd.blink();
          break;
       case 3:
         clockCursor=6;
          Serial.println(clockCursor);
          break;
       case 6:
         clockCursor=9;
         Serial.println(clockCursor);
         break;
       case 9:
         clockCursor=0;
         Serial.println(clockCursor);
         lcd.noBlink();
         break;
     }
     lcd.setCursor(clockCursor,0);
   } 
   delay(50);
 }
  nowSw[1]=digitalRead(Adjustment);
  if(nowSw[1]!=preSw[1]){
   preSw[1]=nowSw[1];
   if(nowSw[1]==0){
     switch(clockCursor){
       case 0:break;
       case 3:
         if(digitalRead(Adjustment)==0)hour++;
         if(hour==12){
           //hour-=12;
           if(ampm==0){lcd.setCursor(11,0);lcd.print("P");ampm=1;}
           else{lcd.setCursor(11,0);lcd.print("A");ampm=0;}
         }
         
         break;
       case 6:
         if(digitalRead(Adjustment)==0)minute++;
         if(minute>=60)minute-=60;
         break;
       case 9:
         if(digitalRead(Adjustment)==0)sec++;
         if(sec>=60)sec-=60;
         break;
     }
   }
  }
  delay(50);
}
void displayTime(void){
  lcd.setCursor(11,0);
/*  if(hour>=12){
    switch(ampm){
      case 0:lcd.print("P");ampm=1;break;
      case 1:lcd.print("A");ampm=0;break;
    }
  }
  else lcd.print("A");*/
  
  if(hour==0)
   hourDisplay=12;
  else if(hour<=12)
   hourDisplay=hour;
  else
   hourDisplay=hour-=12;
   
  lcd.setCursor(2,0);
  if(hourDisplay<10)
  lcd.print("0");
  lcd.print(hourDisplay);
  
  lcd.setCursor(5,0);
  if(minute<10)
  lcd.print("0");
  lcd.print(minute); 
 
  lcd.setCursor(8,0); 
  if(sec<10)
  lcd.print("0");
  lcd.print(sec);
  
  if(clockCursor)
    lcd.setCursor(clockCursor,0);  
}
