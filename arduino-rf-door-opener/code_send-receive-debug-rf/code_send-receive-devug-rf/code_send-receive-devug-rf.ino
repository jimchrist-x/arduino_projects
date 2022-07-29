#include <RCSwitch.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
short int pulse=312, repeat=10;
RCSwitch mySwitch = RCSwitch();
RCSwitch theSwitch = RCSwitch();
static const char alphabet[] ="01";
static const int alphabetSize = sizeof(alphabet) - 1;
int count=1;
int buzzerpin=8;
void bruteImpl(char* str, int index, int maxDepth) {
    for (int i = 0; i < alphabetSize; ++i)
    {
        str[index] = alphabet[i];

        if (index == maxDepth - 1) {
           /*Serial.print(count);
           Serial.print(" : ");
           Serial.print(str);
           Serial.print("\n");*/
           mySwitch.send(str);
           if (theSwitch.available()) {
               output(mySwitch.getReceivedValue(), mySwitch.getReceivedBitlength(), mySwitch.getReceivedDelay(), mySwitch.getReceivedRawdata(),mySwitch.getReceivedProtocol());
               mySwitch.resetAvailable();
           }
           digitalWrite(4, HIGH);
           delay(50);
           digitalWrite(4, LOW);
           delay(50);
           count++;
        }
        
        else bruteImpl(str, index + 1, maxDepth);
        if (digitalRead(7)==HIGH) break;
    }
}
void setup() {
  Serial.begin(9600);
  
  // Transmitter is connected to Arduino Pin #10  
  mySwitch.enableTransmit(10);
  
  // Optional set protocol (default is 1, will work for most outlets)
  mySwitch.setProtocol(1);

  // Optional set pulse length.
  mySwitch.setPulseLength(pulse);
  
  // Optional set number of transmission repetitions.
  mySwitch.setRepeatTransmit(repeat);
  pinMode(4, OUTPUT);
  pinMode(7, INPUT);
  pinMode(buzzerpin, OUTPUT);
  theSwitch.enableReceive(0);
}

void loop() {
  short int but_state=digitalRead(7);
  if (but_state==HIGH) {
    char* buf = malloc(13);
    memset(buf, 0, 13);
    for (int i=0;i<=150;i++) {
    digitalWrite(buzzerpin, HIGH);
    delay(2);
    digitalWrite(buzzerpin, LOW);
    delay(2);
    }
    bruteImpl(buf, 0, 12);
    for (int i=0;i<=400;i++) {
    digitalWrite(buzzerpin, HIGH);
    delay(3);
    digitalWrite(buzzerpin, LOW);
    delay(3);
    }
    free(buf);
  }
}
