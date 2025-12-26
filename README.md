# 👶 Smart NeoCare: Automated Infant Incubator

![Platform](https://img.shields.io/badge/Platform-Arduino-blue)
![Sensors](https://img.shields.io/badge/Sensors-DHT11%20%7C%20MQ2%20%7C%20LDR-orange)
![Actuators](https://img.shields.io/badge/Actuators-Servo%20%7C%20Heater%20%7C%20Fan-red)
![Domain](https://img.shields.io/badge/Domain-Biomedical%20Engineering-purple)

## 📌 Project Overview
**Smart NeoCare** is an embedded control system for infant incubators designed to simulate the womb's environment for premature babies. Using **Arduino**, the system continuously monitors vital environmental parameters (Temperature, Humidity, Air Quality, Light) and automatically adjusts actuators to maintain stable conditions.

This project aims to reduce neonatal mortality by ensuring a safe, controlled, and responsive environment, minimizing the need for manual intervention by nursing staff.

## ⚙️ Key Features
* **Temperature Regulation:**
    * Reads internal temperature via **DHT11** and body temperature via **Thermistor**.
    * Automatically activates the **Heater** if temp < 35°C and the **Fan** if temp > 35°C to prevent hypothermia or overheating.
* **Air Quality Control:**
    * Monitors toxic gases using an **MQ-2 Sensor**.
    * If gas levels exceed the safety threshold (>300), a **Servo Motor** automatically opens the ventilation window, and a Red Alarm LED triggers.
* **Smart Lighting:**
    * Uses an **LDR (Light Dependent Resistor)** to detect ambient light.
    * Automatically turns on internal lighting (White LED) when the room gets dark (<100) to allow visibility.
* **Weight/Presence Monitoring:**
    * Utilizes an **FSR (Force Sensitive Resistor)** to monitor the infant's weight or presence on the mattress.
* **Phototherapy Integration:**
    * Controls Blue LEDs for jaundice treatment functionality.
* **User Interface:**
    * Displays real-time data (Temp, Humidity, Gas Level) on an **LCD 16x2** screen for staff monitoring.

## 🛠️ Hardware Stack
* **Controller:** Arduino Uno.
* **Sensors:** DHT11 (Temp/Hum), MQ-2 (Gas), LDR (Light), FSR (Force), NTC Thermistor (Body Temp).
* **Actuators:** Servo Motor (SG90), DC Fan, Heating Element (Simulated), LEDs.
* **Display:** LCD 16x2.

## 🚀 How to Run
1.  **Wiring:** Connect sensors and actuators according to the pin definitions in `src/incubator_control.ino`.
2.  **Libraries:** Install the `DHT` and `LiquidCrystal` libraries in Arduino IDE.
3.  **Upload:** Flash the code to the Arduino board.
4.  **Monitor:** Parameters will be displayed on the LCD.

## 📄 Documentation
For detailed system design, block diagrams, and circuit schematics, please refer to the [Project Report](docs/Project_Report.pdf).