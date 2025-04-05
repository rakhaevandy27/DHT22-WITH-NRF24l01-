# 📡 ESP32 DHT22 NRF24L01 Wireless Sensor System with OLED Display

This project demonstrates a simple wireless temperature and humidity monitoring system using ESP32 microcontrollers, DHT22 sensors, NRF24L01 transceivers, and an SSD1306 OLED display.

## 🌟 Features

- 📈 Real-time temperature and humidity data
- 📶 Wireless communication with NRF24L01
- 🌡️ Accurate readings using DHT22
- 🖥️ Live display on OLED (SSD1306)
- 🔁 Transmitter and receiver architecture

---

## 🧠 System Overview

- **Transmitter Node (ESP32)**
  - Reads temperature and humidity from DHT22
  - Sends data via NRF24L01

- **Receiver Node (ESP32)**
  - Receives data from transmitter
  - Displays data on SSD1306 OLED

---

## 🔧 Hardware Required

| Component           | Quantity |
|---------------------|----------|
| ESP32 Dev Board     | 2        |
| DHT22 Sensor        | 1        |
| NRF24L01 Module     | 2        |
| SSD1306 OLED Display| 1        |
| Breadboard & Wires  | As needed |
| Capacitor (10uF–100uF) | 2 (recommended for NRF24L01 stability) |

---

## 🔌 Wiring Diagram

### Transmitter (ESP32)

| DHT22 Pin | ESP32 Pin |
|-----------|-----------|
| VCC       | 3.3V      |
| GND       | GND       |
| DATA      | GPIO 27    |

| NRF24L01 Pin | ESP32 Pin |
|--------------|-----------|
| VCC          | 3.3V      |
| GND          | GND       |
| CE           | GPIO 5    |
| CSN          | GPIO 17   |
| SCK          | GPIO 18   |
| MOSI         | GPIO 23   |
| MISO         | GPIO 19   |

---

### Receiver (ESP32)

| NRF24L01 Pin | ESP32 Pin |
|--------------|-----------|
| VCC          | 3.3V      |
| GND          | GND       |
| CE           | GPIO 5    |
| CSN          | GPIO 17   |
| SCK          | GPIO 18   |
| MOSI         | GPIO 23   |
| MISO         | GPIO 19   |

| OLED Pin | ESP32 Pin |
|----------|-----------|
| VCC      | 3.3V      |
| GND      | GND       |
| SDA      | GPIO 21   |
| SCL      | GPIO 22   |

> ⚠️ Don't forget to use a 10uF–100uF capacitor across NRF24L01’s VCC-GND.

---

## 💻 Libraries Used

Install these libraries in the Arduino IDE:

- `DHT sensor library` by Adafruit  
- `Adafruit Unified Sensor`  
- `RF24` by TMRh20  
- `Adafruit SSD1306`  
- `Adafruit GFX`  

---

## 📥 Installation

1. Clone this repository:
   ```bash
   git clone https://github.com/yourusername/esp32-dht22-nrf24l01-oled.git
