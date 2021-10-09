
int hmeter=A0;
int hval;
int blue_led=3, yel_led=5, red_led=6;
int ledval;
void setup() {
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  hval=analogRead(hmeter);
  Serial.println(hval);
  ledval=(255./100.)*hval;

  if (ledval>0) {
    digitalWrite(blue_led, ledval);
  }
  if (ledval>84) {
    digitalWrite(yel_led, ledval);
  }
  if (ledval>168) {
    digitalWrite(red_led, ledval);
  }
  delay(180);
}
