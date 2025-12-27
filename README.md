# IoT-Based Health Monitoring System 🩺🌐

## 📌 Abstract
Healthcare is one of the most vital sectors where technology can make a transformative impact. With the rise of the Internet of Things (IoT), it has become possible to continuously monitor patient health parameters remotely and provide timely interventions.  

This project demonstrates a **low-cost, scalable, and reliable IoT-based health monitoring system** using the **ESP32 microcontroller**, **MAX30100 pulse oximeter sensor**, **DHT11 temperature & humidity sensor**, **DS18B20 body temperature sensor**, and the **Blynk cloud platform**.  

The system measures **heart rate, SpO₂, body temperature, and environmental conditions**, transmitting them to a mobile dashboard for remote monitoring. It highlights how IoT can improve healthcare accessibility, especially in rural and underserved areas.

---

## 🎯 Objectives
- Design and implement a real-time IoT-based health monitoring system.
- Measure and transmit heart rate, SpO₂, body temperature, and room conditions to a cloud dashboard.
- Provide remote access to patient data via mobile/web interface.
- Ensure scalability and reliability for future enhancements.
- Demonstrate how IoT can reduce healthcare costs and improve patient outcomes.

---

## 🛠️ Technology Overview
- **ESP32 Microcontroller**: Dual-core, Wi-Fi + Bluetooth, low power consumption.
- **Blynk Cloud Platform**: Real-time visualization, data logging, remote control.
- **Sensors**:
  - MAX30100 → Heart rate & SpO₂
  - DHT11 → Ambient temperature & humidity
  - DS18B20 → Body temperature (OneWire protocol)
- **Communication Protocols**:
  - I²C → ESP32 ↔ MAX30100
  - OneWire → DS18B20
  - Digital Pin → DHT11

---

## 🔩 Hardware Components
- ESP32 Development Board  
- MAX30100 Pulse Oximeter Sensor  
- DHT11 Temperature & Humidity Sensor  
- DS18B20 Waterproof Temperature Sensor  
- 4.7kΩ Resistor  
- 5V Power Supply Adapter  
- Zero PCB (Prototyping Board)  

---

## ⚡ Circuit Diagram
*(Add your circuit diagram image here, e.g. `/images/circuit.png`)*

---

## 📱 Screenshots
*(Add screenshots of your Blynk dashboard here)*

---

## ✅ Results
- Heart rate & SpO₂ readings stable with proper finger placement.
- Room temperature & humidity matched ambient conditions.
- DS18B20 body temperature readings accurate compared to digital thermometer.
- System operated continuously with reliable Wi-Fi connectivity.

---

## 📌 Conclusion
The IoT-based Health Monitoring System provides a reliable and scalable solution for real-time patient monitoring. By leveraging ESP32 and Blynk cloud, it ensures continuous tracking of vital signs and environmental conditions.  

While not a substitute for clinical-grade equipment, it offers significant potential for **home healthcare, elderly monitoring, and remote diagnostics**. Future enhancements may include:
- Alert notifications
- AI-based anomaly detection
- Integration with additional medical sensors

---

## 🚀 How to Run
1. Clone this repository:
   ```bash
   git clone https://github.com/<your-username>/<repo-name>.git
