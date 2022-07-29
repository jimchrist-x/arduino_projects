#include <RCSwitch.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
short int pulse=312, repeat=5;
RCSwitch mySwitch = RCSwitch();
static const char alphabet[] ="01";
static const int alphabetSize = sizeof(alphabet) - 1;
int buzzerpin=8;
int count=1;
int red_led_pin=4;
void bruteImpl(char* str, int index, int maxDepth) {
    for (int i = 0; i < alphabetSize; ++i)
    {
        str[index] = alphabet[i];

        if (index == maxDepth - 1) {
           Serial.print(count);
           Serial.print(" : ");
           Serial.print(str);
           Serial.print("\n");
           mySwitch.send(str);
           //digitalWrite(red_led_pin, HIGH);
           //delay(50);
           //digitalWrite(red_led_pin, LOW);
           //delay(50);
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
  mySwitch.setProtocol(11);

  // Optional set pulse length.
  mySwitch.setPulseLength(pulse);
  
  // Optional set number of transmission repetitions.
  mySwitch.setRepeatTransmit(repeat);
  pinMode(red_led_pin, OUTPUT);
  pinMode(7, INPUT);
  pinMode(buzzerpin, OUTPUT);
}

void loop() {
  short int but_state=digitalRead(7);
  if (but_state==HIGH) {
    char* buf_12 = (char *)malloc(13);
    //char* buf_8 = (char *)malloc(9);
    memset(buf_12, 0, 13);
    //memset(buf_8, 0, 9);
    for (int i=0;i<=150;i++) {
    digitalWrite(buzzerpin, HIGH);
    delay(2);
    digitalWrite(buzzerpin, LOW);
    delay(2);
    }
    bruteImpl(buf_12, 0, 12);
    count=1;
    //bruteImpl(buf_8, 0, 8);
    //count=1;
    for (int i=0;i<=400;i++) {
    digitalWrite(buzzerpin, HIGH);
    delay(3);
    digitalWrite(buzzerpin, LOW);
    delay(3);
    }
    free(buf_12);
    //free(buf_8);
  }
}
