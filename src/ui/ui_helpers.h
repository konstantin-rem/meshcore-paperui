#pragma once
#include "board.h" // Подключаем board.h здесь, где мы точно знаем, что BOARD_EPAPER определен

#ifdef BOARD_EPAPER
#include <epdiy.h>

// Функция-помощник: обновляет экран e-paper
inline void ui_refresh_epaper() {
    extern "C" EpdiyHighlevelState hl; // Говорим компилятору: "hl" существует где-то в проекте (в board.cpp)
    epd_hl_update(&hl);
    Serial.println("[UI] E-Paper refreshed");
}
#else
inline void ui_refresh_epaper() {
    lv_refr_exec();
}
#endif
