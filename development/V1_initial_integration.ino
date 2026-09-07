// Pin Definitions
const int mtrEble = 6;   // PWM (L293D EN)
const int mtrIn3    = 3;  // L293D IN1
const int mtrIn4    = 4;  // L293D IN2

const int PIRsig     = 5;   // Motion sensor
const int tmpPin     = A0;  // TMP sensor

const int ledGrn = 8; // Green LED 
const int ledRed = 2; // Red LED
 

void setup() {
  pinMode(mtrEble, OUTPUT);
  pinMode(mtrIn3, OUTPUT);
  pinMode(mtrIn4, OUTPUT);

  pinMode(PIRsig, INPUT);

  pinMode(ledGrn, OUTPUT);
  pinMode(ledRed, OUTPUT);
  
  
  // Motor OFF initially
  digitalWrite(mtrIn3, LOW);
  digitalWrite(mtrIn4, LOW);
  analogWrite(mtrEble, 0);
  digitalWrite(ledRed, HIGH);
}

void loop() {
  // Reading Temperature 
  int SnsrValue = analogRead(tmpPin);
  float voltage = SnsrValue   * (5.0 / 1023.0);
  float Tempchnge = (voltage - 0.5) * 100;
  

   // Reading Motion 
  int motion = digitalRead(PIRsig);

  int speedValue = 0;
  
   digitalWrite(ledRed, HIGH);
  

  if (motion == HIGH){
    digitalWrite(mtrIn3, HIGH);
    digitalWrite(mtrIn4, LOW);
    speedValue = 0;
// OFF indicator
    digitalWrite(ledGrn, HIGH); 
    digitalWrite(ledRed, LOW);
    delay(15000);
  }
  else {
    // Motion detected = Motor ON
    digitalWrite(mtrIn3, LOW);
    digitalWrite(mtrIn4, LOW);
    
    digitalWrite(ledGrn, LOW);
    
    
      // ON indicator

    // --- Temperature-based speed ---
    if (Tempchnge < 10) {
      speedValue = 0;
    } 
    else if (Tempchnge < 25) {
      speedValue = map(Tempchnge, 10, 25, 50, 120);
    } 
    else if (Tempchnge < 30) {
      speedValue = map(Tempchnge, 25, 30, 120, 200);
    } 
    else {
      speedValue = 255;
    }

    // --- LED Indicators ---
    digitalWrite(ledGrn, Tempchnge >= 25);
    digitalWrite(ledRed, Tempchnge >= 30);
  }

  // Apply motor speed
  analogWrite(mtrEble, speedValue);

  delay(500);
}

