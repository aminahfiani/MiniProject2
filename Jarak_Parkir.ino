#include <SevSeg.h>
#include <elapsedMillis.h>

SevSeg sevseg;
elapsedMillis timeElapsed;
unsigned int interval = 500;
byte theNum = 0;
const int trigPin = 2;
const int echoPin = 3;
const int ledHijau = A3;
const int ledBiru = A2;
const int ledMerah = A0;
int distance;
int duration;

void setup() 
{
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledHijau, OUTPUT);
  pinMode(ledBiru, OUTPUT);
  pinMode(ledMerah, OUTPUT);

  byte numDigits=1;
  byte digitPins[] = {};
  byte segmentPins[]= {4,5,6,7,8,9,10,11};
  bool resistorsOnSegments = true;
  
  byte hardwareConfig = COMMON_CATHODE;
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(100);
}
byte angka = 0;

void loop() 
{
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance=duration*0.034/2;
  delay(1000);

  if (distance > 50) //Jika jarak lebih dari 30cm
  
{
      Serial.println("Jarak aman");
      angka  = 8;
      digitalWrite(ledHijau, HIGH); //Menyala
      digitalWrite(ledBiru, LOW); //Mati
      digitalWrite(ledMerah, LOW); //Mati
}

  else if (distance > 10) //Jika kurang dari 30cm
  
{
      Serial.println("Hati-hati");
      angka = 5;
      digitalWrite(ledHijau, LOW);
      digitalWrite(ledBiru, HIGH);
      digitalWrite(ledMerah, LOW);   
      
}

  else if (distance <= 10) //Jika kurang dari 30cm
  
{
      Serial.println("Bahaya");
      angka = 3;
      digitalWrite(ledHijau, LOW);
      digitalWrite(ledBiru, LOW);
      digitalWrite(ledMerah, HIGH);   
      
}

{
 Serial.print("Jarak : ");
 Serial.print(distance);
 Serial.println(" cm");
 Serial.println();
 delay(120);
 sevseg.setNumber(angka, angka%2);
 sevseg.refreshDisplay();
}
}
