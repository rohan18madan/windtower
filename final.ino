//#include <LiquidCrystal.h>
#include "Adafruit_Si7021.h"
//LiquidCrystal lcd = LiquidCrystal(2, 3, 4, 5, 6, 7);
Adafruit_Si7021 sensor = Adafruit_Si7021();
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  //lcd.begin(16, 2);

  // wait for serial port to open
  while (!Serial) {
    delay(10);
  }
  if (!sensor.begin()) {
    Serial.println("Did not find Si7021 sensor!");
    while (true);
  }
  

}
unsigned long myTime;
unsigned long Time;
unsigned long temporary = 0;
unsigned long tempTime = 0;
unsigned long difference;
float voltage;
double rpm;
int sensorValue;
double humidity;
double temperature;
void loop() {
  // read the input on analog pin 0:
 
  //for(int i=0; i<200; i++){
    sensorValue = analogRead(A0);
    voltage = sensorValue * (5.0 / 1024.0);

    while(voltage >= 1.0){
      sensorValue = analogRead(A0);
      voltage = sensorValue * (5.0 / 1024.0);
      myTime = millis();
     
    }
    while(voltage < 1.0){
      sensorValue = analogRead(A0);
      voltage = sensorValue * (5.0 / 1024.0);
    }
  //}
 

  difference = myTime-tempTime;
  rpm = (1000.0/difference)*60.0;
  tempTime = myTime;

  Time = millis();
  if((Time-temporary)>2000){
    humidity = sensor.readHumidity();
    temperature = sensor.readTemperature();
    temporary = Time;
  }
  if(rpm<500){
    Serial.println("POTIENTIAL HINDRANCE IN FAN");
  }
  if(temperature>75){
    Serial.println("FAN OVERHEATING");
  }
  if(humidity>80){
    Serial.println("HUMIDITY LEVELS COULD DAMAGE FAN");
  }
  

}
