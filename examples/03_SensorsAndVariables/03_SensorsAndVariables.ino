/*
 * کتابخانه: PersianOLED
 * مثال ۳: نمایش مقادیر متغیر سنسورها (دما، رطوبت) با ارقام فارسی
 * سازگار با: ESP8266, ESP32, Arduino Uno, Nano, RP2040, STM32
 */

#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include "PersianOLED.h"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
PersianOLED persian;

// متغیرهای سنسور
float temperature = 26.4;
int humidity = 58;

void setup() {
  u8g2.begin();
  u8g2.enableUTF8Print();
}

void loop() {
  temperature += 0.1;
  if (temperature > 35.0) temperature = 22.0;

  u8g2.clearBuffer();
  u8g2.drawFrame(0, 0, 128, 64);
  
  // سربرگ
  u8g2.setFont(u8g2_font_cu12_t_arabic);
  String title = persian.reshape("ایستگاه هواشناسی");
  int wTitle = u8g2.getUTF8Width(title.c_str());
  u8g2.drawUTF8((128 - wTitle) / 2, 12, title.c_str());

  // نمایش دما
  String tempStr = "دما: " + String(temperature, 1) + " درجه";
  String faTemp = persian.reshape(tempStr);
  int wTemp = u8g2.getUTF8Width(faTemp.c_str());
  u8g2.drawUTF8(124 - wTemp, 36, faTemp.c_str());

  // نمایش رطوبت
  String humStr = "رطوبت: " + String(humidity) + " درصد";
  String faHum = persian.reshape(humStr);
  int wHum = u8g2.getUTF8Width(faHum.c_str());
  u8g2.drawUTF8(124 - wHum, 54, faHum.c_str());

  u8g2.sendBuffer();
  delay(1000);
}
