int led = 3;
int interruptPin = 2;
bool state = LOW;

void setup(){
  pinMode(interruptPin, INPUT);
  pinMode(led, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), interrupt, RISING);
}


void loop(){
  digitalWrite(led, state);
}

void interrupt(){
  static unsigned long vorigeInterrupt = 0;
  unsigned long interruptTijd = millis();
  if (interruptTijd - vorigeInterrupt > 100){
    state =! state;
  }
  vorigeInterrupt = interruptTijd;
}
