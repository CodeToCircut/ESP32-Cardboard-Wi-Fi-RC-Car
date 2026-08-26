# ESP32 Cardboard Wi-Fi RC Car 🚗⚡

A lightweight, low-cost Wi-Fi controlled RC car built using an ESP32 microcontroller, a dual-motor driver, and a cardboard chassis. This project hosts an interactive web dashboard directly on the ESP32, allowing you to drive the car wirelessly from any smartphone or computer connected to the same network.

## 🛠️ Components & Hardware
* **Microcontroller:** ESP32 Development Board (DOIT DevKit v1 or equivalent)
* **Motor Driver:** L298N or DRV8833 Motor Driver Module
* **Actuators:** Dual TT Gear Motors (3V–6V) + Wheels
* **Chassis:** Cardboard cut to custom dimensions
* **Power Source:** 3.7V Li-ion battery pack or portable power bank

---

## 📌 Wiring Pinout
| ESP32 Pin | Connected To | Description |
| :--- | :--- | :--- |
| **GPIO 25** | IN1 (Motor Driver) | Left Motor Forward |
| **GPIO 26** | IN2 (Motor Driver) | Left Motor Reverse |
| **GPIO 27** | IN3 (Motor Driver) | Right Motor Forward |
| **GPIO 14** | IN4 (Motor Driver) | Right Motor Reverse |
| **GND** | GND & Battery Common | Common Ground |
| **VIN / 5V** | Motor Driver VCC | Power Supply |

---

## 🚀 Getting Started

### 1. Prerequisites
Open the **Arduino IDE** and make sure you have the **ESP32 Board Package** installed. No external libraries are required as this project relies entirely on the built-in `WiFi.h` library.

### 2. Configuration
Update the Wi-Fi credentials in the code below to match your local network:
```cpp
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";
