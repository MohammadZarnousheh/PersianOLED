# PersianOLED

> **Persian & English Documentation**  
> [راهنمای فارسی](#راهنمای-فارسی) | [English Guide](#english-guide)

---

# راهنمای فارسی

کتابخانه **PersianOLED** برای نمایش صحیح و زیبای متن‌های **فارسی و عربی** روی نمایشگرهای OLED (مانند SSD1306) در آردوینو و بردهای ESP8266 و ESP32 طراحی شده است.

این کتابخانه به‌صورت خودکار:
- حروف فارسی را به شکل درست به یکدیگر می‌چسباند (**Reshape**).
- جهت متن را راست‌به‌چپ مرتب می‌کند (**BiDi**).
- ارقام و کلمات انگلیسی را بدون برعکس شدن در متن قرار می‌دهد.

### ویژگی‌ها
* پشتیبانی از تمامی ۳۲ حرف فارسی (`گ، چ، پ، ژ، ک، ی`).
* نمایش بدون نقص ارقام و اعداد اعشاری (بدون وارونه شدن اعداد).
* پشتیبانی همزمان از متن ترکیبی فارسی و انگلیسی.
* ۳ اندازه متن استاندارد (`Small`, `Medium`, `Large`).
* توابع تراز متن: `printCenter` (وسط‌چین) و `printRight` (راست‌چین).
* بسیار سبک با مصرف حداقل حافظه RAM.

### سیم‌بندی ماژول OLED (I2C)

| پایه OLED | Arduino Uno / Nano | ESP8266 | ESP32 | RP2040 (Pico) |
| :---: | :---: | :---: | :---: | :---: |
| **GND** | GND | GND | GND | GND |
| **VCC** | 5V / 3.3V | 3.3V | 3.3V | 3.3V |
| **SCL** | A5 | D1 (GPIO 5) | GPIO 22 | GP5 (Pin 7) |
| **SDA** | A4 | D2 (GPIO 4) | GPIO 21 | GP4 (Pin 6) |

### نصب در Arduino IDE
1. پوشه `PersianOLED` را در مسیر کتابخانه‌های آردوینو کپی کنید (`Documents/Arduino/libraries/`).
2. کتابخانه **U8g2** را نیز از بخش Library Manager نصب کنید.
3. از مسیر **File -> Examples -> PersianOLED** نمونه کدها را اجرا کنید.

### نمونه کد ساده (Quick Start)

```cpp
#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include "PersianOLED.h"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
PersianOLED persian;

void setup() {
  u8g2.begin();
  u8g2.enableUTF8Print();
}

void loop() {
  u8g2.clearBuffer();
  u8g2.drawFrame(0, 0, 128, 64);
  
  // چاپ متن در وسط صفحه
  persian.printCenter(u8g2, 36, "سلام دنیا");
  
  u8g2.sendBuffer();
  delay(1000);
}
```

### نمونه کدهای موجود (Examples)
* **01_BasicPersianText:** نمایش متن پایه فارسی در مرکز صفحه.
* **02_MixedPersianEnglish:** ترکیب کلمات فارسی و انگلیسی با نمادها.
* **03_SensorsAndVariables:** نمایش دما و رطوبت با ارقام مرتب فارسی.
* **04_AutoScrollingText:** اسکرول افقی متن‌های طولانی.
* **05_TextSizesAndStyles:** نمایش متن در ۳ اندازه مختلف.
* **06_SalamDonyaTextSizes:** چرخش کلمه «سلام دنیا» در سایزهای مختلف.

---

# English Guide

**PersianOLED** is a lightweight Arduino C++ library for displaying **Persian and Arabic text** correctly on OLED displays (SSD1306 128x64) using Arduino, ESP8266, ESP32, and RP2040.

It automatically handles:
- Contextual character reshaping (connecting letters properly).
- Right-to-Left (BiDi) text ordering.
- Proper digit sequence and mixed English/Persian text without flipping.

### Features
* Complete 32-letter Persian alphabet support (`گ چ پ ژ ک ی`).
* Correct number ordering (e.g. `58` stays `58`, decimals like `26.4`).
* Seamless mixed Persian and English text.
* 3 pre-configured font sizes (`Small`, `Medium`, `Large`).
* Simple alignment functions: `printCenter`, `printRight`, `printLeft`.
* Low memory footprint for standard microcontrollers.

### I2C Wiring Table

| OLED Pin | Arduino Uno / Nano | ESP8266 | ESP32 | RP2040 (Pico) |
| :---: | :---: | :---: | :---: | :---: |
| **GND** | GND | GND | GND | GND |
| **VCC** | 5V / 3.3V | 3.3V | 3.3V | 3.3V |
| **SCL** | A5 | D1 (GPIO 5) | GPIO 22 | GP5 (Pin 7) |
| **SDA** | A4 | D2 (GPIO 4) | GPIO 21 | GP4 (Pin 6) |

### Installation
1. Copy the `PersianOLED` folder into your Arduino libraries directory (`Documents/Arduino/libraries/`).
2. Install the **U8g2** library via Arduino Library Manager.
3. Open examples from **File -> Examples -> PersianOLED**.

### Quick Start Example

```cpp
#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include "PersianOLED.h"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
PersianOLED persian;

void setup() {
  u8g2.begin();
  u8g2.enableUTF8Print();
}

void loop() {
  u8g2.clearBuffer();
  u8g2.drawFrame(0, 0, 128, 64);
  
  // Print centered Persian text
  persian.printCenter(u8g2, 36, "سلام دنیا");
  
  u8g2.sendBuffer();
  delay(1000);
}
```

### Included Examples
* **01_BasicPersianText:** Basic centered Persian text.
* **02_MixedPersianEnglish:** Mixed Persian and English text with punctuation.
* **03_SensorsAndVariables:** Real-time sensor display with Persian digits.
* **04_AutoScrollingText:** Smooth horizontal scrolling text banner.
* **05_TextSizesAndStyles:** Demonstrating Small, Medium, and Large font sizes.
* **06_SalamDonyaTextSizes:** Cycling text through multiple sizes.

---

### License
MIT License - Free for personal and commercial use.
