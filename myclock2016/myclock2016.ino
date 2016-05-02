#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

 void displayTime(void); 
 
 unsigned long previousMillis=0;
 const int interval=1000;
 int i=0,j=0;
 byte sec=0,minute=0,hour=0,hourDisplay;
 LiquidCrystal_I2C lcd(0x27,16,2);
 
 void setup (){
 lcd.init(); 
 lcd.backlight();
 lcd.print("    :  :    M");
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
       if(hour==24);
       hour=0;
   }
  }
 }
 i=millis()%1000;
 lcd.setCursor(0,1);
 lcd.print(" ms=");
 lcd.setCursor(3,1);
 millis()%200>=185||millis()%200<=15?j=0:j=200;
 j+=(((millis()%1000)/200)*200);
 if(j>=1000)j-=1000;
 lcd.print(j);
 displayTime();
}
void displayTime(void){
  lcd.setCursor(11,0);
  if(hour>=12)
  lcd.print("P");
  else
  lcd.print("A");
  
  if(hour==0)
   hourDisplay=12;
  else if(hour<=12)
   hourDisplay=hour;
  else
   hourDisplay=hour-12;
   
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
}

