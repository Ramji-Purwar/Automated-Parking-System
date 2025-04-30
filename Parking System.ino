a#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int entrySensor = 2;
const int exitSensor = 3;
const int spot1Sensor = 4;
const int spot2Sensor = 5;
const int servoPin = 9;

Servo myServo;
bool isGateOpen = false;
bool entryTriggered = false;
bool exitTriggered = false;
unsigned long detectionTime = 0;
const unsigned long returnDelay = 5000;

unsigned long spot1EntryTime = 0;
unsigned long spot2EntryTime = 0;
bool spot1WasOccupied = false;
bool spot2WasOccupied = false;

void setup() {
  pinMode(entrySensor, INPUT);
  pinMode(exitSensor, INPUT);
  pinMode(spot1Sensor, INPUT);
  pinMode(spot2Sensor, INPUT);
  
  myServo.attach(servoPin);
  myServo.write(0);
  
  lcd.init();
  lcd.backlight();
  lcd.print("Parking System");
  lcd.setCursor(0, 1);
  lcd.print("Initialized");
  
  Serial.begin(9600);
  delay(1000);
  lcd.clear();
}

void loop() {
  bool entryDetected = (digitalRead(entrySensor) == LOW);
  bool exitDetected = (digitalRead(exitSensor) == LOW);
  bool spot1Occupied = (digitalRead(spot1Sensor) == LOW);
  bool spot2Occupied = (digitalRead(spot2Sensor) == LOW);
  bool parkingFull = spot1Occupied && spot2Occupied;

  if (spot1Occupied && !spot1WasOccupied) {
    spot1EntryTime = millis();
    spot1WasOccupied = true;
  }
  if (spot2Occupied && !spot2WasOccupied) {
    spot2EntryTime = millis();
    spot2WasOccupied = true;
  }

  if (entryDetected && !isGateOpen) {
    if (!parkingFull) {
      myServo.write(90);
      isGateOpen = true;
      entryTriggered = true;
      detectionTime = millis();

      if (!spot1Occupied) {
        showLcdMessage("Welcome!", "Spot 1 free");
      } else {
        showLcdMessage("Welcome!", "Spot 2 free");
      }
    } else {
      showLcdMessage("PARKING FULL", "No spots available");
    }
    delay(300);
  }

  if (exitDetected && !isGateOpen) {
    myServo.write(90);
    isGateOpen = true;
    exitTriggered = true;
    detectionTime = millis();
    
    if (spot1WasOccupied && !spot1Occupied) {
      unsigned long parkingDuration = (millis() - spot1EntryTime) / 1000; // in seconds
      displayExitMessage(parkingDuration);
      spot1WasOccupied = false;
    } 
    else if (spot2WasOccupied && !spot2Occupied) {
      unsigned long parkingDuration = (millis() - spot2EntryTime) / 1000; // in seconds
      displayExitMessage(parkingDuration);
      spot2WasOccupied = false;
    } 
    else {
      showLcdMessage("Thank You!", "Drive safe!");
    }
    delay(300);
  }

  if ((entryTriggered && exitDetected && isGateOpen) || 
      (exitTriggered && entryDetected && isGateOpen)) {
    delay(500);
    myServo.write(0);
    isGateOpen = false;
    entryTriggered = false;
    exitTriggered = false;
    showLcdMessage("Gate Closed", "");
    delay(300);
  }

  if (isGateOpen && (millis() - detectionTime > returnDelay)) {
    myServo.write(0);
    isGateOpen = false;
    entryTriggered = false;
    exitTriggered = false;
    showLcdMessage("Gate Closed", "Timeout");
    delay(300);
  }

  delay(30);
}

void displayExitMessage(unsigned long durationSec) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Thank You!");
  
  lcd.setCursor(0, 1);
  lcd.print("TIME: ");
  
  unsigned long hours = durationSec / 3600;
  unsigned long minutes = (durationSec % 3600) / 60;
  unsigned long seconds = durationSec % 60;
  
  if (hours > 0) {
    lcd.print(hours);
    lcd.print("h ");
  }
  if (minutes > 0 || hours > 0) {
    lcd.print(minutes);
    lcd.print("m ");
  }
  lcd.print(seconds);
  lcd.print("s");
}

void showLcdMessage(String line1, String line2) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);
}
