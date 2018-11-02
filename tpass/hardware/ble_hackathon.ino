// Import libraries (BLEPeripheral depends on SPI)
#include <SPI.h>
#include <BLEPeripheral.h>
#include <U8g2lib.h>
#include "BLESerial.h"
//#include <fc/reflect/private_key.hpp>

//custom boards may override default pin definitions with BLESerial(PIN_REQ, PIN_RDY, PIN_RST)
BLESerial bleSerial;
U8G2_SH1106_128X64_NONAME_F_SW_I2C u8g2(U8G2_R2, 24, 23);

const uint8_t logo[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,63,158,120,3,207,7,192,248,0,0,0,0,0,0,0,0,63,159,254,15,255,31,227,252,0,0,0,0,0,0,0,0,63,159,254,15,255,31,227,252,0,0,0,0,0,0,0,0,30,31,191,31,191,60,7,128,0,0,0,0,0,0,0,0,30,31,15,190,31,60,7,128,0,0,0,0,0,0,0,0,30,30,7,188,15,63,135,240,0,0,0,0,0,0,0,0,30,30,7,188,15,31,227,252,0,0,0,0,0,0,0,0,30,30,7,188,15,7,240,254,0,0,0,0,0,0,0,0,30,30,7,188,15,1,240,62,0,0,0,0,0,0,0,0,30,31,15,62,31,0,240,30,0,0,0,0,0,0,0,0,30,31,191,31,191,48,246,30,0,0,0,0,0,0,0,0,30,31,254,15,255,63,231,252,0,0,0,0,0,0,0,0,30,31,254,15,255,63,231,252,0,0,0,0,0,0,0,0,30,30,120,3,207,15,129,240,0,0,0,0,0,0,0,0,0,30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
const char* privateKey = "5JLNE22S9LNhPqN7HuDXCfR7ncuVjcojZVKEZ4433fcjdo5pDYF";

#define LED_PIN    7
#define BUTTON     6

void ledOff() {
  digitalWrite(LED_PIN, HIGH);  
}

void ledOn() {
  digitalWrite(LED_PIN, LOW);  
}

void printLogo() {
    u8g2.clearBuffer();
    u8g2.drawBitmap(0,0,16,64,logo); 
    u8g2.sendBuffer();
}

void clearScreen() {
    u8g2.clearBuffer(); 
    u8g2.sendBuffer();    
}

bool buttonPressed() {
  return digitalRead(BUTTON) == LOW;
}

void setup() {
  // custom services and characteristics can be added as well
  pinMode(25, OUTPUT);
  pinMode(28, OUTPUT);
  digitalWrite(25, HIGH);
  digitalWrite(28, LOW);
  pinMode(BUTTON, INPUT_PULLUP);
  
  u8g2.begin();
  printLogo();
  ledOn();
  delay(100);
  ledOff();
  clearScreen();

  bleSerial.setLocalName("UART");
  bleSerial.begin();  
}

int iter = 0;
int start = 0;
char msg[1000];

void presentation() {
  strcpy(msg, "FutureMail");
  printLogo();
  delay(2000);
  int finish = millis() + 15500;
  while(finish > millis()) {
    bool end = false;
    if(buttonPressed()) {
      end = true;
    }
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB08_tr);
    if(end) {
      u8g2.drawStr(1,10,"Logging to:");
    } else {
      u8g2.drawStr(1,10,String(("Logging to:         (") + String(float(finish-millis()) / 1000., 1) + ")").c_str());      
    }
    u8g2.setFont(u8g2_font_crox4h_tr);
    u8g2.drawStr(10,32,msg);
    if(end) {
      u8g2.setFont(u8g2_font_8x13B_tr);
      u8g2.drawStr(5,48,"LOGIN APPROVED");      
    } else {
      u8g2.setFont(u8g2_font_ncenB08_tr);
      u8g2.drawStr(1,50,"Confirm");
      u8g2.drawStr(90,50,"Reject");
    }
    u8g2.sendBuffer();    
    if(end) {
      delay(2000);
      break;
    }
    delay(10);
  }
  printLogo();
  delay(2000);
  clearScreen();
}

void loop() {
  bleSerial.poll();
  digitalWrite(LED_PIN, (millis() / 1000) % 3);
  if(bleSerial) {
    int i = 0;
    int rbyte;
    while ((rbyte = bleSerial.read()) > 0) { 
        if(iter == 0 && i < 100)
          msg[i++] = (char)rbyte;
        // here should be also code to recive transaction
    }
    
    if(i > 0 && iter == 0) {
      iter = 1;
      msg[i] = 0;
      printLogo();
    } else if(iter == 100) {
      start = millis();
    } else if(iter > 100 && start + 16500 < millis()) {
      if(iter < 200)
            bleSerial.write(0xFF);
      iter = 0;      
      clearScreen();
    } else if(iter > 100 && start + 15500 < millis()) {
      printLogo();
    } else if(iter > 100 && iter < 200) {
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_ncenB08_tr);
      u8g2.drawStr(1,10,String(("Logging to:         (") + String(float(start+15500-millis()) / 1000., 1) + ")").c_str());
      u8g2.setFont(u8g2_font_crox4h_tr);
      u8g2.drawStr(10,32,msg);
      u8g2.setFont(u8g2_font_ncenB08_tr);
      u8g2.drawStr(1,50,"Confirm");
      u8g2.drawStr(90,50,"Reject");
      u8g2.sendBuffer();    
      if(buttonPressed())
        iter = 200;
    } else if(iter == 200) {
      iter = 201;
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_ncenB08_tr);
      u8g2.drawStr(1,10,"Logging to:");
      u8g2.setFont(u8g2_font_crox4h_tr);
      u8g2.drawStr(10,32,msg);
      u8g2.setFont(u8g2_font_8x13B_tr);
      u8g2.drawStr(5,48,"LOGIN APPROVED");
      u8g2.sendBuffer();          
      start = millis() - 13500;
      // here should be code for sign transaction and send it back
      // sign(privateKey, msg, signedMsg)
      // bleSerial.write(signedMsg)
      char ret = 0x00;
      bleSerial.write(ret);
    }
  
    if(iter > 0 && iter < 101) {
      iter += 1;
    }
    delay(10);
  } else if(iter > 100) { 
      iter = 0;      
      clearScreen();
  } else if(buttonPressed()) {
    presentation();
  }
}

