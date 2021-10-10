
int hmeter=A0;
double hval=0.0;
int blue_led=3, yel_led=5, red_led=6;
int _delay=1;
int samples=10000;


void setup() {
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  hval=0.0;
  for (int i=0; i<samples;i++) {
    hval+=analogRead(hmeter);
    delay(_delay);
  }
  hval = hval/samples;
  Serial.println(hval);
  if (hval>30 && hval<50) {
    digitalWrite(blue_led, HIGH);
  }
  else {
    digitalWrite(blue_led, LOW);
  }
  if (hval>50 && hval<70) {
    digitalWrite(yel_led, HIGH);
  }
  else {
    digitalWrite(yel_led, LOW);
  }
  if (hval>70) {
    digitalWrite(red_led, HIGH);
  }
  else {
    digitalWrite(red_led, LOW);
  }
}
