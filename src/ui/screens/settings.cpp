#include "settings.h"
#include "../screen_ids.h"
#include "../ui_screen_mgr.h"
#include "../kit/ui_kit.h"
#include "../i18n.h"

#ifdef BOARD_WIO_L1
    #include "../../mesh/mesh_task.h"
#else
    #include <nvs_param.h>
#endif

#ifdef BOARD_EPAPER
    #include <lvgl.h>
#endif

#include <stdio.h>         

#ifdef BOARD_EPAPER
    #include "board.h" 
    using namespace board; 
#endif

namespace ui::screen::settings {

using namespace ui::kit;

#ifndef BOARD_WIO_L1
static void on_language_toggle(void*) {
    i18n::Lang current = i18n::get_lang();
    i18n::Lang next = (current == i18n::Lang::EN) ? i18n::Lang::RU : i18n::Lang::EN;
    
    i18n::set_lang(next);
    nvs_param_set_u8(NVS_ID_LANGUAGE, static_cast<uint8_t>(next));
    
    Serial.printf("Language switched to: %s\n", (next == i18n::Lang::EN) ? "EN" : "RU");

    #ifdef BOARD_EPAPER
        lv_obj_invalidate(lv_scr_act());

        #ifndef MESHUI_SIM
            int w = epd_rotated_display_width();
            int h = epd_rotated_display_height();
            EpdRect rect = {0, 0, w, h};
            epd_hl_update_area(&hl, (enum EpdDrawMode)EPD_MODE_DEFAULT, 25, rect);
            Serial.println("[UI] Screen refreshed (AUTO mode)");
        #else
            // В симуляторе не делаем вызовы драйвера дисплея
            // Если нужно логирование, используй LV_LOG_INFO, но только если LV_USE_LOG=1 в lv_conf.h
            // LV_LOG_INFO("Settings screen rendered in simulator (no hardware update)\n");
        #endif
    #else
        Serial.println("[UI] Language changed (No screen refresh needed)");
    #endif
} // <-- Закрывающая скобка для on_language_toggle
#endif 

static void on_gps(void*)     { ui::screen_mgr::push(SCREEN_SET_GPS, true); }
static void on_mesh(void*)   { ui::screen_mgr::push(SCREEN_SET_MESH, true); }
static void on_display(void*){ ui::screen_mgr::push(SCREEN_SET_DISPLAY, true); }
static void on_ble(void*)    { ui::screen_mgr::push(SCREEN_SET_BLE, true); }

#ifdef BOARD_WIO_L1
static void on_battery(void*)   { ui::screen_mgr::push(SCREEN_BATTERY, true); }
static void on_provision(void*) { ui::screen_mgr::push(SCREEN_PROVISION, true); }

static Handle lbl_buzzer = nullptr;
static Handle lbl_advert = nullptr;

static void on_buzzer(void*) {
    bool en = !mesh::task::get_buzzer_enabled();
    mesh::task::set_buzzer_enabled(en);
    if (lbl_buzzer) set_text(lbl_buzzer, i18n::t(en ? i18n::T_ON : i18n::T_OFF));
}
static void on_advert(void*) {
    bool en = !mesh::task::get_advert_location();
    mesh::task::set_advert_location(en);
    if (lbl_advert) set_text(lbl_advert, i18n::t(en ? i18n::T_ON : i18n::T_OFF));
}
#endif

#ifndef BOARD_WIO_L1
static void on_storage(void*) { ui::screen_mgr::push(SCREEN_SET_STORAGE, true); }
static void on_debug(void*)   { ui::screen_mgr::push(SCREEN_SETTINGS_DEBUG, true); }
static void on_device(void*)  { ui::screen_mgr::push(SCREEN_SETTINGS_DEVICE, true); }
#endif

static void create(Handle parent) {
    Handle menu = list(parent);

#ifdef BOARD_WIO_L1
    menu_row(menu, i18n::t(i18n::T_DISPLAY),       on_display, nullptr);
    lbl_buzzer = toggle_item(menu, i18n::t(i18n::T_BUZZER),
                             i18n::t(mesh::task::get_buzzer_enabled() ? i18n::T_ON : i18n::T_OFF),
                             on_buzzer, nullptr);
    menu_row(menu, i18n::t(i18n::T_BLUETOOTH),     on_ble,     nullptr);
    menu_row(menu, i18n::t(i18n::T_GPS_SETTINGS),  on_gps,     nullptr);
    menu_row(menu, i18n::t(i18n::T_MESH_SETTINGS), on_mesh,    nullptr);
    menu_row(menu, i18n::t(i18n::T_BATTERY),       on_battery, nullptr);
    lbl_advert = toggle_item(menu, i18n::t(i18n::T_ADVERT_GPS),
                             i18n::t(mesh::task::get_advert_location() ? i18n::T_ON : i18n::T_OFF),
                             on_advert, nullptr);
    menu_row(menu, i18n::t(i18n::T_PROVISION),     on_provision, nullptr);
#else
    menu_row(menu, i18n::t(i18n::T_LANGUAGE),      on_language_toggle, nullptr);
    menu_row(menu, i18n::t(i18n::T_DISPLAY),       on_display, nullptr);
    menu_row(menu, i18n::t(i18n::T_BLUETOOTH),     on_ble,     nullptr);
    menu_row(menu, i18n::t(i18n::T_GPS_SETTINGS),  on_gps,     nullptr);
    menu_row(menu, i18n::t(i18n::T_MESH_SETTINGS), on_mesh,    nullptr);

    #ifndef MESHUI_SIM
        menu_row(menu, "Storage",       on_storage, nullptr); 
        menu_row(menu, "Debug",          on_debug,   nullptr); 
        menu_row(menu, "Device",         on_device,  nullptr);  
    #else
        // В симуляторе эти пункты скрыты. Можно раскомментировать LV_LOG_INFO, если включено логирование.
        // LV_LOG_INFO("Hiding Storage/Debug/Device menu items in simulator\n");
    #endif
#endif
}

static void entry() {}
static void exit_fn() {}
static void destroy() {
#ifdef BOARD_WIO_L1
    lbl_buzzer = nullptr; 
    lbl_advert = nullptr;
#endif
}

screen_lifecycle_t lifecycle = { create, entry, exit_fn, destroy };

} // namespace ui::screen::settings
