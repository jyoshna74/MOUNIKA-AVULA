#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX for fingerprint sensor
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup() {
  Serial.begin(9600);  // Start serial communication for debugging
  mySerial.begin(9600);  // Start software serial for fingerprint sensor

  if (finger.begin()) {
    Serial.println("Fingerprint sensor initialized.");
  } else {
    Serial.println("Fingerprint sensor not detected.");
    while (1);
  }

  delay(1000);
  Serial.println("Place your finger on the sensor...");

  if (finger.getTemplateCount() == 0) {
    Serial.println("No fingerprints enrolled. Enroll a fingerprint.");
    enrollFinger();
  } else {
    Serial.println("Ready to recognize fingerprints.");
  }
}

void loop() {
  int fingerID = getFingerprintID();
  if (fingerID >= 0) {
    Serial.print("Fingerprint matched with ID: ");
    Serial.println(fingerID);
    logAttendance(fingerID);
  }
  delay(2000);  // Wait before checking for another fingerprint
}

void enrollFinger() {
  Serial.println("Please place your finger on the sensor for enrollment.");
  int fingerID = -1;
  while (fingerID == -1) {
    fingerID = getFingerprintID();
    delay(1000);
  }
  
  Serial.print("Enroll finger ID: ");
  Serial.println(fingerID);
  
  if (finger.storeModel(fingerID) == FINGERPRINT_OK) {
    Serial.println("Fingerprint enrolled successfully.");
  } else {
    Serial.println("Failed to enroll fingerprint.");
  }
}

int getFingerprintID() {
  uint8_t result;
  uint8_t fingerID = -1;
  
  result = finger.getImage();
  if (result != FINGERPRINT_OK) {
    Serial.println("No finger detected.");
    return -1;
  }

  result = finger.image2Tz();
  if (result != FINGERPRINT_OK) {
    Serial.println("Failed to convert image.");
    return -1;
  }

  result = finger.fingerSearch();
  if (result == FINGERPRINT_OK) {
    fingerID = finger.fingerID;
  } else {
    Serial.println("Fingerprint not recognized.");
    fingerID = -1;
  }

  return fingerID;
}

void logAttendance(int id) {
  Serial.print("Logging attendance for user ID: ");
  Serial.println(id);
}
