# Automated Parking System
**Course Project – ES-116: Principles and Applications of Electrical Engineering**  
*Indian Institute of Technology, Gandhinagar – 2025*

---

## 🧠 Overview

This project was developed as part of the ES-116 course at IIT Gandhinagar, where students applied foundational electrical engineering concepts to a real-world scenario. The goal was to design an **Automated Parking System** that manages vehicle entry and exit, tracks parking space availability, and communicates in real-time using a servo-controlled gate and LCD display.

---

## 🎯 Objective

To develop a **smart parking assistant** using Arduino, IR sensors, and a servo motor that:
- Detects vehicle entry and exit.
- Monitors and displays parking spot availability.
- Calculates and displays parking duration.

---

## 🔧 Components Used

- Arduino UNO
- 4 IR Sensors (2 for entry/exit, 2 for spot monitoring)
- Servo Motor (for gate control)
- 16x2 I2C LCD Display
- Jumper Wires and Breadboard
- USB Cable and Power Supply

---

## 🛠️ System Design & Logic

### **Entry Detection & Control**
- When a vehicle triggers the **entry sensor**, the system checks if any of the two parking spots are free.
- If available, the gate opens using the **servo motor**, and the LCD shows:
  - A welcome message.
  - Which spot is free (Spot 1 or Spot 2).
- If the parking is full, the gate remains closed and the display shows `PARKING FULL`.

### **Exit Detection & Time Calculation**
- When a vehicle triggers the **exit sensor**, the gate opens automatically.
- The system checks which spot was vacated and calculates the total time parked using the `millis()` function.
- This time is displayed on the LCD in `Hh Mm Ss` format.

### **Auto Gate Closing**
- The system includes logic to:
  - Automatically close the gate after a delay.
  - Close the gate if both entry and exit triggers are processed.
  - Reset all trigger flags to prevent false positives.

---

## 📂 Code Functionality

The Arduino code handles:
- Digital reads from IR sensors.
- Conditional gate control via a servo motor.
- LCD output with `LiquidCrystal_I2C`.
- Time tracking for each parking spot.
- Debouncing and timing safeguards for clean operation.

---

## 📺 Demonstration

*A video demonstration is available showing the working model in real-time.*

📹 *[https://www.youtube.com/watch?v=vqLUUqFr0BI&authuser=0]*

---

## 🚀 Future Improvements

- Add support for more parking spots using arrays.
- Integrate with Wi-Fi/Bluetooth modules for real-time remote monitoring.
- Use RFID or License Plate Recognition for secure access control.
- Add payment integration for commercial deployment.

---

Thank you!
