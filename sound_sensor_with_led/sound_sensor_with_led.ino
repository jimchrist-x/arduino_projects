int audio_sens_pin = A0, val; 
int led_pin=8;
void setup() {
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
}

void loop() {
  val=analogRead(audio_sens_pin);
  Serial.println(val);
  if (val>30) {
    digitalWrite(led_pin, HIGH);
    delay(1000);
  }
  else {
    digitalWrite(led_pin, LOW);
  }
}
