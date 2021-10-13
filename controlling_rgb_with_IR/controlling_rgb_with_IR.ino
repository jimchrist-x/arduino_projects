#include <IRremote.h>
int RECVPIN=11;
int red_pin=5, green_pin=3, blue_pin=6;
IRrecv rcv(RECVPIN);
void control(unsigned int val, decode_type_t protocol);
void setcolors(int red, int green, int blue);


void setup() {
  Serial.begin(9600);
  rcv.enableIRIn();
  setcolors(90, 90, 90);
  
}

void loop() {
  if (rcv.decode()) {
    if (rcv.decodedIRData.protocol == UNKNOWN) {
      rcv.printIRResultRawFormatted(&Serial, true);
      rcv.resume();
    } else {
       rcv.printIRResultShort(&Serial);
       control(rcv.decodedIRData.command, rcv.decodedIRData.protocol);
       rcv.resume();
    }
    
    
  }
}



void control(unsigned int val, decode_type_t protocol) {
  Serial.println(protocol);
  if (protocol==8) { // NEC Protocol
    if (val==0x16) 
      setcolors(255, 255, 255);
    else if (val==0xC) 
      setcolors(255, 0, 0);
    else if (val==0x18)
      setcolors(0, 255, 0);
    else if (val==0x5E) 
      setcolors(0, 0, 255);
    else if (val==0x8) 
      setcolors(255,255,0);
    else if (val==0x1C) 
      setcolors(0,255,255);
    else if (val==0x5A) 
      setcolors(255, 0, 255);
    else if (val==0x42) 
      setcolors(255,69,0);
    else if (val==0x52) 
      setcolors(255, 0, 127);
    else if (val==0x4A) 
      setcolors(0, 0, 0);
    else {
    }
  }
  else if (protocol==9) { // Panasonic protocol
    if (val==0x19) 
      setcolors(255, 255, 255);
    else if (val==0x10)
      setcolors(255, 0, 0);
    else if (val==0x11)
      setcolors(0, 255, 0);
    else if (val==0x12)
      setcolors(0, 0, 255);
    else if (val==0x13)
      setcolors(255,255,0);
    else if (val==0x14)
      setcolors(0,255,255);
    else if (val==0x15)
      setcolors(255, 0, 255);
    else if (val==0x16)
      setcolors(255,69,0);
    else if (val==0x17)
      setcolors(255, 0, 127);
    else if (val==0x18)
      setcolors(0, 0, 0);
    else {
    }
  }
  else if (protocol==15) { // RC5 Protocol
    if (val==0x0) 
      setcolors(255, 255, 255);
    else if (val==0x1)
      setcolors(255, 0, 0);
    else if (val==0x2)
      setcolors(0, 255, 0);
    else if (val==0x3)
      setcolors(0, 0, 255);
    else if (val==0x4)
      setcolors(255,255,0);
    else if (val==0x5)
      setcolors(0,255,255);
    else if (val==0x6)
      setcolors(255, 0, 255);
    else if (val==0x7)
      setcolors(255,69,0);
    else if (val==0x8)
      setcolors(255, 0, 127);
    else if (val==0x9)
      setcolors(0, 0, 0);
    else {
    }
  }
}



void setcolors(int red, int green, int blue) {
  analogWrite(red_pin, red);
  analogWrite(green_pin, green);
  analogWrite(blue_pin, blue);
}
