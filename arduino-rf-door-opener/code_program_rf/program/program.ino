#include <SoftwareSerial.h>
#include <string.h>
#include <RCSwitch.h>
#define components 10
#define TRANSMITIONS 5
static unsigned short int r_data_led=4,r_mode_led=A5,y_mode_led=A4,b_mode_led=A3, button_send=7, button_mode=13, buzzer=8, blue_tx=12, blue_rx=11;
char flag='1', rec_mode='1',send_mode='2',brute_mode='3',send_='8',stop_='9';
unsigned short int delay_=0, protocol=1, bitlen=12, count=1, up_fall=0;
unsigned int decimal=0;
static const char alphabet[] ="01";
static const int alphabetSize = sizeof(alphabet) - 1; 
SoftwareSerial blue_tooth(blue_rx, blue_tx); // rx | tx
RCSwitch receiver = RCSwitch();
RCSwitch transmitter = RCSwitch();
void bruteImpl(char* str, int index, int maxDepth) {
    for (int i = 0; i < alphabetSize; ++i)
    {
        str[index] = alphabet[i];
        if (index == maxDepth - 1) {
           Serial.print(count);
           Serial.print(" : ");
           Serial.print(str);
           Serial.print("\n");
           transmitter.send(str);
           count++;
        }
        else bruteImpl(str, index + 1, maxDepth);
        if (blue_tooth.available()) flag=blue_tooth.read();
        if (digitalRead(button_send)==HIGH || flag==stop_) break;
    }
}
void buzz1() {
  for (int i=0; i<150;i++) {
    digitalWrite(buzzer, HIGH);
    delay(1);
    digitalWrite(buzzer, LOW);
    delay(1);
  }
}
void buzz2() {
  for (int i=0; i<80;i++) {
    digitalWrite(buzzer, HIGH);
    delay(3);
    digitalWrite(buzzer, LOW);
    delay(3);
  }
}
void setup() {
  Serial.begin(9600);
  blue_tooth.begin(9600);
  pinMode(r_data_led, OUTPUT);
  pinMode(button_send, INPUT);
  pinMode(button_mode, INPUT);
  pinMode(buzzer, OUTPUT);
  Serial.println("Bluetooth ready. Default passwd : 1234. Waiting to connect...");
  receiver.enableReceive(0);
  transmitter.enableTransmit(10);
}
void loop() {
  if (blue_tooth.available()) {
    flag=blue_tooth.read();
    Serial.print(flag);
    buzz1();
  }
  if (digitalRead(button_mode) == HIGH) {
    buzz1();
    if (flag==rec_mode) {
      up_fall=0;
      flag++;
      Serial.println("Mode : SEND");
    }
    else if (flag==send_mode) {
      if (up_fall==0) {
        flag++;
        Serial.println("Mode : BRUTEFORCE");
      }
      else if (up_fall==1) {
        flag--;
        Serial.println("Mode : RECEIVE");
      }
      else Serial.println("An error occured!!!");
    }
    else if (flag == brute_mode) {
      up_fall=1;
      flag--;
      Serial.println("Mode : SEND");
    }
    else Serial.println("An error occured!!!");
    delay(560);
  }
  if (flag == rec_mode) {
    analogWrite(b_mode_led, 255);
    analogWrite(y_mode_led, 0);
    analogWrite(r_mode_led, 0);
    if (receiver.available()) {
      digitalWrite(r_data_led, HIGH);
      decimal=receiver.getReceivedValue();
      delay_=receiver.getReceivedDelay();
      protocol=receiver.getReceivedProtocol();
      bitlen=receiver.getReceivedBitlength();
      Serial.println("Received rf signal!!!");
      Serial.println("=========================");
      Serial.print("||\tDECIMAL\t|| ");
      Serial.print(decimal);
      Serial.print(" / ");
      Serial.print(bitlen);
      Serial.print(" Bit");
      Serial.println("\t||");
      Serial.print("||\tDELAY\t|| ");
      Serial.print(delay_);
      Serial.println("\t||");
      Serial.print("||\tPROTOCOL|| ");
      Serial.print(protocol);
      Serial.println("\t||");
      Serial.print("\n\n\n\n");
      //output(receiver.getReceivedValue(), receiver.getReceivedBitlength(), receiver.getReceivedDelay(), receiver.getReceivedRawdata(),receiver.getReceivedProtocol());
      receiver.resetAvailable();
      delay(560);
      digitalWrite(r_data_led, LOW);
    }
  }
  if (flag == send_mode) {
    analogWrite(y_mode_led, 255);
    analogWrite(b_mode_led, 0);
    analogWrite(r_mode_led, 0);
    transmitter.setProtocol(protocol);
    transmitter.setPulseLength(delay_);
    transmitter.setRepeatTransmit(TRANSMITIONS);
    if (digitalRead(button_send)==HIGH || flag==send_) {
      Serial.print("Sending "); Serial.print(decimal); Serial.print(" / "); Serial.print(bitlen); Serial.println(" Bit...");
      buzz2();
      transmitter.send(decimal, bitlen);
      digitalWrite(r_data_led, HIGH);
      if (delay_<=0) delay(300*TRANSMITIONS);
      else delay(delay_*TRANSMITIONS);
      digitalWrite(r_data_led, LOW);
      flag=send_mode;
    }
  }
  if (flag == brute_mode) {
    analogWrite(r_mode_led, 255);
    analogWrite(b_mode_led, 0);  
    analogWrite(y_mode_led, 0);
    transmitter.setPulseLength(delay_);
    transmitter.setRepeatTransmit(TRANSMITIONS);
    if (digitalRead(button_send)==HIGH || flag==send_) {
        Serial.println("Starting bruteforce mode...");
        char* buf_12 = (char *)malloc(13);
        memset(buf_12, 0, 13);
        buzz2();
        digitalWrite(r_data_led, HIGH);
        for (int i=1;i<=12;i++) {
          transmitter.setProtocol(i);
          bruteImpl(buf_12, 0, 12);
          if (digitalRead(button_send)==HIGH || flag==stop_) break; 
        }
        digitalWrite(r_data_led, LOW);
        count=1;
        buzz2();
        buzz2();
        free(buf_12);
        flag=brute_mode;
    }
  }
}
