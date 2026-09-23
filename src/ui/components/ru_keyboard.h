#pragma once
#include "lvgl.h"
#include <cstring>

namespace ru_keyboard {

static const char* RU_KB_BTN_LAYOUT = "layout";

// EN нижний регистр (переопределяем дефолт, добавляем кнопку "RU")
static const char* en_lower_map[] = {
    "q","w","e","r","t","y","u","i","o","p","\n",
    "a","s","d","f","g","h","j","k","l","\n",
    LV_SYMBOL_UP,"z","x","c","v","b","n","m",LV_SYMBOL_BACKSPACE,"\n",
    "1#","RU"," ",LV_SYMBOL_OK,"\n",
    ""
};

// EN верхний регистр
static const char* en_upper_map[] = {
    "Q","W","E","R","T","Y","U","I","O","P","\n",
    "A","S","D","F","G","H","J","K","L","\n",
    LV_SYMBOL_UP,"Z","X","C","V","B","N","M",LV_SYMBOL_BACKSPACE,"\n",
    "1#","RU"," ",LV_SYMBOL_OK,"\n",
    ""
};

// RU нижний регистр (ЙЦУКЕН)
static const char* ru_lower_map[] = {
    "\xD0\xB9","\xD1\x86","\xD1\x83","\xD0\xBA","\xD0\xB5","\xD0\xBD","\xD0\xB3","\xD1\x88","\xD1\x89","\xD0\xB7","\xD1\x85","\n",
    "\xD1\x84","\xD1\x8B","\xD0\xB2","\xD0\xB0","\xD0\xBF","\xD1\x80","\xD0\xBE","\xD0\xBB","\xD0\xB4","\xD0\xB6","\xD1\x8D","\n",
    LV_SYMBOL_UP,"\xD1\x8F","\xD1\x87","\xD1\x81","\xD0\xBC","\xD0\xB8","\xD1\x82","\xD1\x8C","\xD0\xB1","\xD1\x8E",LV_SYMBOL_BACKSPACE,"\n",
    "1#","EN"," ",LV_SYMBOL_OK,"\n",
    ""
};

// RU верхний регистр
static const char* ru_upper_map[] = {
    "\xD0\x99","\xD0\xA6","\xD0\xA3","\xD0\x9A","\xD0\x95","\xD0\x9D","\xD0\x93","\xD0\xA8","\xD0\xA9","\xD0\x97","\xD0\xA5","\n",
    "\xD0\xA4","\xD0\xAB","\xD0\x92","\xD0\x90","\xD0\x9F","\xD0\xA0","\xD0\x9E","\xD0\x9B","\xD0\x94","\xD0\x96","\xD0\xAD","\n",
    LV_SYMBOL_UP,"\xD0\xAF","\xD0\xA7","\xD0\xA1","\xD0\x9C","\xD0\x98","\xD0\xA2","\xD0\xAC","\xD0\x91","\xD0\xAE",LV_SYMBOL_BACKSPACE,"\n",
    "1#","EN"," ",LV_SYMBOL_OK,"\n",
    ""
};

// ── Control-массивы ──
// EN: 10 + 9 + 9 + 4 = 32 кнопки
#define NR LV_BUTTONMATRIX_CTRL_NO_REPEAT
#define CK NR | LV_BUTTONMATRIX_CTRL_CHECKED
#define W2 NR | (2 << LV_BUTTONMATRIX_CTRL_WIDTH_SHIFT)
#define W6 NR | (6 << LV_BUTTONMATRIX_CTRL_WIDTH_SHIFT)

static const lv_buttonmatrix_ctrl_t en_ctrl[] = {
    NR,NR,NR,NR,NR,NR,NR,NR,NR,NR,            // row 1: 10
    NR,NR,NR,NR,NR,NR,NR,NR,NR,              // row 2: 9
    CK,NR,NR,NR,NR,NR,NR,NR,W2,             // row 3: Shift + 7 + Backspace
    CK,CK,W6,W2,                            // row 4: 1# + RU + Space + OK
};

// RU: 11 + 11 + 11 + 4 = 37 кнопок
static const lv_buttonmatrix_ctrl_t ru_ctrl[] = {
    NR,NR,NR,NR,NR,NR,NR,NR,NR,NR,NR,        // row 1: 11
    NR,NR,NR,NR,NR,NR,NR,NR,NR,NR,NR,        // row 2: 11
    CK,NR,NR,NR,NR,NR,NR,NR,NR,NR,W2,       // row 3: Shift + 9 + Backspace
    CK,CK,W6,W2,                            // row 4: 1# + EN + Space + OK
};

#undef NR
#undef CK
#undef W2
#undef W6

inline void register_maps(lv_obj_t* kb) {
    lv_keyboard_set_map(kb, LV_KEYBOARD_MODE_TEXT_LOWER, en_lower_map, en_ctrl);
    lv_keyboard_set_map(kb, LV_KEYBOARD_MODE_TEXT_UPPER, en_upper_map, en_ctrl);
    lv_keyboard_set_map(kb, LV_KEYBOARD_MODE_USER_1,    ru_lower_map,  ru_ctrl);
    lv_keyboard_set_map(kb, LV_KEYBOARD_MODE_USER_2,    ru_upper_map,  ru_ctrl);
}

} // namespace ru_keyboard
