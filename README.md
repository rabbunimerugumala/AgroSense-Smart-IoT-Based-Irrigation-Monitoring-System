# 🌾 AgroSense — Smart IoT-Based Irrigation & Monitoring System

**AgroSense** is a smart IoT-based automation system designed to modernize agriculture through real-time monitoring, intelligent irrigation control, and cloud-connected data visualization.  
Built using **Arduino Uno**, **NodeMCU (ESP8266)**, and the **Blynk IoT platform**, it helps farmers conserve water, reduce labor, and improve crop yield through automation and remote access.

---

## 📘 Project Overview

Traditional farming often suffers from water wastage, human error, and inefficient irrigation methods.  
**AgroSense** tackles these challenges by using environmental sensors to automatically monitor and control irrigation systems based on real-time soil and weather data.

This project demonstrates how **IoT, embedded systems, and automation** can work together to make farming more sustainable, efficient, and intelligent.

---

## 🧠 Key Features

- 🌦️ **Real-Time Monitoring** – Tracks soil moisture, temperature, humidity, light intensity, and rainfall conditions.
- 💧 **Automated Irrigation** – Activates the water pump only when the soil is dry and there is no rainfall.
- 📱 **IoT Integration (Blynk App)** – Enables remote control and live data visualization via smartphone.
- 🖥️ **Local LCD Display** – Displays live environmental parameters for offline access.
- ⚙️ **Dual Microcontroller Setup** – Arduino handles sensors and logic; NodeMCU handles IoT communication.
- 🔒 **Manual Override** – Farmers can manually start/stop irrigation through the Blynk app.
- 🌱 **Low-Cost and Scalable** – Built using affordable, easily available components.

---

## ⚙️ System Architecture

**Modules Used:**
- **Arduino Uno** – Sensor data collection and control logic.
- **NodeMCU ESP8266** – Wi-Fi connectivity and Blynk integration.
- **Sensors:**
  - Soil Moisture Sensor  
  - DHT11 (Temperature & Humidity)  
  - Rain Sensor  
  - IR Motion Sensor  
  - LDR (Light-Dependent Resistor)
- **Actuators:**
  - Relay module (Pump Control)
  - Buzzer for alerts
  - 16×2 I2C LCD Display

**Communication Flow:**
1. Arduino reads data from all sensors.
2. Processes and transmits data to NodeMCU via UART.
3. NodeMCU uploads data to Blynk Cloud.
4. Farmers monitor and control irrigation remotely.

---

## 💻 Technologies Used

| Component | Function |
|------------|-----------|
| **Arduino UNO** | Sensor data acquisition and pump logic |
| **NodeMCU ESP8266** | IoT communication with Blynk |
| **Blynk IoT App** | Remote monitoring and control |
| **DHT11 Sensor** | Temperature & humidity measurement |
| **Soil Moisture Sensor** | Soil dryness detection |
| **Rain Sensor** | Rainfall detection |
| **IR Sensor** | Human/animal motion detection |
| **LDR** | Ambient light detection |
| **LCD (I2C)** | Local real-time display |
| **Relay** | Pump actuation control |

---

## 🧩 Working Principle

1. **Sensors** continuously collect field data (moisture, temperature, humidity, etc.).  
2. **Arduino** processes this data and decides when to activate irrigation.  
3. **NodeMCU** uploads the processed data to the **Blynk Cloud** and handles manual override commands.  
4. **Pump** operates automatically when the soil is dry and no rainfall is detected.  
5. All data is displayed on both the **LCD** and **Blynk dashboard**.

---

## 📊 Results & Observations

- ✅ Stable data transmission between Arduino and NodeMCU (9600 bps UART).  
- 🌐 Real-time updates in Blynk App (V0–V7 virtual pins).  
- 💡 LCD rotates between data screens for easy on-field reading.  
- 💧 Reduced water wastage by automating irrigation.  
- ⚡ Responsive manual control through the mobile app.

---

## 🌍 Advantages

- Saves water through smart irrigation control  
- Reduces manual labor and human error  
- Provides real-time environmental data  
- Works even in semi-urban/rural areas  
- Easily expandable with additional sensors or AI-based features  

---

## ⚠️ Limitations

- Depends on stable internet connectivity  
- Sensor calibration required periodically  
- Limited long-term data logging  
- Basic weather prediction support  

---

## 🚀 Future Enhancements

- ☁️ Cloud-based data logging (Firebase / AWS / Azure)  
- 🤖 AI-driven irrigation scheduling using predictive analytics  
- ☀️ Solar power integration for off-grid deployment  
- 📊 Advanced mobile app with historical trend analysis  
- 🧪 Addition of pH, nutrient, and atmospheric sensors  

---

## 🧰 Hardware Connections (Quick Reference)

| **Arduino Pin** | **Connected Component / Function** |
|-----------------|------------------------------------|
| D3 | Relay (Pump Control) |
| D6 | Soil Moisture Sensor |
| D7 | Rain Sensor (FC-37) |
| D8 | IR Motion Sensor |
| D9 | DHT11 (Temperature & Humidity Sensor) |
| D10 | Buzzer |
| D11 | LDR (Light Sensor) |
| A4 (SDA) | I2C LCD Display |
| A5 (SCL) | I2C LCD Display |
| RX (Pin 0) | Connected to NodeMCU TX |
| TX (Pin 1) | Connected to NodeMCU RX |

---

## 📲 IoT Dashboard (Blynk Virtual Pins)

| Virtual Pin | Parameter |
|--------------|------------|
| V0 | Soil Status |
| V1 | Temperature |
| V2 | Humidity |
| V3 | Rain Detection |
| V4 | Motion Detection |
| V5 | Pump Status |
| V6 | LDR Value |
| V7 | Manual Pump Control |

---

## 👨‍🔧 Developed by  

**👨‍🔧 Merugumala Rabbuni**  
🎓 B.Tech in Electrical & Electronics Engineering (EEE)  
🔗 [GitHub](https://github.com/rabbunimerugumala)  
💼 [LinkedIn](https://www.linkedin.com/in/merugumala-rabbuni)


## 🪴 License

This project is released under the **MIT License** — free to use, modify, and build upon with proper attribution.

---

### ⭐ If you found this project helpful, consider giving it a star on GitHub!
