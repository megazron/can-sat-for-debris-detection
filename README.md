# 🛰️ Space Debris Detection using LiDAR

This project implements a **LiDAR-based system for detecting space debris** in Low Earth Orbit (LEO).  
It uses **Arduino firmware, LiDAR sensors, and Python applications** to simulate debris detection and tracking.  

The project is part of a research initiative on solving the increasing problem of space debris, which poses a serious threat to satellites, rockets, and future space missions.

---

## 📌 Problem Statement
There are millions of untracked debris particles orbiting Earth, some moving at speeds up to **30,000 km/h**.  
Even pea-sized fragments can destroy satellites, creating chain reactions that could make Earth’s orbit unusable in the future.  

This project proposes a **LiDAR-based pico-satellite system** designed to detect and track debris that traditional satellites cannot.

---

## 📂 Repository Contents
| File | Description |
|------|-------------|
| **VL53L0X_lidar.ino** | Arduino program for LiDAR sensor (distance measurements). |
| **debris.ino** | Arduino firmware for debris detection and data handling. |
| **app.py** | Python application to process and visualize LiDAR data. |

---

## ⚙️ Methodology
1. **LiDAR Technology**  
   - Uses a VL53L0X LiDAR sensor to measure distances.  
   - Backscattered light from debris is used to calculate position and speed.  

2. **Data Processing**  
   - Arduino handles sensor interfacing (`VL53L0X_lidar.ino`, `debris.ino`).  
   - Python app (`app.py`) processes raw LiDAR data and plots debris trajectories.  

3. **Applications**  
   - Tracking of small, fast-moving debris.  
   - Potential integration with pico-satellites for real-time debris detection.  

---

## 🚀 Setup & Installation
### Hardware Requirements
- Arduino (UNO/Mega/Nano).  
- VL53L0X LiDAR sensor.  
- Communication interface (UART/I2C).  

### Software Requirements
- **Arduino IDE** (for `.ino` files).  
- **Python 3.x** with dependencies:  
  ```bash
  pip install numpy matplotlib
  ```

### Running
1. Upload `VL53L0X_lidar.ino` or `debris.ino` to your Arduino board.  
2. Connect LiDAR sensor (I2C).  
3. Run the Python app:  
   ```bash
   python app.py
   ```

---

## 📊 Results
- Successful **LiDAR-based detection of simulated debris**.  
- Real-time distance measurements.  
- Python visualizations for debris movement and trajectory.  

---

## 🌍 Social & Scientific Impact
- Helps prevent future **collisions in space**.  
- Supports safe satellite launches and sustainability of space missions.  
- Contributes to **space situational awareness (SSA)** research.  

---

## 👨‍💻 Authors
Developed by **Team MegaZroN**  
Students of MGM’s Jawaharlal Nehru Engineering College.  

Portfolio: [https://megazron.com](https://megazron.com)  

---

## 📜 License
This project is licensed under the terms of the [LICENSE](LICENSE) file.
