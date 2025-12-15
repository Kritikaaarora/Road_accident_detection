# 🚗 Accident Detection & Alert System (IoT-Based)

An **IoT-enabled Accident Detection and Alert System** built using **ESP32** and **MPU6050** that detects real-time vehicle crashes using sensor fusion and automatically sends emergency alerts with location details. This project focuses strongly on **accurate accident detection**, **false-trigger reduction**, and **fast emergency response**.

---

## 🔥 Key Highlight – Accident Detection (Core Focus)

The **Accident Detection Module** is the heart of this project. It continuously monitors vehicle motion using a **3-axis accelerometer and gyroscope (MPU6050)** and intelligently determines whether a crash has occurred.

### 🧠 How Accident Detection Works

The system uses **sensor fusion + threshold-based logic** to differentiate between:

* Normal driving vibrations
* Sudden braking
* Potholes / speed breakers
* **Actual accidents (collision, rollover, fall)**

### 📊 Sensors Used

* **MPU6050 Accelerometer** → detects sudden force, impact, free-fall
* **MPU6050 Gyroscope** → detects abnormal tilt, roll, or rotation

Both sensors work together to reduce false positives.

---

## ⚙️ Accident Detection Algorithm (Simplified)

1. ESP32 continuously reads acceleration (Ax, Ay, Az) and rotation values
2. Noise filtering is applied to ignore minor vibrations
3. Sudden change (Δ) in acceleration or tilt is calculated
4. If threshold exceeds safe limit → **Possible Accident Detected**
5. System enters **Warning Mode**
6. Driver gets **10 seconds** to cancel false alert using push button
7. If no response → **Accident Confirmed**
8. Emergency alert is triggered automatically

```text
If (ΔAcceleration > Threshold OR ΔTilt > Threshold)
    → Warning Mode
    → Buzzer ON
    → Wait for Driver Response
If (No Response within Time Limit)
    → Accident Confirmed
    → Send Emergency Alert
```

---

## 🚨 False Trigger Prevention Logic

To avoid false alerts caused by:

* Speed breakers
* Rough roads
* Sudden turns

The system includes:

* Time-based confirmation window
* Driver safety confirmation button
* Combined accelerometer + gyroscope validation

✅ Result: **High accuracy accident detection with minimal false alarms**

---

## 📍 What Happens After Accident Detection

Once an accident is confirmed:

* 🔊 **Buzzer** activates for local emergency alert
* 🔴 **LED** turns OFF (simulated engine failure)
* 📟 **LCD** displays "Accident Detected"
* 📡 **ESP32 sends alert via Wi-Fi / Blynk / API**
* 📍 **Live GPS location** is attached
* 📲 Emergency contact receives notification

All actions happen **automatically without human intervention**.

---

## 🛠 Hardware Used

* ESP32 (Wi-Fi enabled microcontroller)
* MPU6050 (Accelerometer + Gyroscope)
* GPS Module
* Buzzer (Emergency alert)
* LED (Status indicator)
* Push Button (Driver safety confirmation)
* 16×2 LCD Display

---

## 🧪 Tested Accident Scenarios

The detection logic was validated for:

* Sudden collision
* Vehicle fall / rollover
* High-impact tilt
* Normal driving (no false trigger)
* False alert cancellation by driver

✔ Successfully tested in **Wokwi simulation** and **real hardware setup**

---

## 🚀 Features Summary

* Real-time accident detection
* Sensor fusion for high accuracy
* Driver confirmation to avoid false alerts
* Automatic emergency notification
* GPS-based location sharing
* Low-cost & scalable design

---

## 🔮 Future Improvements

* AI/ML-based accident severity prediction
* Cloud accident data logging (Black Box)
* Drowsiness detection using camera
* GSM fallback for no-WiFi zones

---

## 📌 Project Use Cases

* Personal vehicles (bikes, cars)
* Public transport
* Fleet management
* Smart city safety systems

---

## 👨‍💻 Authors

* **Kritika Arora**
* **Kunal Chaudhary**

Jaypee Institute of Information Technology, Noida

##
