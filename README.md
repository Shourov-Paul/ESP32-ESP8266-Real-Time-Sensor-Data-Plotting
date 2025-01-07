**ESP32-ESP8266-Real-Time-Sensor-Data-Plotting**

---

### **Repository Description**:  
A project that builds an asynchronous web server using ESP32 or ESP8266 to display real-time sensor data (temperature, humidity, pressure) on interactive charts. The web interface uses the Highcharts library to graph data collected from a BME280 sensor, with easy modification for other sensors.

---

### **Table of Contents**:  
1. [Introduction](#introduction)  
2. [Prerequisites](#prerequisites)  
3. [Parts Required](#parts-required)  
4. [Wiring Diagram](#wiring-diagram)  
5. [File Organization](#file-organization)  
6. [Uploading Code and Files](#uploading-code-and-files)  
7. [Project Structure](#project-structure)  
8. [How to Use](#how-to-use)  
9. [License](#license)

---

### **Introduction**:  
In this project, we will build an asynchronous web server using the ESPAsyncWebServer library, which will serve HTML pages stored in the ESP32 or ESP8266 filesystem (LittleFS). The project reads sensor data from a BME280 sensor and displays it on a web interface, updating in real-time with interactive charts.

You can modify this project to use any other sensor readings, such as a temperature sensor, humidity sensor, etc.

---

### **Prerequisites**:  
Before you start, make sure to have the following setup:

1. **Install ESP Board in Arduino IDE**:  
   - Install the ESP32 or ESP8266 add-on for Arduino IDE.  
   - Follow these tutorials for installation:  
     - [Installing ESP32 Board in Arduino IDE](https://github.com/espressif/arduino-esp32)  
     - [Installing ESP8266 Board in Arduino IDE](https://github.com/esp8266/Arduino)

2. **Filesystem Uploader Plugin**:  
   To upload the HTML file to the ESP32 or ESP8266 flash memory, install the Filesystem Uploader plugin:  
   - [ESP8266 NodeMCU LittleFS Uploader](https://github.com/esp8266/arduino-esp8266fs-plugin)  
   - [ESP32 LittleFS Uploader](https://github.com/me-no-dev/arduino-esp32fs-plugin)

3. **Libraries Required**:
   - **ESP32**: Install `ESPAsyncWebServer` and `AsyncTCP` libraries.  
   - **ESP8266**: Install `ESPAsyncWebServer` and `ESPAsyncTCP` libraries.  
   - **BME280 Sensor**: Install `Adafruit BME280` and `Adafruit Unified Sensor` libraries.

---

### **Parts Required**:  
1. ESP32 or ESP8266  
2. BME280 sensor  
3. Breadboard  
4. Jumper wires

---

### **Wiring Diagram**:  
The BME280 sensor uses I2C communication, and the wiring for the ESP8266 is as follows:

| **BME280**  | **ESP8266** |
|-------------|-------------|
| SCK (SCL)   | GPIO 5      |
| SDI (SDA)   | GPIO 4      |

Make sure to connect the sensor to the correct I2C pins based on your specific board.

---

### **File Organization**:  
To structure your project, the Arduino sketch and HTML file must be organized as follows:
1. **ESP_Chart_Web_Server.ino** (Arduino sketch)
2. **data** (folder containing the HTML file)

---

### **Uploading Code and Files**:  
Follow these steps to upload your project to the ESP32 or ESP8266:

1. Save your Arduino sketch as `ESP_Chart_Web_Server.ino` or download all project files.
2. Create a folder called `data` in the sketch folder and place your HTML file inside.
3. To upload the HTML file to the ESP filesystem:
   - Open Arduino IDE and press [Ctrl] + [Shift] + [P] (Windows) or [⌘] + [Shift] + [P] (MacOS).
   - Search for the **Upload LittleFS to ESP32/ESP8266** command and execute it.
   - Ensure the Serial Monitor is closed during the upload process.
4. Upload the Arduino code to your ESP board.
5. Insert your network credentials (Wi-Fi SSID and password) in the code.
6. Once uploaded, open the Serial Monitor at 115200 baud rate. Press the “EN/RST” button on the board to print the IP address.

---

### **Project Structure**:  
```
ESP32-ESP8266-Real-Time-Sensor-Data-Plotting/
│
├── ESP32-ESP8266-Real-Time-Sensor-Data-Plotting.ino    # Arduino Sketch
└── data/                                               # Folder containing HTML file
    └── index.html                                      # HTML file for the web interface
```

---

### **How to Use**:  
1. Open the **ESP_Chart_Web_Server.ino** in Arduino IDE.
2. Install the required libraries and plugins.
3. Configure your Wi-Fi credentials in the code.
4. Upload the HTML file using the Filesystem Uploader plugin.
5. Upload the Arduino sketch to your ESP32 or ESP8266 board.
6. Open the Serial Monitor to get the IP address and navigate to it in your browser to view the real-time sensor data.

---

### **License**:  
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---
