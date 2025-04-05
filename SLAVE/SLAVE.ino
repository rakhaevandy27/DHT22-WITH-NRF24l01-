#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <DHT.h>

// NRF24L01 wiring:
// CE  -> GPIO 4
// CSN -> GPIO 5
// MOSI -> GPIO 23 (ESP32 default)
// MISO -> GPIO 19 (ESP32 default)
// SCK  -> GPIO 18 (ESP32 default)
// VCC -> 3.3V
// GND -> GND

// DHT22 wiring:
// DATA -> GPIO 27
// VCC  -> 3.3V or 5V
// GND  -> GND

#define CE_PIN 4
#define CSN_PIN 5
#define DHTPIN 27
#define DHTTYPE DHT22

RF24 radio(CE_PIN, CSN_PIN);
DHT dht(DHTPIN, DHTTYPE);

const byte address[6] = "00101";

struct SensorData {
  float temperature;
  float humidity;
};

void setup() {
  Serial.begin(115200);
  if (!radio.begin()) {
    Serial.println("NRF24 not connected!");
    while (1);
  }

  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_2MBPS);
  radio.stopListening();
  dht.begin();
}

void loop() {
  SensorData data = {
    dht.readTemperature(),
    dht.readHumidity()
  };

  if (isnan(data.temperature) || isnan(data.humidity)) return;

  Serial.printf("Sending Temp: %.1f °C, Humidity: %.1f %%\n", data.temperature, data.humidity);
  radio.write(&data, sizeof(data));
  delay(500); // Faster update
}
