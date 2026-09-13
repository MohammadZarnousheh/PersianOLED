#ifndef PERSIAN_OLED_H
#define PERSIAN_OLED_H

#include <Arduino.h>

#ifdef __has_include
  #if __has_include(<U8g2lib.h>)
    #include <U8g2lib.h>
    #define PERSIAN_OLED_HAS_U8G2 1
  #endif
#endif

#ifndef PERSIAN_OLED_HAS_U8G2
class U8G2;
#endif

// اندازه قلم‌های استاندارد فارسی برای نمایشگر OLED
enum PersianFontSize {
    PERSIAN_FONT_SMALL = 1,   // ~10-12px (u8g2_font_cu12_t_arabic) - مناسب ۳ الی ۴ سطر متن یا سنسورها
    PERSIAN_FONT_MEDIUM = 2,  // ~16px (u8g2_font_unifont_t_arabic) - استاندارد با وضوح بالا
    PERSIAN_FONT_LARGE = 3    // ~20px (u8g2_font_10x20_t_arabic) - تیتر درشت و اعلانات
};

// تراز متن
enum PersianAlign {
    PERSIAN_ALIGN_RIGHT = 0,
    PERSIAN_ALIGN_CENTER = 1,
    PERSIAN_ALIGN_LEFT = 2
};

class PersianOLED {
public:
    struct CharGlyph {
        uint16_t unicode;
        bool joinable;
        uint16_t isolated;
        uint16_t initial;
        uint16_t medial;
        uint16_t final_form;
    };

    PersianOLED();

    // Main reshape function: Converts standard Persian UTF-8 text to joined contextual glyphs with BiDi ordering
    String reshape(const String& input);
    String reshape(const char* input);

    // Converts ASCII English digits (0-9) to Persian digits (۰-۹)
    String toPersianDigits(const String& input);
    String toPersianDigits(const char* input);

    // Configuration
    void setConvertDigits(bool enable);
    bool getConvertDigits() const;

    // --- روش‌های تنظیم اندازه متن و چاپ سریع برای U8G2 ---
    // تنظیم فونت و سایز روی نمایشگر U8g2
    void setFont(U8G2& display, PersianFontSize size);
    void setTextSize(U8G2& display, uint8_t size); // 1 = Small, 2 = Medium, 3 = Large

    // چاپ مستقیم با تبدیل خودکار و تنظیم سایز
    int print(U8G2& display, int x, int y, const String& text, PersianFontSize size = PERSIAN_FONT_MEDIUM);
    int print(U8G2& display, int x, int y, const char* text, PersianFontSize size = PERSIAN_FONT_MEDIUM);

    // چاپ راست‌چین (مخصوص زبان فارسی)
    int printRight(U8G2& display, int y, const String& text, PersianFontSize size = PERSIAN_FONT_MEDIUM, int margin = 2);
    int printRight(U8G2& display, int y, const char* text, PersianFontSize size = PERSIAN_FONT_MEDIUM, int margin = 2);

    // چاپ وسط‌چین (مناسب تیترها، پیام‌ها و ساعت)
    int printCenter(U8G2& display, int y, const String& text, PersianFontSize size = PERSIAN_FONT_MEDIUM);
    int printCenter(U8G2& display, int y, const char* text, PersianFontSize size = PERSIAN_FONT_MEDIUM);

    // چاپ چپ‌چین
    int printLeft(U8G2& display, int y, const String& text, PersianFontSize size = PERSIAN_FONT_MEDIUM, int margin = 2);
    int printLeft(U8G2& display, int y, const char* text, PersianFontSize size = PERSIAN_FONT_MEDIUM, int margin = 2);

    // محاسبه طول متن شکل‌گرفته بر حسب پیکسل
    int getTextWidth(U8G2& display, const String& text, PersianFontSize size = PERSIAN_FONT_MEDIUM);

private:
    bool _convertDigits;

    static uint16_t getUnicodeFromUTF8(const uint8_t* bytes, int& index, int length);
    static void appendUnicodeToUTF8(uint16_t code, String& output);
    static const CharGlyph* findCharGlyph(uint16_t code);
    static bool isPersianChar(uint16_t code);
    static bool isDigit(uint16_t code);
    static bool isLatin(uint16_t code);
};

#endif