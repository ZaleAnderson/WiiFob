#include "ESP32Wiimote.h"


ESP32Wiimote wiimote;
int LED_BUILTIN = 2;


unsigned long previousMillis = 0;
const long interval = 600000;  

void setup()
{
    Serial.begin(115200);
    wiimote.init();
    pinMode (LED_BUILTIN, OUTPUT);
    pinMode(13, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(14, OUTPUT);
    pinMode(27, OUTPUT);
    Serial.println("Ready...");
}

void loop()
{
  wiimote.task();
  unsigned long currentMillis = millis();
  
  if (wiimote.available() > 0) {
      digitalWrite(LED_BUILTIN, HIGH);
      uint16_t button = wiimote.getButtonState();
      Serial.printf("%04x\n", button);
      if (button == ESP32Wiimote::BUTTON_A) { // UNLOCK
        digitalWrite(13, LOW);
        Serial.println("A button");
        delay(100);
        digitalWrite(13, HIGH);
      }
      if (button == ESP32Wiimote::BUTTON_B) { // LOCK
        digitalWrite(12, LOW);
        Serial.println("B button");
        delay(100);
        digitalWrite(12, HIGH);
      }
      if (button == ESP32Wiimote::BUTTON_RIGHT) { //TRUNK
        digitalWrite(14, LOW);
        Serial.println("Down button");
        delay(100);
        digitalWrite(14, HIGH);
      }
      if (button == ESP32Wiimote::BUTTON_ONE) { //   5
        digitalWrite(27,LOW);
        Serial.println("One button");
        delay(100);
        digitalWrite(27, HIGH);
      }
      if (button == ESP32Wiimote::BUTTON_HOME) { //   Restart
        digitalWrite(32, LOW);
        Serial.println("Home button");
        delay(100);
        digitalWrite(32, HIGH);
        digitalWrite(LED_BUILTIN, LOW);
        ESP.restart();
      }
  }
  if (currentMillis - previousMillis >= interval) {
      // save the last time you blinked the LED
      previousMillis = currentMillis;
        digitalWrite(LED_BUILTIN, LOW);
        Serial.println("Resetting...");
        ESP.restart();
    }
  }
