#include <Servo.h>

// Pin Definitions
const int trigPin = 9;
const int echoPin = 10;
const int servoPin = 11;
const int greenLed = 7;
const int redLed = 8;
const int buzzer = 13;

Servo myServo;

void setup() {
  // Pin setup
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  
  Serial.begin(9600);
  myServo.attach(servoPin);
  
  // Initial safety state
  digitalWrite(greenLed, HIGH);
  digitalWrite(redLed, LOW);
  noTone(buzzer);
  Serial.println("System Rebooted. Starting Scan...");
}

void loop() {
  for(int i = 15; i <= 165; i++){  
    processRadar(i);
  }
  for(int i = 165; i > 15; i--){  
    processRadar(i);
  }
}

void processRadar(int angle) {
  myServo.write(angle);
  delay(40);
  
  int distance = getDistance();
  
  // If object is closer than 250cm (can tweak based on actual physical component testings)
  if (distance > 2 && distance < 250) {
    digitalWrite(redLed, HIGH);   // Danger LED on
    digitalWrite(greenLed, LOW);  // Safe LED off
    tone(buzzer, 100);         
    
    Serial.print("TARGET DETECTED | Angle: ");
    Serial.print(angle);
    Serial.print(" | Distance: ");
    Serial.println(distance);
  } 
  else {
    digitalWrite(redLed, LOW);    // Red LED off
    digitalWrite(greenLed, HIGH); // Green LED on
    noTone(buzzer);               // Low Signal
    
    Serial.print("Scanning... | Angle: ");
    Serial.print(angle);
    Serial.print(" | Distance: ");
    Serial.println(distance);
  }
}

int getDistance() { 
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH, 25000); 
  
  // Speed of sound calculation in centimeters
  int d = duration * 0.034 / 2;
  return d;
}
