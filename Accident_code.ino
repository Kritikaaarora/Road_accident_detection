#define BLYNK_TEMPLATE_ID "TMPL3IBFN03rS"
#define BLYNK_TEMPLATE_NAME "Notification"
#define BLYNK_AUTH_TOKEN "GIdsOfGX7aOTNjFT1wIiBe1paNz1vF0p"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <MPU6050.h>
#include <LiquidCrystal_I2C.h>

MPU6050 mpu;
LiquidCrystal_I2C lcd(0x27, 16, 2);

// WiFi
char ssid[] = "Kunal's Galaxy F23 5G";
char pass[] = "@3456789";

// Pins
const int LED_PIN = 4;      // Motor LED
const int BUZZER  = 25;     // Active Buzzer
const int BUTTON  = 26;     // Button (GND trigger)

// MPU values
int16_t ax, ay, az;
int16_t lastAY = 0, lastAZ = 0;

// Accident logic
bool accidentDetected = false;
unsigned long accidentStartTime = 0;
unsigned long buzzerTimer = 0;
bool buzzerState = false;

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);   // Motor ON normally

  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);

  pinMode(BUTTON, INPUT_PULLUP);  // Button to GND

  // LCD Setup
  Wire.begin(21, 22);
  lcd.init();
  lcd.backlight();
  lcd.print("System Loading...");
  delay(1000);
  lcd.clear();

  // WiFi
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(200);
  }
  Serial.println("\nWiFi OK");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // MPU
  mpu.initialize();
  lcd.setCursor(0, 0);
  lcd.print(mpu.testConnection() ? "MPU OK" : "MPU FAIL");
  delay(1000);
  lcd.clear();

  // Store initial stable readings to avoid false accidents
  mpu.getAcceleration(&ax, &ay, &az);
  lastAY = ay;
  lastAZ = az;
  delay(500);
}

void loop() {
  Blynk.run();

  // Read MPU
  mpu.getAcceleration(&ax, &ay, &az);

  float ay_g = ay / 16384.0;
  float az_g = az / 16384.0;
  float dAY = abs(ay_g - (lastAY / 16384.0));
  float dAZ = abs(az_g - (lastAZ / 16384.0));

  lcd.setCursor(0, 0);
  lcd.print("AY:");
  lcd.print(ay_g, 2);
  lcd.print(" AZ:");
  lcd.print(az_g, 2);

  // ACCIDENT DETECTION (fixed threshold)
  if (!accidentDetected && (dAY > 0.50 || dAZ > 0.50)) {  
    accidentDetected = true;
    accidentStartTime = millis();

    digitalWrite(LED_PIN, LOW);  // Motor OFF
    lcd.setCursor(0, 1);
    lcd.print("Accident!PressBtn");

    Serial.println("ACCIDENT DETECTED!");
  }

  // ACCIDENT HANDLING
  if (accidentDetected) {

    // Buzzer toggling (non-blocking)
    if (millis() - buzzerTimer > 250) {
      buzzerTimer = millis();
      buzzerState = !buzzerState;
      digitalWrite(BUZZER, buzzerState);
    }

    // BUTTON PRESS cancels alert
    if (digitalRead(BUTTON) == LOW) {
      accidentDetected = false;

      digitalWrite(BUZZER, LOW);
      digitalWrite(LED_PIN, HIGH);

      lcd.clear();
      lcd.print("Alert Cancelled");
      delay(1500);
      lcd.clear();
    }

    // AUTO SEND AFTER 10s
    if (millis() - accidentStartTime >= 10000) {

      Blynk.logEvent("notification", "Accident! No response.");

      digitalWrite(BUZZER, LOW);

      lcd.clear();
      lcd.print("Alert Sent!");

      // Motor stays OFF after accident
      digitalWrite(LED_PIN, LOW);

      delay(1500);
      lcd.clear();

      accidentDetected = false;
    }
  }
  lastAY = ay;
  lastAZ = az;
}
