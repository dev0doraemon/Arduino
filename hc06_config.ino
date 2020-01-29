#include <SoftwareSerial.h>

#define BAUD 9600

SoftwareSerial hc05(3, 4);
//SoftwareSerial hc06(12, 13);

int temp = 0;

String cmd = "";
boolean check;

void setup() {
  //Initialize Serial Monitor
  // Supported baud rate: 9600,19200,38400,57600,115200,230400,460800
  uint32_t baud[] = { 9600, 19200, 38400, 57600, 115200, 230400, 460800, 921600, 1382400 };
  Serial.begin(9600);
  pinMode(8, OUTPUT);
  //  Serial.println("ENTER AT Commands:");
  //Initialize Bluetooth Serial Port
  for (int i = 0; i < 9; i++) {
    check = checkBaud(&hc05, baud[i], "AT");

    if (check) {
      Serial.println("Success!");
      break;
    }
    else {
      Serial.println("Failed");
    }
  }

  Serial.println("Set the baud");
  Serial.println("Checking process is done!");
  Serial.println("Setting baud...");
  setBaud(&hc05, BAUD);
  Serial.println("Done!");

  //  hc05.write("AT+NAMEODH");
  //  delay(60);
  //  while (hc05.available()) {
  //    Serial.write(hc05.read());
  //  }
  //
  //  hc05.write("AT+PIN0000");
  //  delay(60);
  //  while (hc05.available()) {
  //    Serial.write(hc05.read());
  //  }
  //
  //  hc05.write("AT+BAUD4");
  //  delay(60);
  //  while (hc05.available()) {
  //    Serial.write(hc05.read());
  //  }
}

void loop() {
  //Write data from HC06 to Serial Monitor
  while (hc05.available()) {
    //    Serial.write(hc06.read());
    temp = hc05.read();  // ASCII 십진수 13과 10을 추가적으로 읽음.
    Serial.print(temp);
    Serial.println((char)temp);

    if (!(temp == 10 || temp == 13)) {  // Removing escape character
      cmd += (char)temp;
    }

    // You can check the command on Serial Monitor when you are using a phone
    //    if (temp == 13) {
    //      Serial.println(cmd);
    //    }
  }

  //  delay(100); // 이게 없으면 스위치가 오동작함....
  //Write from Serial Monitor to HC06
  //  if (Serial.available()) {
  //    hc06.write(Serial.read());
  //    Serial.println("B to Ph");
  //  }
  //  Serial.println(1);
  //  Serial.println(buf);
  //  Serial.println(2);
  //  Serial.println(buf == "ON");
  if (cmd == "ON") {
    digitalWrite(8, HIGH);
    hc05.write("CMD ON");
  }
  else if (cmd == "OFF") {
    digitalWrite(8, LOW);
    hc05.write("CMD OFF");
  }

  cmd = "";
  delay(60);
}

boolean checkBaud(SoftwareSerial* obj, uint32_t baud, char* CMD) {
  String resp = "";
  int temp;

  (*obj).begin(baud);
  Serial.println("Checking in " + (String)baud + " baud");
  Serial.println(CMD);
  (*obj).write(CMD);
  delay(60);
  while ((*obj).available()) {
    temp = (*obj).read();
    Serial.write(temp);
    if (!(temp == 10 || temp == 13)) {
      resp += (char)temp;
    }
  }

  if (resp == "OK" || resp == "ERROR:(0)") {
    Serial.println(baud);
    return true;
  }
  else {
    (*obj).end();
    return false;
  }
}

void setBaud(SoftwareSerial* obj, int baud) {
  switch (baud) {
    case 1200:
      (*obj).write("AT+BAUD1");
      break;
    case 2400:
      (*obj).write("AT+BAUD2");
      break;
    case 4800:
      (*obj).write("AT+BAUD3");
      break;
    case 9600:
      (*obj).write("AT+BAUD4");
      break;
    case 19200:
      (*obj).write("AT+BAUD5");
      break;
    case 38400:
      (*obj).write("AT+BAUD6");
      break;
    case 57600:
      (*obj).write("AT+BAUD7");
      break;
    case 115200:
      (*obj).write("AT+BAUD8");
      break;
    case 230400:
      (*obj).write("AT+BAUD9");
      break;
    case 460800:
      (*obj).write("AT+BAUDA");
      break;
    case 921600:
      (*obj).write("AT+BAUDB");
      break;
    case 1382400:
      (*obj).write("AT+BAUDC");
      break;
  }
  delay(60);
  
  while ((*obj).available()) {
    Serial.write((*obj).read());
  }
}
