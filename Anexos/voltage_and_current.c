// SoftwareSerial para comunicacao com XBee:
#include <SoftwareSerial.h>
SoftwareSerial XBee(2, 3); // RX, TX
#include "EmonLib.h"                  

EnergyMonitor emon1;
double current = 0;
double voltage = 0;
int currentPin = 5;
int voltagePin = 3;
String bufferString = "";
double burdenResistor = 150.0;
double CYCLE_TIME = 1 / 60;
int buffer[170];

double analogToDouble(int reading){
  return (double)reading / 1024 * 5;
}

double readVoltage(){
  double reading = analogToDouble(analogRead(voltagePin));
  if(reading < 2.5){
    return 110;
  }else{
    return 220;
  }
}

double readCurrent(int samples){
  double sum = 0;
  int sample;
  double convertedSample;
  double max = 0;
  for(int i = 0; i < samples; i++){
    offsetI = (offsetI + (sampleI-offsetI)/1024);
    filteredI = sampleI - offsetI;
    
    sample = analogRead(currentPin);
    convertedSample = (analogToDouble(sample) - 2.45) / burdenResistor;
    sum += convertedSample * convertedSample;
    
  }
  return sqrt(sum / samples) * 2000.0;
}

void setup(){
  Serial.begin(9600);
  XBee.begin(9600);
  emon1.current(currentPin, 100.0);   
}

void loop(){
  bufferString += "{'v':";
  bufferString += readVoltage();
  bufferString += ", 'i': ";
  bufferString += readCurrent(1667);
  bufferString += "}";
  Serial.println(bufferString);
  XBee.print(bufferString);
  bufferString = "";
  delay(1000);
}