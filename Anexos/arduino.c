// SoftwareSerial para comunicacao com XBee:
#include <SoftwareSerial.h>
SoftwareSerial XBee(2, 3); // RX, TX

float current = 0;
float voltage = 0;
int currentPin = 5;
int voltagePin = 3;
String bufferString = "";

float analogToFloat(int reading){
  return (float)reading / 1024 * 5;
}

float readVoltage(){
  float reading = analogToFloat(analogRead(voltagePin));
  if(reading < 2.5){
    return 110 * sqrt(2);
  }else{
    return 220 * sqrt(2);
  }
}

float readCurrent(){
  return analogToFloat(analogRead(currentPin));
}

void setup(){
  Serial.begin(9600);
  XBee.begin(9600);
}

void loop(){
  bufferString += "{'v':";
  bufferString += analogToFloat(analogRead(voltagePin));
  bufferString += ", 'i': ";
  bufferString += readCurrent();
  bufferString += "}";
  Serial.println(bufferString);
  XBee.print(bufferString);
  bufferString = "";
  delay(100);
}
