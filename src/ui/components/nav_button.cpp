#include "nav_button.h"
#include "../ui_port.h"
#include "../ui_screen_mgr.h"
#include "../ui_theme.h"
#include "../../nvs_param.h"

namespace ui::nav {

static bool hit_area_debug_state = false;
static bool hit_area_debug_loaded = false;

static void ensure_hit_area_debug_loaded() {
    if (hit_area_debug_loaded) return;
    hit_area_debug_state = nvs_param_get_u8(NVS_ID_HIT_AREA_DEBUG) != 0;
    hit_area_debug_loaded = true;
}

static void style_hit_area(lv_obj_t* obj) {
    ensure_hit_area_debug_loaded();
    lv_obj_set_style_bg_opa(obj, LV_OPA_0, LV_PART_MAIN);
    if (hit_area_debug_state) {
        lv_obj_set_style_pad_all(obj, 1, LV_PART_MAIN);
        lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN);
        lv_obj_set_style_border_color(obj, lv_color_hex(EPD_COLOR_FOCUS), LV_PART_MAIN);
    } else {
        lv_obj_set_style_pad_all(obj, 0, LV_PART_MAIN);
        lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN);
    }
}

static lv_obj_t* create_hit_row(lv_obj_t* parent, lv_event_cb_t cb, void* user_data) {
    lv_obj_t* hit = lv_obj_create(parent);
    lv_obj_set_size(hit, lv_pct(100), UI_MENU_ITEM_HEIGHT);
    style_hit_area(hit);
    
    // ИСПРАВЛЕНО: вместо clear_flag
    lv_obj_set_scrollable(hit, false);
    
    // ИСПРАВЛЕНО: вместо add_flag
    lv_obj_set_clickable(hit, true);
    
    lv_obj_add_event_cb(hit, cb, LV_EVENT_CLICKED, user_data);
    lv_obj_set_ext_click_area(hit, UI_EXT_CLICK_LIST);
    ui::port::keyboard_focus_register(hit);
    return hit;
}

static lv_obj_t* create_back_hit_row(lv_obj_t* parent, lv_event_cb_t cb, void* user_data) {
    lv_obj_t* hit = lv_obj_create(parent);
    lv_obj_set_size(hit, LV_SIZE_CONTENT, UI_BACK_BTN_HEIGHT);
    style_hit_area(hit);
    
    // ИСПРАВЛЕНО
    lv_obj_set_scrollable(hit, false);
    
    if (cb) {
        // ИСПРАВЛЕНО
        lv_obj_set_clickable(hit, true);
        lv_obj_add_event_cb(hit, cb, LV_EVENT_CLICKED, user_data);
        ui::port::keyboard_focus_register(hit);
    } else {
        // ИСПРАВЛЕНО
        lv_obj_set_clickable(hit, false);
    }
    lv_obj_set_ext_click_area(hit, UI_EXT_CLICK_BACK);
    return hit;
}

static void create_back_content(lv_obj_t* parent, const char* title) {
    lv_obj_t* arrow = lv_label_create(parent);
    lv_obj_set_style_text_font(arrow, UI_FONT_NAV, LV_PART_MAIN);
    lv_obj_set_style_text_color(arrow, lv_color_hex(EPD_COLOR_TEXT), LV_PART_MAIN);
    lv_label_set_text(arrow, LV_SYMBOL_LEFT);
    // LV_OBJ_FLAG_EVENT_BUBBLE не имеет прямого сеттера, оставляем как есть — это не deprecated
    lv_obj_add_flag(arrow, LV_OBJ_FLAG_EVENT_BUBBLE);

    lv_obj_t* label = lv_label_create(parent);
    lv_obj_set_style_text_font(label, UI_FONT_NAV, LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_hex(EPD_COLOR_TEXT), LV_PART_MAIN);
    lv_label_set_text(label, title);
    lv_obj_add_flag(label, LV_OBJ_FLAG_EVENT_BUBBLE);
}

static lv_obj_t* create_nav_action_button(lv_obj_t* parent, const char* action_text,
                                          lv_event_cb_t action_cb, void* action_user_data,
                                          lv_obj_t** action_label_out) {
    lv_obj_t* action = lv_obj_create(parent);
    lv_obj_set_size(action, LV_SIZE_CONTENT, UI_ACTION_BTN_H);
    lv_obj_add_style(action, &ui::theme::style_nav_action, LV_PART_MAIN);
    
    // ИСПРАВЛЕНО
    lv_obj_set_scrollable(action, false);
    lv_obj_set_clickable(action, true);
    
    lv_obj_add_event_cb(action, action_cb, LV_EVENT_CLICKED, action_user_data);
    lv_obj_set_ext_click_area(action, UI_EXT_CLICK_ACTION);
    ui::port::keyboard_focus_register(action);

    lv_obj_t* label = lv_label_create(action);
    lv_obj_set_style_text_font(label, UI_FONT_TITLE, LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_hex(EPD_COLOR_TEXT), LV_PART_MAIN);
    lv_label_set_text(label, action_text);
    lv_obj_add_flag(label, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_center(label);

    if (action_label_out) {
        *action_label_out = label;
    }
    return action;
}

lv_obj_t* back_button(lv_obj_t* parent, const char* title, lv_event_cb_t cb) {
    ui::screen_mgr::set_nav_title(title);

    lv_obj_t* hit = create_back_hit_row(parent, cb, NULL);

    lv_obj_t* row = lv_obj_create(hit);
    lv_obj_set_size(row, LV_SIZE_CONTENT, UI_BACK_BTN_HEIGHT);
    lv_obj_align(row, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_bg_opa(row, LV_OPA_0, LV_PART_MAIN);
    lv_obj_set_style_border_width(row, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_left(row, UI_NAV_PAD_LEFT, LV_PART_MAIN);
    lv_obj_set_style_pad_right(row, UI_NAV_PAD_LEFT, LV_PART_MAIN);
    lv_obj_set_style_pad_top(row, UI_BACK_BTN_PAD_TOP, LV_PART_MAIN);
    lv_obj_set_style_pad_bottom(row, UI_BACK_BTN_PAD_BOTTOM, LV_PART_MAIN);
    lv_obj_set_style_pad_column(row, UI_BACK_BTN_COL_PAD, LV_PART_MAIN);
    
    // ИСПРАВЛЕНО: раздельные сеттеры вместо clear_flag с маской
    lv_obj_set_scrollable(row, false);
    lv_obj_set_clickable(row, false);
    
    lv_obj_add_flag(row, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_set_flex_flow(row, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(row, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    create_back_content(row, ui::screen_mgr::previous_nav_title(title));

    return hit;
}

// Остальные функции-обёртки (back_button_action_ex, back_button_actions_ex и т.д.) оставляем без изменений — они только вызывают другие функции

lv_obj_t* back_button_three_actions_ex(lv_obj_t* parent, const char* title, lv_event_cb_t back_cb,
                                       const char* first_action_text, lv_event_cb_t first_action_cb, void* first_action_user_data,
                                       const char* second_action_text, lv_event_cb_t second_action_cb, void* second_action_user_data,
                                       const char* third_action_text, lv_event_cb_t third_action_cb, void* third_action_user_data,
                                       lv_obj_t** first_action_label_out, lv_obj_t** second_action_label_out,
                                       lv_obj_t** third_action_label_out) {
    ui::screen_mgr::set_nav_title(title);

    lv_obj_t* row = create_back_hit_row(parent, NULL, NULL);
    lv_obj_set_size(row, lv_pct(UI_OUTER_WIDTH_PCT), UI_BACK_BTN_HEIGHT);
    lv_obj_set_style_bg_opa(row, LV_OPA_0, LV_PART_MAIN);
    lv_obj_set_style_border_width(row, 0, LV_PART_MAIN);
    
    // ИСПРАВЛЕНО
    lv_obj_set_scrollable(row, false);
    
    lv_obj_set_style_pad_all(row, 0, LV_PART_MAIN);

    lv_obj_t* back = lv_obj_create(row);
    lv_obj_set_size(back, LV_SIZE_CONTENT, lv_pct(100));
    lv_obj_align(back, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_bg_opa(back, LV_OPA_0, LV_PART_MAIN);
    lv_obj_set_style_border_width(back, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_left(back, UI_NAV_PAD_LEFT, LV_PART_MAIN);
    lv_obj_set_style_pad_right(back, UI_NAV_PAD_LEFT, LV_PART_MAIN);
    lv_obj_set_style_pad_top(back, UI_BACK_BTN_PAD_TOP, LV_PART_MAIN);
    lv_obj_set_style_pad_bottom(back, UI_BACK_BTN_PAD_BOTTOM, LV_PART_MAIN);
    lv_obj_set_style_pad_column(back, UI_BACK_BTN_COL_PAD, LV_PART_MAIN);
    
    // ИСПРАВЛЕНО
    lv_obj_set_scrollable(back, false);
    lv_obj_set_clickable(back, true);
    
    lv_obj_add_event_cb(back, back_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_set_ext_click_area(back, UI_EXT_CLICK_BACK);
    ui::port::keyboard_focus_register(back);
    lv_obj_set_flex_flow(back, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(back, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    create_back_content(back, ui::screen_mgr::previous_nav_title(title));

    lv_obj_t* actions = lv_obj_create(row);
    lv_obj_set_size(actions, LV_SIZE_CONTENT, lv_pct(100));
    lv_obj_align(actions, LV_ALIGN_RIGHT_MID, 0, 0);
    lv_obj_set_style_bg_opa(actions, LV_OPA_0, LV_PART_MAIN);
    lv_obj_set_style_border_width(actions, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(actions, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_top(actions, UI_BACK_BTN_PAD_TOP, LV_PART_MAIN);
    lv_obj_set_style_pad_bottom(actions, UI_BACK_BTN_PAD_BOTTOM, LV_PART_MAIN);
    lv_obj_set_style_pad_column(actions, 4, LV_PART_MAIN);
    
    // ИСПРАВЛЕНО: раздельные вызовы
    lv_obj_set_scrollable(actions, false);
    lv_obj_set_clickable(actions, false);
    
    lv_obj_set_flex_flow(actions, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(actions, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    if (first_action_text && first_action_cb) {
        create_nav_action_button(actions, first_action_text, first_action_cb, first_action_user_data,
                                 first_action_label_out);
    } else if (first_action_label_out) {
        *first_action_label_out = NULL;
    }
    if (second_action_text && second_action_cb) {
        create_nav_action_button(actions, second_action_text, second_action_cb, second_action_user_data,
                                 second_action_label_out);
    } else if (second_action_label_out) {
        *second_action_label_out = NULL;
    }
    if (third_action_text && third_action_cb) {
        create_nav_action_button(actions, third_action_text, third_action_cb, third_action_user_data,
                                 third_action_label_out);
    } else if (third_action_label_out) {
        *third_action_label_out = NULL;
    }
    return row;
}

// Функции-обёртки back_button_action и др. оставляем как были

lv_obj

