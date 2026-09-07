const int mtrEble = 6;
const int mtrIn3 = 3;
const int mtrIn4 = 4;

const int PIRsig = 5;
const int tmpPin = A0;

const int ledGrn = 8;
const int ledRed = 2;

void setup() {
  pinMode(mtrEble, OUTPUT);
  pinMode(mtrIn3, OUTPUT);
  pinMode(mtrIn4, OUTPUT);
  pinMode(PIRsig, INPUT);
  pinMode(ledGrn, OUTPUT);
  pinMode(ledRed, OUTPUT);

  digitalWrite(ledRed, HIGH);
  digitalWrite(ledGrn, LOW);
}

void loop() {
  int motion = digitalRead(PIRsig);
  int val = analogRead(tmpPin);
  float t = (val * (5.0 / 1023.0) - 0.5) * 100;

  int speed = 0;

  if (motion == HIGH) {
    digitalWrite(mtrIn3, HIGH);
    digitalWrite(mtrIn4, LOW);
    digitalWrite(ledGrn, HIGH);
    digitalWrite(ledRed, LOW);

    if (t >= 30) speed = 255;
    else if (t >= 25) speed = map(t, 25, 30, 120, 200);
    else if (t >= 10) speed = map(t, 10, 25, 50, 120);

    analogWrite(mtrEble, speed);

    delay(15000);
  } else {
    digitalWrite(mtrIn3, LOW);
    digitalWrite(mtrIn4, LOW);
    digitalWrite(ledGrn, LOW);
    digitalWrite(ledRed, HIGH);
    analogWrite(mtrEble, 0);
  }
}
