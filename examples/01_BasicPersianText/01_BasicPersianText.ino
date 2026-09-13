/*
 * کتابخانه: PersianOLED
 * مثال ۱: نمایش متن فارسی پایه روی نمایشگر OLED SSD1306
 * سازگار با: ESP8266, ESP32, Arduino Uno, Nano, RP2040, STM32
 */

#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include "PersianOLED.h"

// راه‌اندازی نمایشگر OLED SSD1306 با رابط I2C
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
PersianOLED persian;

void setup() {
  u8g2.begin();
  u8g2.enableUTF8Print();
  u8g2.setFont(u8g2_font_cu12_t_arabic);
}

void loop() {
  u8g2.clearBuffer();
  u8g2.drawFrame(0, 0, 128, 64);
  
  // چاپ متن فارسی در مرکز صفحه
  persian.printCenter(u8g2, 36, "سلام دنیا");
  
  u8g2.sendBuffer();
  delay(1000);
}
