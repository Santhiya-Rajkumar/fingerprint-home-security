#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ---------- Pin setup ----------
SoftwareSerial mySerial(2, 3);         // (RX, TX) for fingerprint sensor
Adafruit_Fingerprint finger(&mySerial);
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define BUZZER 6                       // Buzzer pin

// ---------- Setup ----------
void setup() {
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Home Security");
  lcd.setCursor(0,1);
  lcd.print("System Init...");

  Serial.begin(9600);

  // Try common baud rates
  if (!startSensor(57600) && !startSensor(9600)) {
    lcd.clear();
    lcd.print("Sensor Error!");
    Serial.println("Fingerprint sensor not found. Check wiring & power.");
    while (1); // stop here
  }

  delay(1500);
}

// ---------- Loop ----------
void loop() {

  // 1️⃣  Wait until a finger is detected
  if (!fingerPresent()) {
    // Show waiting message only when idle
    lcd.setCursor(0,0);
    lcd.print("Place Finger... ");
    delay(200);          // small delay to avoid flicker
    return;              // go back to start of loop
  }

  // 2️⃣  Finger detected: try to identify
  int id = identifyFingerprint();

  if (id >= 0) {  // Authorized
    Serial.print("Authorized ID: ");
    Serial.println(id);
    lcd.clear();
    lcd.print("Access Granted");
    tone(BUZZER, 1000, 200);   // short beep
    delay(2000);
  } 
  else {          // Finger present but not enrolled
    Serial.println("Unauthorized finger");
    lcd.clear();
    lcd.print("Access Denied");
    tone(BUZZER, 500, 600);    // long beep
    delay(2000);
  }

  // After result, give a moment before checking again
  delay(500);
}

// ---------- Helper Functions ----------

// Try a specific baud rate for the sensor
bool startSensor(uint32_t baud) {
  finger.begin(baud);
  Serial.print("Testing at "); Serial.print(baud); Serial.println(" baud...");
  if (finger.verifyPassword()) {
    Serial.print("Sensor ready at "); Serial.print(baud); Serial.println(" baud");
    lcd.clear();
    lcd.print("Sensor Ready");
    return true;
  }
  return false;
}

// Check if any finger is currently touching the sensor
bool fingerPresent() {
  int p = finger.getImage();
  return (p != FINGERPRINT_NOFINGER);
}

// Try to identify the fingerprint that is already known to be present
int identifyFingerprint() {
  if (finger.image2Tz() != FINGERPRINT_OK) return -1;
  if (finger.fingerSearch() != FINGERPRINT_OK) return -1;
  return finger.fingerID;  // matched ID
}