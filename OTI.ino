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
  
  // Start communication and attach motor
  Serial.begin(9600);
  myServo.attach(servoPin);
  
  // Initial safety state
  digitalWrite(greenLed, HIGH);
  digitalWrite(redLed, LOW);
  noTone(buzzer);
  Serial.println("System Rebooted. Starting Scan...");
}

void loop() {
  // Rotate forward 15 to 165
  for(int i = 15; i <= 165; i++){  
    processRadar(i);
  }
  // Rotate backward 165 to 15
  for(int i = 165; i > 15; i--){  
    processRadar(i);
  }
}

void processRadar(int angle) {
  myServo.write(angle);
  delay(40); // Gives simulation time to process
  
  int distance = getDistance();
  
  // Logic: If object is closer than 100cm (approx 1 meter)
  if (distance > 2 && distance < 250) {
    digitalWrite(redLed, HIGH);   // Danger LED on
    digitalWrite(greenLed, LOW);  // Safe LED off
    tone(buzzer, 100);           // Continuous beep
    
    Serial.print("TARGET DETECTED | Angle: ");
    Serial.print(angle);
    Serial.print(" | Distance: ");
    Serial.println(distance);
  } 
  else {
    digitalWrite(redLed, LOW);    // Danger LED off
    digitalWrite(greenLed, HIGH); // Safe LED on
    noTone(buzzer);               // Silence
    
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
  
  // We use a 25000us timeout for the simulation pulse
  long duration = pulseIn(echoPin, HIGH, 25000); 
  
  // Speed of sound calculation (cm)
  int d = duration * 0.034 / 2;
  return d;
}