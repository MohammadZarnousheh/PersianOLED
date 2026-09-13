/*
 * کتابخانه: PersianOLED
 * مثال ۲: نمایش متن فارسی به همراه ارقام و علائم نگارشی
 * سازگار با: ESP8266, ESP32, Arduino Uno, Nano, RP2040, STM32
 */

#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include "PersianOLED.h"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
PersianOLED persian;

void setup() {
  u8g2.begin();
  u8g2.enableUTF8Print();
  u8g2.setFont(u8g2_font_cu12_t_arabic);
  persian.setConvertDigits(true);
}

void loop() {
  u8g2.clearBuffer();
  u8g2.drawFrame(0, 0, 128, 64);
  
  // سطر ۱: متن فارسی با عدد
  String line1 = persian.reshape("دستگاه شماره ۱۲");
  int w1 = u8g2.getUTF8Width(line1.c_str());
  u8g2.drawUTF8(124 - w1, 20, line1.c_str());
  
  // خط جداکننده
  u8g2.drawHLine(4, 26, 120);
  
  // سطر ۲: متن با علائم نگارشی
  String line2 = persian.reshape("سیگنال:(عالی)");
  int w2 = u8g2.getUTF8Width(line2.c_str());
  u8g2.drawUTF8(124 - w2, 45, line2.c_str());
  
  u8g2.sendBuffer();
  delay(3000);
}
