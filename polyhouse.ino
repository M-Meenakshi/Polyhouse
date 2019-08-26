#include <LiquidCrystal.h>
#include "DHT.h"
#define DHTPIN A1

 #define fan 8
 #define pump A4
 

 
 int moisture_sensor = A2;
 const int ledPin =10;
 const int ldrPin =A0;
 int sensorvalue=0;
 #define DHTTYPE DHT11
 DHT dht(DHTPIN,DHTTYPE);
 LiquidCrystal lcd(12,11,5,4,3,2);
 
 void setup()
 {  
  lcd.begin(16,2);
  dht.begin();
  Serial.begin(9600);
  lcd.print("Temp: Humidity:");
  pinMode(ledPin,OUTPUT);
  pinMode(ldrPin,INPUT);
  pinMode(fan,OUTPUT);
  pinMode(pump,OUTPUT);
  
 }
 void loop()
 {
  lcd.setCursor(0,1);
  float h = dht.readHumidity();
  Serial.println(h);
  delay(500);
  float f = dht.readTemperature();
  Serial.println(f);
  delay(500);
  if(isnan(h)|| isnan(f))
  {
    lcd.print("ERROR");
    return;
  }
    lcd.print(f);
    lcd.setCursor(8,1);
    lcd.print(h);
   if(f>25)
    {
      digitalWrite(fan,HIGH);
     }
     else
     {
      digitalWrite(fan,LOW);
     }
     if(f<20)
     {
      digitalWrite(ledPin,HIGH);
     }
 
   sensorvalue = analogRead(A2);
    if(sensorvalue<=500)
   {
    analogWrite(pump,HIGH);
    Serial.println("Soil is dry");
    Serial.print(sensorvalue);
    delay(500);
   }
   else{
    analogWrite(pump,LOW);
    Serial.println("soil is wet");
    Serial.print(sensorvalue);
   }
   int ldrstatus = analogRead(ldrPin);
   if(ldrstatus>100)
   {
    digitalWrite(ledPin,HIGH);
   Serial.println("Its DARK TURN on led");
   Serial.print(ldrstatus);
   }
   else
   {
    digitalWrite(ledPin,LOW);
    Serial.println("Its Bright,turn off led:");
    Serial.print(ldrstatus);
   }
       
 }
  
  
 

