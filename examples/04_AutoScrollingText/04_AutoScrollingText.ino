/*
 * کتابخانه: PersianOLED
 * مثال ۴: نمایش متن متحرک و اسکرول افقی فارسی
 * سازگار با: ESP8266, ESP32, Arduino Uno, Nano, RP2040, STM32
 */

#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include "PersianOLED.h"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
PersianOLED persian;

String scrollText;
int textWidth = 0;
int textOffset = 0;

void setup() {
  u8g2.begin();
  u8g2.enableUTF8Print();
  u8g2.setFont(u8g2_font_cu12_t_arabic);
  
  // شکل‌دهی متن متحرک
  scrollText = persian.reshape("پروژه متن فارسی با قابلیت اسکرول روان");
  textWidth = u8g2.getUTF8Width(scrollText.c_str());
  textOffset = -textWidth;
}

void loop() {
  u8g2.clearBuffer();
  u8g2.drawFrame(0, 0, 128, 64);
  
  // سربرگ ثابت
  String title = persian.reshape("اخبار و اعلانات");
  int titleWidth = u8g2.getUTF8Width(title.c_str());
  u8g2.drawUTF8((128 - titleWidth) / 2, 12, title.c_str());
  
  // خط جداکننده
  u8g2.drawHLine(0, 15, 128);
  
  // متن متحرک
  u8g2.drawUTF8(textOffset, 40, scrollText.c_str());
  
  // حرکت متن به سمت راست
  textOffset += 2;
  if (textOffset > 128) {
    textOffset = -textWidth;
  }
  
  u8g2.sendBuffer();
  delay(30);
}
