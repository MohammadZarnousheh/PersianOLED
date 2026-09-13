/*
 * کتابخانه: PersianOLED
 * مثال ۵: روش‌های مختلف تنظیم اندازه متن (TextSize)
 * سازگار با: ESP8266, ESP32, Arduino Uno, Nano, RP2040, STM32
 */

#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include "PersianOLED.h"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
PersianOLED persian;

int screenMode = 0;

void setup() {
  u8g2.begin();
  u8g2.enableUTF8Print();
}

// حالت ۱: نمایش هر ۳ اندازه همزمان در یک صفحه
void drawMultiSizeScreen() {
  u8g2.clearBuffer();
  u8g2.drawFrame(0, 0, 128, 64);

  // تیتر درشت (Large)
  persian.printCenter(u8g2, 13, "سامانه هوشمند", PERSIAN_FONT_LARGE);
  
  // خط جداکننده
  u8g2.drawHLine(14, 18, 100);

  // متن متوسط (Medium)
  persian.printRight(u8g2, 36, "وضعیت: آنلاین", PERSIAN_FONT_MEDIUM, 6);

  // متن ریز (Small)
  persian.printRight(u8g2, 54, "دما: ۲۴.۵ درجه", PERSIAN_FONT_SMALL, 6);

  u8g2.sendBuffer();
}

// حالت ۲: نمایش پیام با فونت متوسط در مرکز صفحه
void drawMediumCentered() {
  u8g2.clearBuffer();
  u8g2.drawFrame(0, 0, 128, 64);

  persian.printCenter(u8g2, 24, "خوش آمدید", PERSIAN_FONT_MEDIUM);
  persian.printCenter(u8g2, 46, "پروژه OLED فارسی", PERSIAN_FONT_MEDIUM);

  u8g2.sendBuffer();
}

// حالت ۳: نمایش متن ۴ سطری با فونت ریز
void drawCompactFourLines() {
  u8g2.clearBuffer();
  u8g2.drawFrame(0, 0, 128, 64);

  persian.printRight(u8g2, 14, "سنسور: فعال", PERSIAN_FONT_SMALL, 6);
  persian.printRight(u8g2, 28, "مخزن: ۸۲ درصد", PERSIAN_FONT_SMALL, 6);
  persian.printRight(u8g2, 42, "ولتاژ: ۱۲ ولت", PERSIAN_FONT_SMALL, 6);
  persian.printRight(u8g2, 56, "سرور: آنلاین", PERSIAN_FONT_SMALL, 6);

  u8g2.sendBuffer();
}

// حالت ۴: ساعت و عنوان با فونت درشت
void drawLargeTitleScreen() {
  u8g2.clearBuffer();
  u8g2.drawFrame(0, 0, 128, 64);

  persian.printCenter(u8g2, 20, "ساعت کارکرد", PERSIAN_FONT_SMALL);
  persian.printCenter(u8g2, 48, "۱۲:۴۵:۳۰", PERSIAN_FONT_LARGE);

  u8g2.sendBuffer();
}

void loop() {
  switch (screenMode) {
    case 0:
      drawMultiSizeScreen();
      break;
    case 1:
      drawMediumCentered();
      break;
    case 2:
      drawCompactFourLines();
      break;
    case 3:
      drawLargeTitleScreen();
      break;
  }

  screenMode = (screenMode + 1) % 4;
  delay(3000);
}
