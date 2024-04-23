# acc_combo_trigger
Arduino code that triggers a keyboard and mouse combo when it is moved on the Z axis at a certain speed

# Components
- [Adafruit QT Py ESP32 Pico - WiFi Dev Board with STEMMA QT - 8MB Flash 2MB PSRAM](https://www.adafruit.com/product/5395)
    - [Overview | Adafruit QT Py ESP32 Pico](https://learn.adafruit.com/adafruit-qt-py-esp32-pico)
- [ADXL343 - Triple-Axis Accelerometer (+-2g/4g/8g/16g) w/ I2C/SPI - STEMMA QT / Qwiic](https://www.adafruit.com/product/4097)
    - [Overview | Analog Devices ADXL343 Breakout Learning Guide ](https://learn.adafruit.com/adxl343-breakout-learning-guide)
    - [API docs](https://adafruit.github.io/Adafruit_ADXL343/html/class_adafruit___a_d_x_l343.html)
- [Adafruit LiIon or LiPoly Charger BFF Add-On for QT Py](https://www.adafruit.com/product/5397)
    - [Overview | Adafruit LiIon or LiPoly Charger BFF Add-On for QT Py ](https://learn.adafruit.com/adafruit-qt-py-charger-bff/overview)
- [Lithium Ion Polymer Battery with Short Cable - 3.7V 420mAh](https://www.adafruit.com/product/4236)
- [STEMMA QT / Qwiic JST SH 4-Pin Cable - 50mm Long](https://www.adafruit.com/product/4399)

# Libraries
## Adafruit_ADXL343
Install right through the Libraries tool in Ardino.

Note: one thing that took me a bit of digging to find was the line "The STEMMA QT connector IO pins in Arduino are 19 (SCL1) and 22 (SDA1) and are available on Wire1." In other words, you construct the Adafruit_ADXL343 like 
```
#include <Wire.h>
Adafruit_ADXL343 accel = Adafruit_ADXL343(0x53, &Wire1); # Address (first arg) doesn't matter apparently?
```

# BLECombo
This one required a little digging.  I started off using the [ESP32-BLE-Keyboard](https://github.com/T-vK/ESP32-BLE-Keyboard) and [ESP32-BLE-Mouse](https://github.com/T-vK/ESP32-BLE-Mouse) libraries by [T-vK](https://github.com/T-vK), but found that they don't both work in the same sketch.  Then I came across this issue: [Support mouse and keyboard profile](https://github.com/T-vK/ESP32-BLE-Keyboard/issues/172) and I ended up using the [ESP32-BLE-Combo](https://github.com/Georgegipa/ESP32-BLE-Combo) library that does both. There is a more recent fork from [alexz006](https://github.com/alexz006/ESP32-BLE-Combo), but I haven't had any problems with the Georgegipa fork, so I just stuck with that. 

