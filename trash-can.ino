#include <Servo.h>

Servo lidServo;

const int trigPin = 5;
const int echoPin = 6;
const int servoPin = 9;

// CLOCKWISE OPERATION: Opened an additional 30% less (Stopped at 88 degrees)
const int CLOSED_ANGLE = 0;    
const int OPEN_ANGLE = 88;

const int triggerDistance = 25; // Opens if a hand is closer than 25 cm
const int minDistance = 8;      // Blocks glitch readings below 8cm

long duration;
int distance;
bool busy = false;

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  lidServo.attach(servoPin);
  lidServo.write(CLOSED_ANGLE); // Starts at 0 degrees (Closed)
  delay(300);                  
  lidServo.detach();

  Serial.println("Smart Trash Can Ready - Highly Restricted Lift V8");
}

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  return distance;
}

void loop() {
  int currentDistance = getDistance();

  Serial.print("Distance: ");
  Serial.print(currentDistance);
  Serial.println(" cm");

  if (currentDistance >= minDistance &&
      currentDistance <= triggerDistance &&
      !busy) {

    busy = true;
    lidServo.attach(servoPin);

    // CLOCKWISE OPEN: Increments from 0 up to 88
    Serial.println("====== OPENING CLOCKWISE ====== ");
    for (int pos = CLOSED_ANGLE; pos <= OPEN_ANGLE; pos += 2) { // Smoother, smaller steps for short range
      lidServo.write(pos);
      delay(15);
    }

    // HOLD TIME: Keeps lid open for 1.5 seconds
    delay(1500);

      // COUNTER-CLOCKWISE CLOSE: Decrements from 88 down to 0
      Serial.println("====== CLOSING COUNTER-CLOCKWISE ====== ");
    for (int pos = OPEN_ANGLE; pos >= CLOSED_ANGLE; pos -= 2) {
      lidServo.write(pos);
      delay(15);
    }

    lidServo.detach();

    // Settle delay before scanning for hands again
    Serial.println("Settle Delay Active...");
    delay(50);

    busy = false;
  }

  delay(10);
}
