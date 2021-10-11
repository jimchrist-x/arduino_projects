int led_pin=3;
double led_val, pot_val;
int pot_pin=A1;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  pot_val=analogRead(pot_pin);
  led_val=map(pot_val, 311, 1023, 0, 255);
  Serial.println(led_val);
  analogWrite(led_pin, led_val);
  delay(100);
}
