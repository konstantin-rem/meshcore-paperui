#include "ru_keyboard.h"

namespace ru_keyboard {

void apply_ru_lower(lv_obj_t * kb) {
    lv_keyboard_set_map(kb, LV_KEYBOARD_MODE_USER_1, kb_ru_lower_map, kb_ru_lower_ctrl);
}

void apply_ru_upper(lv_obj_t * kb) {
    lv_keyboard_set_map(kb, LV_KEYBOARD_MODE_USER_2, kb_ru_upper_map, kb_ru_upper_ctrl);
}

bool is_layout_btn(const char * txt) {
    return lv_strcmp(txt, RU_KB_BTN_LAYOUT) == 0;
}

} // namespace ru_keyboard
