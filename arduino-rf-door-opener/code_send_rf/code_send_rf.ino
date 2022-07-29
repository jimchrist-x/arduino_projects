/*
  Example for different sending methods
  
  https://github.com/sui77/rc-switch/
  
*/
#include <RCSwitch.h>

//specific code
char code[100]="000001000010";
short int pulse=320, repeat=5;
RCSwitch mySwitch = RCSwitch();
void setup() {

  Serial.begin(9600);
  
  // Transmitter is connected to Arduino Pin #10  
  mySwitch.enableTransmit(10);
  
  // Optional set protocol (default is 1, will work for most outlets)
  mySwitch.setProtocol(11);

  // Optional set pulse length.
  mySwitch.setPulseLength(pulse);
  
  // Optional set number of transmission repetitions.
  mySwitch.setRepeatTransmit(repeat);
  pinMode(4, OUTPUT);
  pinMode(7, INPUT);
  
}

void loop() {
  short int but_state;
  but_state=digitalRead(7);
  if (but_state==HIGH) {
    mySwitch.send(code);
    digitalWrite(4, HIGH);
    delay(pulse*repeat);
  }
  digitalWrite(4, LOW);
  
}
