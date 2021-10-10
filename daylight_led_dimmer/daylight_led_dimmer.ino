int led=3, photo_res=A0;
double pt_val, led_val;
void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

void loop() {
  pt_val=analogRead(photo_res);
  led_val=255./1023.*pt_val;
  Serial.println(led_val);
  analogWrite(led, led_val);
  delay(100);
}
