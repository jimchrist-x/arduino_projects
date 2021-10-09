int red_1=12, red_2=7, yel_1=11, yel_2=6, blue_1=10, blue_2=5;
int delay_yel=2000;
int delay_r_b = 5000;
void set_13() {
  digitalWrite(13, 1);
  delay(10);
  digitalWrite(13, 0);
}
void setup() {
  pinMode(13, OUTPUT);
  //Phanari 1
  pinMode(red_1, OUTPUT);
  pinMode(yel_1, OUTPUT);
  pinMode(blue_1, OUTPUT);
  // Phanari 2
  pinMode(red_2, OUTPUT);
  pinMode(yel_2, OUTPUT);
  pinMode(blue_2, OUTPUT);
}

void loop() {
  digitalWrite(yel_1, HIGH);
  set_13();
  digitalWrite(blue_1, LOW);
  set_13();
  delay(delay_yel);
  digitalWrite(yel_1, LOW);
  set_13();
  digitalWrite(red_1, HIGH);
  set_13();
  digitalWrite(red_2, LOW);
  set_13();
  digitalWrite(yel_2, LOW);
  set_13();
  digitalWrite(blue_2, HIGH);
  set_13();
  delay(delay_r_b);
  digitalWrite(red_1, LOW);
  set_13();
  digitalWrite(blue_1, HIGH);
  set_13();
  digitalWrite(blue_2, LOW);
  set_13();
  digitalWrite(yel_2, HIGH);
  set_13();
  delay(delay_yel);
  digitalWrite(yel_2, LOW);
  set_13();
  digitalWrite(red_2, HIGH);
  set_13();
  delay(delay_r_b);
}
