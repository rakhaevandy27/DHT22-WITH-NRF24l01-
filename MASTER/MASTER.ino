#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED wiring:
// SDA  -> GPIO 21
// SCL  -> GPIO 22
// VCC  -> 3.3V or 5V
// GND  -> GND

// NRF24L01 wiring:
// CE   -> GPIO 4
// CSN  -> GPIO 5
// MOSI -> GPIO 23
// MISO -> GPIO 19
// SCK  -> GPIO 18
// VCC  -> 3.3V
// GND  -> GND

#define SCREEN_I2C_ADDR 0x3C
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RST_PIN -1

#define CE_PIN 4
#define CSN_PIN 5

RF24 radio(CE_PIN, CSN_PIN);
const byte address[6] = "00101";

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST_PIN);

String rf_status = "OFF";

struct SensorData {
  float temperature;
  float humidity;
};

void updateDisplay(float temp, float hum);

void setup() {
  Serial.begin(115200);

  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_I2C_ADDR);
  display.clearDisplay();
  display.display();

  if (!radio.begin()) {
    Serial.println("NRF24 not connected!");
    while (1);
  }

  radio.openReadingPipe(1, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_2MBPS);
  radio.startListening();
}

void loop() {
  SensorData data;
  if (radio.available()) {
    radio.read(&data, sizeof(data));
    rf_status = "ON";

    Serial.printf("Temp: %.1f°C, Humidity: %.1f%%\n", data.temperature, data.humidity);
    updateDisplay(data.temperature, data.humidity);
  } else {
    rf_status = "OFF";
  }

  delay(100);  // Fast refresh
}

void updateDisplay(float temp, float hum) {
  display.clearDisplay();

  display.drawRect(0, 0, 128, 11, 1);
  display.drawLine(103, 0, 103, 10, 1);
  display.setCursor(3, 2);
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.print("ESP32 MONITORING");
  display.setCursor(109, 2);
  display.print(rf_status);

  display.setCursor(10, 20);
  display.setTextSize(2);
  display.print("T: ");
  display.print(temp, 1);
  display.print("C");

  display.setCursor(10, 40);
  display.print("H: ");
  display.print(hum, 1);
  display.print("%");

  display.display();
}
