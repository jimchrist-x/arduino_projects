double ptvalue; // Photoresistant value
int rgb_red=10, rgb_green=9, rgb_blue=11;
int ptpin=A0;
int rgb_on_off=8;
void setcolor(int red, int green, int blue);

void setup() {
  Serial.begin(9600);
  pinMode(rgb_red, OUTPUT);
  pinMode(rgb_green, OUTPUT);
  pinMode(rgb_blue, OUTPUT);
  pinMode(rgb_on_off, OUTPUT);
  delay(1000);
}

void loop() {
  ptvalue=analogRead(ptpin);
  Serial.println(ptvalue);
  if (ptvalue>500) {
    digitalWrite(rgb_on_off, HIGH);
    setcolor(255, 0, 0);
    delay(200);
    setcolor(0, 0, 255);
    
  } else {
    digitalWrite(rgb_on_off, LOW);
  }
  delay(200);
}
void setcolor(int red, int green, int blue) {
  analogWrite(rgb_red, red);
  analogWrite(rgb_green, green);
  analogWrite(rgb_blue, blue);
}
