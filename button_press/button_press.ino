int red=8, blue=7;
int button=2;
int button_old=1;
int button_new;
int led_state=0;
int del=100;
void setup() {
  // put your setup code here, to run once:
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(button, INPUT);
  digitalWrite(red, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  button_new=digitalRead(button);

  if (button_old==1 && button_new==0) {
    if (led_state==0){
      digitalWrite(blue, HIGH);
      digitalWrite(red, LOW);
      led_state=1;
    }
    else if (led_state==1) {
      digitalWrite(red, HIGH);
      digitalWrite(blue, LOW);
      led_state=0;
    }
  }
  button_old=button_new;
  delay(del);
}
