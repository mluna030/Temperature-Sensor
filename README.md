# **Real-Time Temperature Sensing System**

![image](https://user-images.githubusercontent.com/24575745/167693636-ff0cada1-fb44-4bf3-9150-637eb35ac700.png)
## **Overview**  
This project is a **temperature monitoring and fan control system** implemented on a **PIC18F4620 microcontroller**. The system reads temperature data from a **DS1621 sensor** via **I2C** and dynamically controls a cooling fan using **PWM**. The temperature readings are displayed on an **ST7735 TFT screen** over an **SPI** interface.  

## **Features**  
✅ **Real-time temperature monitoring** using a DS1621 sensor  
✅ **Dynamic fan speed control** based on temperature thresholds  
✅ **TFT display for live temperature readings** (ST7735, SPI interface)  
✅ **UART-based debugging** for real-time diagnostics  
✅ **Optimized I2C routines** to improve bus reliability  

## **Technologies & Components**  
- **Microcontroller:** PIC18F4620  
- **Sensors:** DS1621 (I2C Temperature Sensor)  
- **Display:** ST7735 TFT (SPI Interface)  
- **Communication Protocols:** I2C, SPI, UART  
- **Software Development:** Embedded C (XC8 Compiler)  

## **Installation & Setup**  
1. **Clone the repository:**  
   ```sh
   git clone https://github.com/mluna030/ECE3301LabFinal.git
   cd ECE3301LabFinal
2.  Build & Flash the Firmware

    Open the Final_lab.X project in MPLAB X.
    Compile the project using the XC8 compiler.
    Use a PIC programmer (e.g., PICKIT 3) to flash the generated HEX file to the PIC18F4620.

## Usage Instructions
1. Power up the circuit (5V supply).
2. The TFT display will show real-time temperature readings.
3. The fan will adjust speed dynamically based on temperature.
4. Use UART logging to debug and monitor system behavior.

## **Demo Video**  

[🎥 Watch the project in action](https://youtube.com/shorts/FqeJr8V_ytQ?feature=share)


