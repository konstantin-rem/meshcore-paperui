#pragma once
#include "lvgl.h"

// Кнопки управления (совпадают с дефолтными LVGL)
#define RU_KB_BTN_SPECIAL "\xC2\xA0"  // неразрывный пробел — невидимая кнопка
#define RU_KB_BTN_NEWLINE LV_SYMBOL_NEW_LINE
#define RU_KB_BTN_BACKSPACE LV_SYMBOL_BACKSPACE
#define RU_KB_BTN_OK LV_SYMBOL_OK
#define RU_KB_BTN_SHIFT LV_SYMBOL_UP
#define RU_KB_BTN_LAYOUT "EN"
#define RU_KB_BTN_NUM "123"

// === Строчная кириллица ===
static const char * kb_ru_lower_map[] = {
    "й", "ц", "у", "к", "е", "н", "г", "ш", "щ", "з", "х", "\n",
    "ф", "ы", "в", "а", "п", "р", "о", "л", "д", "ж", "э", "\n",
    RU_KB_BTN_SHIFT, "я", "ч", "с", "м", "и", "т", "ь", "б", "ю", RU_KB_BTN_BACKSPACE, "\n",
    RU_KB_BTN_NUM, RU_KB_BTN_LAYOUT, " ", RU_KB_BTN_OK, "\n",
    ""
};

// === Заглавная кириллица ===
static const char * kb_ru_upper_map[] = {
    "Й", "Ц", "У", "К", "Е", "Н", "Г", "Ш", "Щ", "З", "Х", "\n",
    "Ф", "Ы", "В", "А", "П", "Р", "О", "Л", "Д", "Ж", "Э", "\n",
    RU_KB_BTN_SHIFT, "Я", "Ч", "С", "М", "И", "Т", "Ь", "Б", "Ю", RU_KB_BTN_BACKSPACE, "\n",
    RU_KB_BTN_NUM, RU_KB_BTN_LAYOUT, " ", RU_KB_BTN_OK, "\n",
    ""
};

// === Control-мапы (флаги кнопок) ===
// LV_BTNMATRIX_CTRL_NO_REPEAT — без повтора при удержании
// LV_BTNMATRIX_CTRL_POPOVER — поповер при нажатии (опционально)
// LV_BTNMATRIX_CTRL_CHECKED — переключатель (Shift)

// 12 + 11 + 11 + 4 = 38 кнопок в строчной мапе
static const lv_btnmatrix_ctrl_t kb_ru_lower_ctrl[] = {
    LV_BTNMATRIX_CTRL_NO_REPEAT, LV_BTNMATRIX_CTRL_NO_REPEAT, LV_BTNMATRIX_CTRL_NO_REPEAT,
    LV_BTNMATRIX_CTRL_NO_REPEAT, LV_BTNMATRIX_CTRL_NO_REPEAT, LV_BTNMATRIX_CTRL_NO_REPEAT,
    LV_BTNMATRIX_CTRL_NO_REPEAT, LV_BTNMATRIX_CTRL_NO_REPEAT, LV_BTNMATRIX_CTRL_NO_REPEAT,
    LV_BTNMATRIX_CTRL_NO_REPEAT, LV_BTNMATRIX_CTRL_NO_REPEAT,
    // 2-я строка
    LV_BTNMATRIX_CTRL_NO_REPEAT, LV_BTNMATRIX_CTRL_NO_REPEAT, LV_BTNMATRIX_CTRL_NO_REPEAT,
    LV_BTNMATRIX_CTRL_NO_REPEAT, LV_BTNMATRIX_CTRL_NO_REPEAT, LV_BTNMATRIX_CTRL_NO_REPEAT,
    LV_BTNMATRIX_CTRL_NO_REPEAT, LV_BTNMATRIX_CTRL_NO_REPEAT, LV_BTNMATRIX_CTRL_NO_REPEAT,
    LV_BTNMATRIX_CTRL_NO_REPEAT, LV_BTNMATRIX_CTRL_NO_REPEAT,
    // 3-я строка
    LV_BTNMATRIX_CTRL_CHECKED | LV_BTNMATRIX_CTRL_NO_REPEAT,  // Shift
    LV_BTNMATRIX_CTRL_NO_REPEAT, LV_BTNMATRIX_CTRL_NO_REPEAT, LV_BTNMATRIX_CTRL_NO_REPEAT,
    LV_BTNMATRIX_CTRL_NO_REPEAT, LV_BTNMATRIX_CTRL_NO_REPEAT, LV_BTNMATRIX_CTRL_NO_REPEAT,
    LV_BTNMATRIX_CTRL_NO_REPEAT, LV_BTNMATRIX_CTRL_NO_REPEAT, LV_BTNMATRIX_CTRL_NO_REPEAT,
    LV_BTNMATRIX_CTRL_NO_REPEAT | 2,  // Backspace (ширина 2)
    // 4-я строка
    LV_BTNMATRIX_CTRL_CHECKED | LV_BTNMATRIX_CTRL_NO_REPEAT,  // 123
    LV_BTNMATRIX_CTRL_CHECKED | LV_BTNMATRIX_CTRL_NO_REPEAT,  // EN/RU
    7,                                                          // Space (ширина 7)
    LV_BTNMATRIX_CTRL_NO_REPEAT | 2,                            // OK (ширина 2)
};

// Тот же массив control-флагов подходит и для заглавной мапы (кол-во кнопок совпадает)
static const lv_btnmatrix_ctrl_t kb_ru_upper_ctrl[] = {
    LV_BTNMATRIX_CTRL_NO_REPEAT, LV_BTNMATRIX_CTRL_NO_REPEAT, LV_BTNMATRIX_CTRL_NO_REPEAT,
    LV_BTNMATRIX_CTRL_NO_REPEAT, LV_BTNMATRIX_CTRL_NO_REPEAT, LV_BTNMATRIX_CTRL_NO_REPEAT,
    LV_BTNMATRIX_CTRL_NO_REPEAT, LV_BTNMATRIX_CTRL_NO_REPEAT, LV_BTNMATRIX_CTRL_NO_REPEAT,
    LV_BTNMATRIX_CTRL_NO_REPEAT, LV_BTNMATRIX_CTRL_NO_REPEAT,
    LV_BTNMATRIX_CTRL_NO_REPEAT, LV_BTNMATRIX_CTRL_NO_REPEAT, LV_BTNMATRIX_CTRL_NO_REPEAT,
    LV_BTNMATRIX_CTRL_NO_REPEAT, LV_BTNMATRIX_CTRL_NO_REPEAT, LV_BTNMATRIX_CTRL_NO_REPEAT,
    LV_BTNMATRIX_CTRL_NO_REPEAT, LV_BTNMATRIX_CTRL_NO_REPEAT, LV_BTNMATRIX_CTRL_NO_REPEAT,
    LV_BTNMATRIX_CTRL_NO_REPEAT, LV_BTNMATRIX_CTRL_NO_REPEAT,
    LV_BTNMATRIX_CTRL_CHECKED | LV_BTNMATRIX_CTRL_NO_REPEAT,
    LV_BTNMATRIX_CTRL_NO_REPEAT, LV_BTNMATRIX_CTRL_NO_REPEAT, LV_BTNMATRIX_CTRL_NO_REPEAT,
    LV_BTNMATRIX_CTRL_NO_REPEAT, LV_BTNMATRIX_CTRL_NO_REPEAT, LV_BTNMATRIX_CTRL_NO_REPEAT,
    LV_BTNMATRIX_CTRL_NO_REPEAT, LV_BTNMATRIX_CTRL_NO_REPEAT, LV_BTNMATRIX_CTRL_NO_REPEAT,
    LV_BTNMATRIX_CTRL_NO_REPEAT | 2,
    LV_BTNMATRIX_CTRL_CHECKED | LV_BTNMATRIX_CTRL_NO_REPEAT,
    LV_BTNMATRIX_CTRL_CHECKED | LV_BTNMATRIX_CTRL_NO_REPEAT,
    7,
    LV_BTNMATRIX_CTRL_NO_REPEAT | 2,
};

namespace ru_keyboard {
    void apply_ru_lower(lv_obj_t * kb);
    void apply_ru_upper(lv_obj_t * kb);
    bool is_layout_btn(const char * txt);
}
