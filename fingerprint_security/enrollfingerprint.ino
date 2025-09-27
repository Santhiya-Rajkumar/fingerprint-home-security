#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

// change pins if needed
SoftwareSerial mySerial(2, 3); // RX, TX
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

uint8_t id;

void setup() {
  Serial.begin(9600);
  while (!Serial);  // wait for serial
  delay(100);
  finger.begin(57600);

  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }
}

void loop() {
  Serial.println("Ready to enroll a fingerprint!");
  Serial.println("Please type in the ID # (1-127) you want to save this finger as...");
  while (true) {
    while (!Serial.available());
    id = Serial.parseInt();
    if (id != 0) {
      Serial.print("Enrolling ID #");
      Serial.println(id);
      break;
    }
  }
  while (!getFingerprintEnroll());
}

uint8_t getFingerprintEnroll() {
  int p = -1;
  Serial.print("Waiting for valid finger to enroll as #"); Serial.println(id);
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
      case FINGERPRINT_OK:
        Serial.println("Image taken");
        break;
      case FINGERPRINT_NOFINGER:
        break;
      case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Communication error");
        break;
      case FINGERPRINT_IMAGEFAIL:
        Serial.println("Imaging error");
        break;
      default:
        Serial.println("Unknown error");
        break;
    }
  }

  // OK success!
  p = finger.image2Tz(1);
  if (p != FINGERPRINT_OK) {
    Serial.println("Image conversion failed");
    return p;
  }
  Serial.println("Remove finger");
  delay(2000);
  while (finger.getImage() != FINGERPRINT_NOFINGER);

  Serial.println("Place same finger again");
  p = -1;
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
  }
  p = finger.image2Tz(2);
  if (p != FINGERPRINT_OK) {
    Serial.println("Second image conversion failed");
    return p;
  }

  // Create model
  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println("Prints matched!");
  } else {
    Serial.println("Fingerprints did not match");
    return p;
  }

  // Store in memory
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    Serial.println("Stored!");
  } else {
    Serial.println("Error storing fingerprint");
    return p;
  }

  return true;
}