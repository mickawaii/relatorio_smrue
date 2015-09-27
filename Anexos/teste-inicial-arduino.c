// SoftwareSerial para comunicacao com XBee:
#include <SoftwareSerial.h>
SoftwareSerial XBee(2, 3); // RX, TX

void setup(){
  XBee.begin(9600);
  Serial.begin(9600);
}

void loop(){
  XBee.print("123123");
  delay(1000);
}
