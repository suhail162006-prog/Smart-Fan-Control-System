// Smart Fan Control System - ER4006 Coursework
// PIN Definitions 
const int mtrEble = 6;
const int mtrIn3 = 3;
const int mtrIn4 = 4;
const int PIRsig = 5;
const int tmpPin = A0;
const int ledGrn = 8;
const int ledRed = 2;
const int SPEED_L = 64; //LOW
const int SPEED_M = 128; //MEDIUM
const int SPEED_H = 255; //HIGH
const unsigned long Fan_on = 15000;//15 sec stop time
unsigned long PIRstopt = 0; // hold stop time
bool Hold = false;// Holding time starts off false with red led

void setup() {
  pinMode(mtrEble,OUTPUT);
  pinMode(mtrIn3,OUTPUT);
  pinMode(mtrIn4,OUTPUT);
  pinMode(PIRsig,INPUT);
  pinMode(ledGrn,OUTPUT);
  pinMode(ledRed,OUTPUT);

  FanOff();
  Serial.begin(9600);
}

//default starting point - OFF
void FanOff() { 
  analogWrite(mtrEble,0);
  digitalWrite(mtrIn3,LOW);
  digitalWrite(mtrIn4,LOW);
  digitalWrite(ledRed,HIGH);
  digitalWrite(ledGrn,LOW);

  Hold = false;
  PIRstopt = 0;
}
//ADC calculation
float ReadTemp() {
  int read = analogRead(tmpPin);
  float volts = read *(5.0 / 1023.0);
  return (volts - 0.5)*100.0;
}
//Temperature sensitve fan speed
void runFan(float t) {
  int speed;

  if(t < 10.0)
  {FanOff();           
    return;
  }
  else if(t < 25.0)
  {speed = SPEED_L;
  }
  else if(t < 30.0)
  {speed = SPEED_M;
  }
  else
  {speed = SPEED_H;
  }

  digitalWrite(mtrIn3,HIGH);
  digitalWrite(mtrIn4,LOW);//  motor spins
  analogWrite(mtrEble,speed);
  digitalWrite(ledGrn,HIGH);
  digitalWrite(ledRed,LOW);
  Serial.print("Fan ON PWM: "); 
  Serial.println(speed);
} 


void loop() {
  bool motion = digitalRead(PIRsig);
  float ftemp = ReadTemp();

  Serial.print("Motion: "); // 
  Serial.println(motion ? "POSITIVE" : "NEGATIVE");// Motion detection
  Serial.print("Temp:");
  Serial.print(ftemp); 
  Serial.println(" C");// TMP sensor Temperature

  if (motion) {
    Hold = false;
    PIRstopt = 0;
     runFan(ftemp);
  } 
    
  else {
    if (!Hold) {
      Hold = true;
      PIRstopt = millis();
      Serial.println("MOTION LOST = 15s hold started");
    }

    if (millis()-PIRstopt >= Fan_on) {
      FanOff();
      Serial.println("Fan OFF");
    } }
  delay(500);
}
