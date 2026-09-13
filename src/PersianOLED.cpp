#include "PersianOLED.h"

// Table of all Persian and Arabic letters with their 4 contextual presentation forms (Unicode Forms-A and Forms-B)
static const PersianOLED::CharGlyph PERSIAN_GLYPH_TABLE[] = {
    // Unicode, LeftJoinable, Isolated, Initial, Medial, Final
    { 0x0622, false, 0xFE81, 0xFE81, 0xFE82, 0xFE82 }, // آ
    { 0x0627, false, 0xFE8D, 0xFE8D, 0xFE8E, 0xFE8E }, // ا
    { 0x0623, false, 0xFE83, 0xFE83, 0xFE84, 0xFE84 }, // أ
    { 0x0625, false, 0xFE87, 0xFE87, 0xFE88, 0xFE88 }, // إ
    { 0x0624, false, 0xFE85, 0xFE85, 0xFE86, 0xFE86 }, // ؤ
    { 0x0626, true,  0xFE89, 0xFE8B, 0xFE8C, 0xFE8A }, // ئ
    { 0x0621, false, 0xFE80, 0xFE80, 0xFE80, 0xFE80 }, // ء
    { 0x0628, true,  0xFE8F, 0xFE91, 0xFE92, 0xFE90 }, // ب
    { 0x067E, true,  0xFB56, 0xFB58, 0xFB59, 0xFB57 }, // پ
    { 0x062A, true,  0xFE95, 0xFE97, 0xFE98, 0xFE96 }, // ت
    { 0x062B, true,  0xFE99, 0xFE9B, 0xFE9C, 0xFE9A }, // ث
    { 0x062C, true,  0xFE9D, 0xFE9F, 0xFEA0, 0xFE9E }, // ج
    { 0x0686, true,  0xFB7A, 0xFB7C, 0xFB7D, 0xFB7B }, // چ
    { 0x062D, true,  0xFEA1, 0xFEA3, 0xFEA4, 0xFEA2 }, // ح
    { 0x062E, true,  0xFEA5, 0xFEA7, 0xFEA8, 0xFEA6 }, // خ
    { 0x062F, false, 0xFEA9, 0xFEA9, 0xFEAA, 0xFEAA }, // د
    { 0x0630, false, 0xFEAB, 0xFEAB, 0xFEAC, 0xFEAC }, // ذ
    { 0x0631, false, 0xFEAD, 0xFEAD, 0xFEAE, 0xFEAE }, // ر
    { 0x0632, false, 0xFEAF, 0xFEAF, 0xFEB0, 0xFEB0 }, // ز
    { 0x0698, false, 0xFB8A, 0xFB8A, 0xFB8B, 0xFB8B }, // ژ
    { 0x0633, true,  0xFEB1, 0xFEB3, 0xFEB4, 0xFEB2 }, // س
    { 0x0634, true,  0xFEB5, 0xFEB7, 0xFEB8, 0xFEB6 }, // ش
    { 0x0635, true,  0xFEB9, 0xFEBB, 0xFEBC, 0xFEBA }, // ص
    { 0x0636, true,  0xFEBD, 0xFEBF, 0xFEC0, 0xFEBE }, // ض
    { 0x0637, true,  0xFEC1, 0xFEC3, 0xFEC4, 0xFEC2 }, // ط
    { 0x0638, true,  0xFEC5, 0xFEC7, 0xFEC8, 0xFEC6 }, // ظ
    { 0x0639, true,  0xFEC9, 0xFECB, 0xFECC, 0xFECA }, // ع
    { 0x063A, true,  0xFECD, 0xFECF, 0xFED0, 0xFECE }, // غ
    { 0x0641, true,  0xFED1, 0xFED3, 0xFED4, 0xFED2 }, // ف
    { 0x0642, true,  0xFED5, 0xFED7, 0xFED8, 0xFED6 }, // ق
    { 0x0643, true,  0xFED9, 0xFEDB, 0xFEDC, 0xFEDA }, // ك (عربی)
    { 0x06A9, true,  0xFB8E, 0xFB90, 0xFB91, 0xFB8F }, // ک (فارسی)
    { 0x06AF, true,  0xFB92, 0xFB94, 0xFB95, 0xFB93 }, // گ
    { 0x0644, true,  0xFEDD, 0xFEDF, 0xFEE0, 0xFEDE }, // ل
    { 0x0645, true,  0xFEE1, 0xFEE3, 0xFEE4, 0xFEE2 }, // م
    { 0x0646, true,  0xFEE5, 0xFEE7, 0xFEE8, 0xFEE6 }, // ن
    { 0x0648, false, 0xFEED, 0xFEED, 0xFEEE, 0xFEEE }, // و
    { 0x0647, true,  0xFEE9, 0xFEEB, 0xFEEC, 0xFEEA }, // ه
    { 0x06C0, false, 0xFBA4, 0xFBA4, 0xFBA5, 0xFBA5 }, // ۀ
    { 0x0629, false, 0xFE93, 0xFE93, 0xFE94, 0xFE94 }, // ة
    { 0x064A, true,  0xFEEF, 0xFEF3, 0xFEF4, 0xFEF0 }, // ي (عربی)
    { 0x06CC, true,  0xFEEF, 0xFEF3, 0xFEF4, 0xFEF0 }, // ی (فارسی: تنها و آخر بدون نقطه، اول و وسط دونقطه)
    { 0x0649, true,  0xFEEF, 0xFEF3, 0xFEF4, 0xFEF0 }  // ى (الف مقصوره)
};

static const size_t GLYPH_TABLE_SIZE = sizeof(PERSIAN_GLYPH_TABLE) / sizeof(PERSIAN_GLYPH_TABLE[0]);

PersianOLED::PersianOLED() : _convertDigits(true) {}

void PersianOLED::setConvertDigits(bool enable) {
    _convertDigits = enable;
}

bool PersianOLED::getConvertDigits() const {
    return _convertDigits;
}

const PersianOLED::CharGlyph* PersianOLED::findCharGlyph(uint16_t code) {
    for (size_t i = 0; i < GLYPH_TABLE_SIZE; i++) {
        if (PERSIAN_GLYPH_TABLE[i].unicode == code) {
            return &PERSIAN_GLYPH_TABLE[i];
        }
    }
    return nullptr;
}

bool PersianOLED::isPersianChar(uint16_t code) {
    return findCharGlyph(code) != nullptr;
}

bool PersianOLED::isDigit(uint16_t code) {
    return (code >= '0' && code <= '9') || (code >= 0x06F0 && code <= 0x06F9) || (code >= 0x0660 && code <= 0x0669);
}

bool PersianOLED::isLatin(uint16_t code) {
    return (code >= 'a' && code <= 'z') || (code >= 'A' && code <= 'Z');
}

uint16_t PersianOLED::getUnicodeFromUTF8(const uint8_t* bytes, int& index, int length) {
    if (index >= length) return 0;
    uint8_t b1 = bytes[index++];

    // 1-byte ASCII
    if ((b1 & 0x80) == 0) {
        return b1;
    }
    // 2-byte UTF-8
    if ((b1 & 0xE0) == 0xC0 && index < length) {
        uint8_t b2 = bytes[index++];
        return ((b1 & 0x1F) << 6) | (b2 & 0x3F);
    }
    // 3-byte UTF-8
    if ((b1 & 0xF0) == 0xE0 && index + 1 < length) {
        uint8_t b2 = bytes[index++];
        uint8_t b3 = bytes[index++];
        return ((b1 & 0x0F) << 12) | ((b2 & 0x3F) << 6) | (b3 & 0x3F);
    }
    return 0;
}

void PersianOLED::appendUnicodeToUTF8(uint16_t code, String& output) {
    if (code < 0x80) {
        output += (char)code;
    } else if (code < 0x800) {
        output += (char)(0xC0 | ((code >> 6) & 0x1F));
        output += (char)(0x80 | (code & 0x3F));
    } else {
        output += (char)(0xE0 | ((code >> 12) & 0x0F));
        output += (char)(0x80 | ((code >> 6) & 0x3F));
        output += (char)(0x80 | (code & 0x3F));
    }
}

String PersianOLED::toPersianDigits(const char* input) {
    if (!input) return "";
    String result = "";
    while (*input) {
        char c = *input++;
        if (c >= '0' && c <= '9') {
            uint16_t faDigit = 0x06F0 + (c - '0');
            appendUnicodeToUTF8(faDigit, result);
        } else {
            result += c;
        }
    }
    return result;
}

String PersianOLED::toPersianDigits(const String& input) {
    return toPersianDigits(input.c_str());
}

String PersianOLED::reshape(const char* input) {
    if (!input || strlen(input) == 0) return "";

    String processedInput = input;
    if (_convertDigits) {
        processedInput = toPersianDigits(processedInput);
    }

    const uint8_t* rawBytes = (const uint8_t*)processedInput.c_str();
    int byteLen = processedInput.length();
    int idx = 0;

    // First decode all UTF-8 characters into 16-bit unicode array
    // Max 128 characters for typical OLED string
    uint16_t unicodes[160];
    int charCount = 0;

    while (idx < byteLen && charCount < 159) {
        uint16_t u = getUnicodeFromUTF8(rawBytes, idx, byteLen);
        if (u != 0) {
            unicodes[charCount++] = u;
        }
    }
    unicodes[charCount] = 0;

    if (charCount == 0) return "";

    // 1. Reshaping pass (Calculate isolated, initial, medial, final forms & Lam-Alef)
    uint16_t reshaped[160];
    int reshapedCount = 0;

    for (int i = 0; i < charCount; i++) {
        uint16_t code = unicodes[i];

        // Lam-Alef ligatures check (لا، لآ، لأ، لإ)
        if (code == 0x0644 && (i + 1 < charCount)) {
            uint16_t nextCode = unicodes[i + 1];
            bool prevJoins = (i > 0 && isPersianChar(unicodes[i - 1]) && findCharGlyph(unicodes[i - 1])->joinable);
            uint16_t lig = 0;

            if (nextCode == 0x0622) lig = prevJoins ? 0xFEF6 : 0xFEF5; // لآ
            else if (nextCode == 0x0623) lig = prevJoins ? 0xFEF8 : 0xFEF7; // لأ
            else if (nextCode == 0x0625) lig = prevJoins ? 0xFEFA : 0xFEF9; // لإ
            else if (nextCode == 0x0627) lig = prevJoins ? 0xFEFC : 0xFEFB; // لا

            if (lig != 0) {
                reshaped[reshapedCount++] = lig;
                i++; // Skip next character
                continue;
            }
        }

        const CharGlyph* glyph = findCharGlyph(code);
        if (glyph != nullptr) {
            bool prevJoins = false;
            if (i > 0) {
                const CharGlyph* prevGlyph = findCharGlyph(unicodes[i - 1]);
                if (prevGlyph && prevGlyph->joinable) {
                    prevJoins = true;
                }
            }

            bool nextJoins = false;
            if (i + 1 < charCount) {
                const CharGlyph* nextGlyph = findCharGlyph(unicodes[i + 1]);
                if (nextGlyph != nullptr) {
                    nextJoins = true;
                }
            }

            uint16_t form;
            if (prevJoins && nextJoins && glyph->joinable) {
                form = glyph->medial;
            } else if (prevJoins) {
                form = glyph->final_form;
            } else if (nextJoins && glyph->joinable) {
                form = glyph->initial;
            } else {
                form = glyph->isolated;
            }

            reshaped[reshapedCount++] = form;
        } else {
            reshaped[reshapedCount++] = code;
        }
    }

    // 2. BiDi Reordering:
    // Classify character types with context for numbers (decimal points, colons, signs)
    enum TokenType { T_RTL, T_LTR, T_NUM, T_PUNCT, T_SPACE };
    struct Token {
        int start;
        int length;
        TokenType type;
    };

    TokenType charTypes[160];
    for (int i = 0; i < reshapedCount; i++) {
        uint16_t c = reshaped[i];

        if (isDigit(c)) {
            charTypes[i] = T_NUM;
        } else if ((c == '.' || c == '/' || c == ':' || c == ',' || c == 0x066B || c == 0x066C) &&
                   (i > 0 && isDigit(reshaped[i - 1])) &&
                   (i + 1 < reshapedCount && isDigit(reshaped[i + 1]))) {
            // Number inner separators (e.g. 26.4, 12:45, 1403/06/20)
            charTypes[i] = T_NUM;
        } else if ((c == '-' || c == '+') &&
                   (i + 1 < reshapedCount && isDigit(reshaped[i + 1])) &&
                   (i == 0 || reshaped[i - 1] == ' ' || reshaped[i - 1] == '\t' || reshaped[i - 1] == '(')) {
            // Leading number sign (e.g. -15, +25)
            charTypes[i] = T_NUM;
        } else if ((c == '%' || c == 0x066A) && (i > 0 && isDigit(reshaped[i - 1]))) {
            // Trailing percent sign (e.g. 58%, 58٪)
            charTypes[i] = T_NUM;
        } else if (isLatin(c)) {
            charTypes[i] = T_LTR;
        } else if ((c >= 0x0600 && c <= 0x06FF) || (c >= 0xFB50 && c <= 0xFDFF) || (c >= 0xFE70 && c <= 0xFEFF)) {
            charTypes[i] = T_RTL;
        } else if (c == ' ' || c == '\t') {
            charTypes[i] = T_SPACE;
        } else {
            charTypes[i] = T_PUNCT;
        }
    }

    Token tokens[40];
    int tokenCount = 0;
    int currStart = 0;
    TokenType currType = charTypes[0];

    for (int i = 1; i < reshapedCount; i++) {
        TokenType t = charTypes[i];
        // Merge adjacent LTR words and Numbers into single LTR run (e.g. ESP32, WiFi2)
        bool sameGroup = (t == currType) || 
                         ((currType == T_LTR || currType == T_NUM) && 
                          (t == T_LTR || t == T_NUM));
        if (!sameGroup) {
            if (tokenCount < 40) {
                tokens[tokenCount++] = { currStart, i - currStart, currType };
            }
            currStart = i;
            currType = t;
        }
    }
    if (tokenCount < 40) {
        tokens[tokenCount++] = { currStart, reshapedCount - currStart, currType };
    }

    // 3. Assemble output in Right-to-Left order for OLED screen printing
    String finalResult = "";
    finalResult.reserve(reshapedCount * 2);

    for (int t = tokenCount - 1; t >= 0; t--) {
        Token tok = tokens[t];

        if (tok.type == T_RTL) {
            // Reverse characters within RTL words
            for (int k = tok.start + tok.length - 1; k >= tok.start; k--) {
                appendUnicodeToUTF8(reshaped[k], finalResult);
            }
        } else if (tok.type == T_PUNCT) {
            // Reverse punctuation and swap brackets
            for (int k = tok.start + tok.length - 1; k >= tok.start; k--) {
                uint16_t p = reshaped[k];
                if (p == '(') p = ')';
                else if (p == ')') p = '(';
                else if (p == '[') p = ']';
                else if (p == ']') p = '[';
                else if (p == '{') p = '}';
                else if (p == '}') p = '{';
                appendUnicodeToUTF8(p, finalResult);
            }
        } else {
            // LTR words, Numbers, Spaces retain their forward order
            for (int k = tok.start; k < tok.start + tok.length; k++) {
                appendUnicodeToUTF8(reshaped[k], finalResult);
            }
        }
    }

    return finalResult;
}

String PersianOLED::reshape(const String& input) {
    return reshape(input.c_str());
}

#if defined(__has_include)
  #if __has_include(<U8g2lib.h>)
    #include <U8g2lib.h>
    #define PERSIAN_OLED_HAS_U8G2_IMPL 1
  #endif
#endif

#if defined(PERSIAN_OLED_HAS_U8G2) || defined(PERSIAN_OLED_HAS_U8G2_IMPL)
void PersianOLED::setFont(U8G2& display, PersianFontSize size) {
    display.enableUTF8Print();
    switch (size) {
        case PERSIAN_FONT_SMALL:
            display.setFont(u8g2_font_cu12_t_arabic);
            break;
        case PERSIAN_FONT_LARGE:
            display.setFont(u8g2_font_10x20_t_arabic);
            break;
        case PERSIAN_FONT_MEDIUM:
        default:
            display.setFont(u8g2_font_unifont_t_arabic);
            break;
    }
}

void PersianOLED::setTextSize(U8G2& display, uint8_t size) {
    if (size <= 1) {
        setFont(display, PERSIAN_FONT_SMALL);
    } else if (size == 2) {
        setFont(display, PERSIAN_FONT_MEDIUM);
    } else {
        setFont(display, PERSIAN_FONT_LARGE);
    }
}

int PersianOLED::getTextWidth(U8G2& display, const String& text, PersianFontSize size) {
    setFont(display, size);
    String reshaped = reshape(text);
    return display.getUTF8Width(reshaped.c_str());
}

int PersianOLED::print(U8G2& display, int x, int y, const String& text, PersianFontSize size) {
    setFont(display, size);
    String reshaped = reshape(text);
    display.drawUTF8(x, y, reshaped.c_str());
    return display.getUTF8Width(reshaped.c_str());
}

int PersianOLED::print(U8G2& display, int x, int y, const char* text, PersianFontSize size) {
    return print(display, x, y, String(text), size);
}

int PersianOLED::printRight(U8G2& display, int y, const String& text, PersianFontSize size, int margin) {
    setFont(display, size);
    String reshaped = reshape(text);
    int width = display.getUTF8Width(reshaped.c_str());
    int dispWidth = display.getDisplayWidth();
    int x = dispWidth - width - margin;
    if (x < 0) x = 0;
    display.drawUTF8(x, y, reshaped.c_str());
    return width;
}

int PersianOLED::printRight(U8G2& display, int y, const char* text, PersianFontSize size, int margin) {
    return printRight(display, y, String(text), size, margin);
}

int PersianOLED::printCenter(U8G2& display, int y, const String& text, PersianFontSize size) {
    setFont(display, size);
    String reshaped = reshape(text);
    int width = display.getUTF8Width(reshaped.c_str());
    int dispWidth = display.getDisplayWidth();
    int x = (dispWidth - width) / 2;
    if (x < 0) x = 0;
    display.drawUTF8(x, y, reshaped.c_str());
    return width;
}

int PersianOLED::printCenter(U8G2& display, int y, const char* text, PersianFontSize size) {
    return printCenter(display, y, String(text), size);
}

int PersianOLED::printLeft(U8G2& display, int y, const String& text, PersianFontSize size, int margin) {
    setFont(display, size);
    String reshaped = reshape(text);
    display.drawUTF8(margin, y, reshaped.c_str());
    return display.getUTF8Width(reshaped.c_str());
}

int PersianOLED::printLeft(U8G2& display, int y, const char* text, PersianFontSize size, int margin) {
    return printLeft(display, y, String(text), size, margin);
}
#endif

