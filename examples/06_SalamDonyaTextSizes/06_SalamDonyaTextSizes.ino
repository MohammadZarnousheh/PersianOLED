/*
 * کتابخانه: PersianOLED
 * مثال ۶: چرخش عبارت «سلام دنیا» در اندازه‌های مختلف هر ۲ ثانیه
 * سازگار با: ESP8266, ESP32, Arduino Uno, Nano, RP2040, STM32
 * نمایشگر: SSD1306 OLED 128x64 I2C
 */

#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include "PersianOLED.h"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
PersianOLED persian;

int mode = 0;

void setup() {
  u8g2.begin();
  u8g2.enableUTF8Print();
}

// روش ۱: اندازه ریز (Small)
void showSmallSize() {
  u8g2.clearBuffer();
  u8g2.drawFrame(0, 0, 128, 64);

  persian.printCenter(u8g2, 13, "قلم ریز", PERSIAN_FONT_SMALL);
  u8g2.drawHLine(14, 17, 100);

  persian.printCenter(u8g2, 38, "سلام دنیا", PERSIAN_FONT_SMALL);
  persian.printCenter(u8g2, 54, "فشرده", PERSIAN_FONT_SMALL);

  u8g2.sendBuffer();
}

// روش ۲: اندازه متوسط (Medium)
void showMediumSize() {
  u8g2.clearBuffer();
  u8g2.drawFrame(0, 0, 128, 64);

  persian.printCenter(u8g2, 13, "قلم متوسط", PERSIAN_FONT_SMALL);
  u8g2.drawHLine(14, 17, 100);

  persian.printCenter(u8g2, 38, "سلام دنیا", PERSIAN_FONT_MEDIUM);
  persian.printCenter(u8g2, 54, "خوانا", PERSIAN_FONT_SMALL);

  u8g2.sendBuffer();
}

// روش ۳: اندازه درشت (Large)
void showLargeSize() {
  u8g2.clearBuffer();
  u8g2.drawFrame(0, 0, 128, 64);

  persian.printCenter(u8g2, 13, "قلم درشت", PERSIAN_FONT_SMALL);
  u8g2.drawHLine(14, 17, 100);

  persian.printCenter(u8g2, 44, "سلام دنیا", PERSIAN_FONT_LARGE);

  u8g2.sendBuffer();
}

// روش ۴: نمایش همزمان هر ۳ اندازه
void showAllSizesTogether() {
  u8g2.clearBuffer();
  u8g2.drawFrame(0, 0, 128, 64);

  persian.printCenter(u8g2, 13, "سلام دنیا", PERSIAN_FONT_SMALL);
  u8g2.drawHLine(14, 17, 100);

  persian.printCenter(u8g2, 36, "سلام دنیا", PERSIAN_FONT_MEDIUM);
  persian.printCenter(u8g2, 54, "سلام دنیا", PERSIAN_FONT_SMALL);

  u8g2.sendBuffer();
}

// روش ۵: تغییر سایز با setTextSize
void showViaSetTextSize() {
  u8g2.clearBuffer();
  u8g2.drawFrame(0, 0, 128, 64);

  persian.printCenter(u8g2, 13, "تغییر سایز", PERSIAN_FONT_SMALL);
  u8g2.drawHLine(14, 17, 100);

  persian.setTextSize(u8g2, 2);
  
  String faText = persian.reshape("سلام دنیا");
  int w = u8g2.getUTF8Width(faText.c_str());
  u8g2.drawUTF8((128 - w) / 2, 38, faText.c_str());

  persian.printCenter(u8g2, 54, "سایز دو", PERSIAN_FONT_SMALL);

  u8g2.sendBuffer();
}

void loop() {
  switch (mode) {
    case 0:
      showSmallSize();
      break;
    case 1:
      showMediumSize();
      break;
    case 2:
      showLargeSize();
      break;
    case 3:
      showAllSizesTogether();
      break;
    case 4:
      showViaSetTextSize();
      break;
  }

  mode = (mode + 1) % 5;
  delay(2000);
}
