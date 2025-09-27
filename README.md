# Fingerprint-Based Home Security System

![Arduino](https://img.shields.io/badge/Platform-Arduino-blue)
![License](https://img.shields.io/badge/License-MIT-green)

This project demonstrates a fingerprint enrollment and access control system using an Arduino, Adafruit AS608 Fingerprint Sensor, 16×2 I2C LCD, and buzzer. Users can enroll fingerprints and then use them to grant or deny access.

---

## Features

### 1. Fingerprint Enrollment
- Register fingerprints with unique IDs (1–127)
- Verifies fingerprints by matching two scans
- Stores templates in the sensor’s internal memory

### 2. Access Control System
- Checks fingerprints against enrolled IDs
- Displays status on a 16×2 I2C LCD
- Uses buzzer for audio feedback:
  - Short beep for access granted
  - Long beep for access denied

---

## Hardware Required
- Arduino Uno (or compatible)  
- Adafruit AS608 Fingerprint Sensor  
- 16×2 I2C LCD (LiquidCrystal_I2C)  
- Buzzer  
- Jumper wires  
- Breadboard (optional)  

---

## Arduino UNO Pin Connections

| Arduino Pin | Connects To              | Notes |
|------------|-------------------------|-------|
| 5V         | VCC of AS608 fingerprint sensor | Sensor works on 3.3–6 V, 5 V recommended |
| GND        | GND of AS608            | Must share a common ground with all devices |
| D2         | TX of AS608             | Arduino receives data → cross-connect sensor TX to Arduino RX (D2) |
| D3         | RX of AS608             | Arduino sends data → cross-connect sensor RX to Arduino TX (D3) |
| 5V         | VCC of 16×2 I2C LCD     | LCD backlight and logic power |
| GND        | GND of LCD              | Same common ground |
| A4 (SDA)   | SDA of LCD module       | I2C data line |
| A5 (SCL)   | SCL of LCD module       | I2C clock line |
| D6         | Positive (+) terminal of buzzer | For tone() output |
| GND        | Negative (−) terminal of buzzer | Common ground |

---

## Circuit Setup

Here’s the actual setup of the project:

![Hardware Setup](images/hardware.jpg)  
Breadboard with Arduino, fingerprint sensor, I2C LCD, and buzzer connected.

---

## LCD Demo

*Place Finger Prompt*  

![LCD Prompt](images/lcd_prompt.jpg)  

*Access Granted*  

![LCD Access Granted](images/lcd_granted.jpg)  

*Access Denied*  

![LCD Access Denied](images/lcd_denied.jpg)  

---

## Software Required
- Arduino IDE  
- Adafruit Fingerprint Sensor Library  
- LiquidCrystal_I2C Library  
- SoftwareSerial Library (built-in with Arduino IDE)  

---

## Installation

1. Install the required libraries in Arduino IDE.  
2. Connect the hardware according to the pin table and images.  
3. Upload the enrollment sketch (FingerprintEnroll.ino) to register fingerprints.  
4. Open the Serial Monitor (baud rate 9600) and follow the prompts to assign IDs.  
5. Upload the access control sketch (FingerprintAccess.ino) for the security system.  
6. Observe the LCD for feedback during use.  

---

## Usage

### 1️⃣ Enrolling Fingerprints
1. Open Serial Monitor.  
2. Enter the ID number (1–127) for the fingerprint.  
3. Place the finger on the sensor when prompted.  
4. Remove and place the same finger again for verification.  
5. If successful, the fingerprint is stored.  

### 2️⃣ Access Control
1. Place an enrolled finger on the sensor.  
2. LCD shows *Access Granted* if matched, *Access Denied* if not.  
3. Buzzer gives short beep for granted, long beep for denied.  

---

## Notes
- Maximum of 127 fingerprint IDs due to sensor memory.  
- Ensure clean fingers and good sensor contact.  
- The system supports multiple users.
