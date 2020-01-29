#include <SoftwareSerial.h>

SoftwareSerial hc06(3, 4);

void setup() {
  //Initialize Serial Monitor
  Serial.begin(9600);
  Serial.println("ENTER AT Commands:");
  //Initialize Bluetooth Serial Port
  hc06.begin(38400);

//  hc06.write("AT+NAMEODH2");
//  delay(100);
//
//  while (1) {
//    if (hc06.available()) {
//      Serial.println(hc06.read());
//    }
//    else {
//      break;
//    }
//  }
//
//  hc06.write("AT+PIN0000");
//  delay(100);
//
//  hc06.write("AT+BAUD4");
//  delay(100);
}

void loop() {
    //Write data from HC06 to Serial Monitor
    if (hc06.available()){
      Serial.write(hc06.read());
    }
  
    //Write from Serial Monitor to HC06
    if (Serial.available()){
      hc06.write(Serial.read()); // Serial.read()는 아스키값 반환함.
    }
}
