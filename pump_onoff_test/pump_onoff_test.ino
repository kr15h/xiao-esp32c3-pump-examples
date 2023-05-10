int ledPin = D0;
int motPin = D2;
int ledState = 0;
int motState = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(motPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, ledState);
  digitalWrite(motPin, motState);
  ledState = !ledState;
  motState = !motState;
  delay(2000);
}
