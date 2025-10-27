#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// LCD Setup
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin definitions
#define RELAY_PIN 3
#define SOIL_PIN 6
#define RAIN_PIN 7
#define IR_PIN 8
#define DHT_PIN 9
#define BUZZER_PIN 10
#define LDR_PIN 11  

#define DHTTYPE DHT11
DHT dht(DHT_PIN, DHTTYPE);

// Variables
unsigned long lastSwitch = 0;
int screen = 0;
const unsigned long switchInterval = 3000;

bool manualPumpControl = false;
String incomingData = "";

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.init();
  lcd.backlight();

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(SOIL_PIN, INPUT);
  pinMode(RAIN_PIN, INPUT);
  pinMode(IR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LDR_PIN, INPUT);

  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  lcd.setCursor(0, 0);
  lcd.print("Smart Irrigation");
  lcd.setCursor(0, 1);
  lcd.print("System Starting");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Read serial command from NodeMCU
  while (Serial.available()) {
    char c = Serial.read();
    incomingData += c;
    if (c == '\n') {
      if (incomingData.startsWith("PUMP_CTRL:")) {
        manualPumpControl = incomingData.endsWith("1\n");
      }
      incomingData = "";
    }
  }

  // Sensor Readings
  bool soilDry = digitalRead(SOIL_PIN);             
  bool rainDetected = digitalRead(RAIN_PIN) == LOW;
  bool motionDetected = digitalRead(IR_PIN) == LOW;
  float temp = dht.readTemperature();
  float humi = dht.readHumidity();
  bool isDark = digitalRead(LDR_PIN) == LOW;  // Assuming LOW = dark
  int ldrValue = isDark ? 0 : 1023;           // Simulate analog scale for display/logging


  // Pump Logic
  if (manualPumpControl) {
    digitalWrite(RELAY_PIN, HIGH);
  } else {
    if (soilDry && !rainDetected) {
      digitalWrite(RELAY_PIN, HIGH);
    } else {
      digitalWrite(RELAY_PIN, LOW);
    }
  }

  // Determine pump status string
  String pumpStatus = digitalRead(RELAY_PIN) ? "ON" : "OFF";

  // Send data to NodeMCU
  Serial.print(soilDry ? "Dry" : "Wet"); Serial.print(",");
  Serial.print(temp); Serial.print(",");
  Serial.print(humi); Serial.print(",");
  Serial.print(rainDetected ? "Yes" : "No"); Serial.print(",");
  Serial.print(motionDetected ? "Yes" : "No"); Serial.print(",");
  Serial.print(pumpStatus); Serial.print(",");
  Serial.println(ldrValue);

  // LCD display switch
  if (millis() - lastSwitch > switchInterval) {
    screen = (screen + 1) % 3;
    lcd.clear();
    lastSwitch = millis();
  }

  switch (screen) {
    case 0:
      lcd.setCursor(0, 0); lcd.print("Temp: ");
      lcd.print(temp); lcd.print("C");
      lcd.setCursor(0, 1); lcd.print("Humi: ");
      lcd.print(humi); lcd.print("%");
      break;
    case 1:
      lcd.setCursor(0, 0); lcd.print("Soil: ");
      lcd.print(soilDry ? "Dry" : "Wet");
      lcd.setCursor(0, 1); lcd.print("Pump: ");
      lcd.print(pumpStatus);
      break;
    case 2:
      lcd.setCursor(0, 0); lcd.print("Rain: ");
      lcd.print(rainDetected ? "Yes" : "No ");
      lcd.setCursor(0, 1); lcd.print("Motion: ");
      lcd.print(motionDetected ? "Yes" : "No ");
      break;
  }

  // Motion alert at night
  if (motionDetected && isDark) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(200);
    digitalWrite(BUZZER_PIN, LOW);
  }

  delay(2000);
}
