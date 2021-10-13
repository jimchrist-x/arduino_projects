int buzz_pin=9;
int _delay=500;
void song();
void setup() {
  Serial.begin(9600);
  pinMode(buzz_pin, OUTPUT);
}

void loop() {
  song();
  delay(_delay);
}
void song() {
  tone(buzz_pin, 523.25);
  delay(_delay);
  noTone(buzz_pin);
  tone(buzz_pin, 587.33);
  delay(_delay);
  noTone(buzz_pin);
  tone(buzz_pin, 698.46);
  delay(_delay);
  noTone(buzz_pin);
  tone(buzz_pin, 587.33);
  delay(_delay);
  noTone(buzz_pin);
  tone(buzz_pin, 880.0);
  delay(_delay);
  noTone(buzz_pin);
  tone(buzz_pin, 783.99);
  delay(_delay);
  noTone(buzz_pin);
  tone(buzz_pin, 698.46);
  delay(_delay);
  noTone(buzz_pin);
}
