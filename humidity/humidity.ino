
int hmeter=A0;
double hval=0.0;
int blue_led=3, yel_led=5, red_led=6;
int ledval;
void setup() {
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i=0; i<300;i++) {
    hval+=analogRead(hmeter);
    delay(10);
  }
  hval = hval/300;
  Serial.println(hval);
  if (hval>30) {
    digitalWrite(blue_led, HIGH);
  }
  else {
    digitalWrite(blue_led, LOW);
  }
  if (hval>50) {
    digitalWrite(yel_led, HIGH);
  }
  else {
    digitalWrite(blue_led, LOW);
  }
  if (hval>60) {
    digitalWrite(red_led, HIGH);
  }
  else {
    digitalWrite(blue_led, LOW);
  }
  hval=0;
}
