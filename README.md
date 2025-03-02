# **DualAccess_Lock using Wifi and Offline keypad access modes: ESP32 & Arduino-Based Door Security System**

## **Overview**
Wi-Key Secure is a smart door security system that allows access control via **Wi-Fi-based webpage input** and **offline keypad control**. It utilizes an ESP32 for web-based authentication and an Arduino for offline keypad-based access.

---

## **Project Features**
- 📡 **Wi-Fi-based key entry via ESP32 webpage**
- ⌨️ **Offline keypad access via Arduino**
- 🔄 **ESP32 to Arduino communication via Serial**
- 🔒 **Security verification with predefined passcodes**
- 📜 **Serial Monitor debugging for keypress events**

---

## **Hardware Requirements**
1. **ESP32**
2. **Arduino Uno/Nano**
3. **4x4 or 4x3 Keypad Module**
4. **Servo Motor (for door lock mechanism) or use a LED for testing**
5. **Connecting Jumper Wires**
6. **Common Power Supply (5V)**
7. **LCD Display (optional for status updates)**

---

## **Circuit Connections**

| Arduino Pin | Connected To  |
|-------------|---------------|
| Pin (RX 0)  | ESP32 TX (17) |
| Pin (TX 1)  | ESP32 RX (16) |

| Keypad Rows & Columns | Digital Pins |
| Servo Motor | PWM Pin |

---

## **Software Setup**
### **1️⃣ ESP32 Setup (Wi-Fi & Web Server)**
1. Install **Arduino IDE** & add **ESP32 Board Support**.
2. Install necessary libraries:
   - `WiFi.h`
   - `WebServer.h`
3. Upload the **ESP32 Code** to start the web server.
4. Open the **Serial Monitor** (115200 baud) and note the IP address.
5. Access the ESP32 webpage via your browser and enter the key.

### **2️⃣ Arduino Setup (Offline Keypad Control & Serial Communication)**
1. Install **Arduino IDE**.
2. Install necessary libraries:
   - `Keypad.h`
   - `Servo.h` (optional: else use an LED for testing)
   - `SoftwareSerial.h` (optional: for Serial communication with ESP32)
   - `LiquidCrystal_I2C.h`
   - `Wire.h`
3. Upload the **Arduino Code** to handle keypad input and door locking.
4. Open the **Serial Monitor** (115200 baud) to check received key data.

---

## **Working Steps**
### **🔹 Web-Based Authentication (ESP32)**
1. Connect ESP32 to Wi-Fi.
2. Open the webpage hosted by ESP32.
3. Enter the passcode on the webpage.
4. If correct, ESP32 sends the key to Arduino for door control or use an LED for testing.
5. If incorrect, access is denied, and the LCD (if used) displays an error and the buzzer gets triggered.

### **🔹 Offline Keypad Authentication (Arduino)**
1. User enters a passcode using the 4x4 or 4x3 keypad.
2. If correct, the Arduino triggers the servo motor to unlock the door or use an LED for testing.
3. If incorrect, access is denied, and the LCD (if used) displays an error and the buzzer gets triggered.

---

## **Future Enhancements**
✅ Add an **RFID Module** for an extra authentication method.
✅ Use **MQTT** for remote access control.
✅ Implement **Blynk/App Integration** for mobile-based control.
✅ Integrate **Cloud Logging** for security access history.

---

## **License**
This project is open-source project anyone can provide their contributions for any better changes in the project.

contact: rameshkumarana@gmail.com
