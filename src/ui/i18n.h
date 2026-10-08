#pragma once
#include <stdint.h>

// Tiny header-only i18n for meshui. Header-only (inline functions + function-
// local static tables) so it can be #included from screens shared by every
// backend without adding a .cpp to each PlatformIO env's build_src_filter.
//
// The active language lives in a single process-global (lang_ref). Persistence
// is the caller's job: read the stored byte at boot and call set_lang(); write
// it back when the user changes it (main_wio.cpp does this via InternalFS).
//
// Both backends now render UTF-8: the LVGL fonts include Latin Extended, and the
// mono e-ink backend draws node labels with the Lemon GFXfont (Latin + Cyrillic,
// U+0020–U+04FF). So Slovenian is written with proper diacritics (č/š/ž). The
// status bar still uses the ASCII 6x8 classic font, but only shows ASCII text.

namespace i18n {

enum Lang : uint8_t { EN = 0, RU = 1, LANG_COUNT };

enum Str : uint16_t {
    // home menu
    T_MESSAGES, T_TRAIL, T_STATUS, T_SETTINGS, T_TEAM,
    // status menu
    T_BATTERY, T_GPS_INFO, T_MESH_INFO,
    // settings menu
    T_DISPLAY, T_BLUETOOTH, T_GPS_SETTINGS, T_MESH_SETTINGS, T_LANGUAGE,
    T_PRIVACY, T_ADVERT_GPS, T_SOUND, T_BUZZER, T_INVERT, T_CHANNEL_ALERTS,
    // common values
    T_ON, T_OFF, T_OK, T_NONE, T_AUTO,
    // set_gps
    T_GPS, T_MODULE, T_RTC_SYNC,
    // set_mesh / mesh_info
    T_NODE, T_TX_POWER, T_GPS_SHARE, T_REPEAT, T_RADIO, T_STATS, T_PEERS,
    // gps info
    T_GPS_STATUS, T_LATITUDE, T_LONGITUDE, T_SATELLITES, T_ALTITUDE, T_SPEED,
    // battery
    T_CHARGE, T_VOLTAGE, T_CURRENT,
    // trail
    T_START, T_STOP, T_CLEAR, T_NO_GPS_TRAIL, T_STOPPED, T_WAITING_FIX,
    T_TRACKING, T_TRACKING_STARTED, T_WAITING_GPS_FIX, T_TRACKING_STOPPED,
    T_TRAIL_CLEARED,
    // chat / channels
    T_NO_MESSAGES, T_MSG_CHANNEL, T_GPS_CHANNEL, T_UNREAD,
    // quick replies
    T_REPLY, T_SENT, T_SEND_FAILED, T_NO_GPS_FIX, T_QR_GPS_LOC,
    T_QR_OMW, T_QR_YES, T_QR_NO, T_QR_HELP, T_QR_ARRIVED, T_QR_TYPE_MSG,
    // map / compass
    T_MAP, T_NO_LOCATIONS, T_MOVE_TO_CAL, T_NO_TARGET,
    // time
    T_TIMEZONE,
    // provision (settings sync)
    T_PROVISION, T_SHARE_PROFILE, T_RECEIVE_PROFILE,
    T_PROV_WAIT, T_PROV_SEARCH, T_PROV_TRANSFER, T_PROV_DONE, T_PROV_FAILED, T_PROV_SELECT,
    // self-advert (announce this node on the mesh)
    T_ADVERT_ZEROHOP, T_ADVERT_FLOOD, T_ADVERT_SENT,
    // waypoints + shared location
    T_WAYPOINTS, T_MARK_HERE, T_NO_WAYPOINTS, T_NAVIGATE, T_SEND, T_SAVE, T_DELETE,
    T_WAYPOINTS_FULL, T_WAYPOINT_MARKED, T_WAYPOINT_SENT, T_WAYPOINT_DELETED, T_SAVED_WAYPOINT,
    // language names (always shown in their own language)
    T_LANG_EN, T_LANG_SL,
    T_COUNT
};

inline Lang& lang_ref() { static Lang l = EN; return l; }
inline Lang  get_lang() { return lang_ref(); }
inline void  set_lang(Lang l) { if (l < LANG_COUNT) lang_ref() = l; }
inline void  set_lang(uint8_t l) { set_lang(l < LANG_COUNT ? (Lang)l : EN); }

inline const char* t(Str id) {
    static const char* const EN_T[T_COUNT] = {
        "Messages", "Trail", "Status", "Settings", "Team",
        "Battery", "GPS Info", "Mesh Info",
        "Display", "Bluetooth", "GPS Settings", "Mesh Settings", "Language",
        "Privacy", "GPS in advert", "Sound", "Buzzer", "Invert", "Channel alerts",
        "On", "Off", "OK", "None", "Auto",
        "GPS", "Module", "RTC Sync",
        "Node", "TX Power", "GPS Share", "Repeat", "Radio", "Stats", "Peers",
        "Status", "Latitude", "Longitude", "Satellites", "Altitude", "Speed",
        "Charge", "Voltage", "Current",
        "Start", "Stop", "Clear", "No GPS / no trail", "Stopped", "Waiting fix",
        "Tracking", "Tracking started", "Waiting for GPS fix", "Tracking stopped",
        "Trail cleared",
        "No messages yet", "Channel", "GPS Chan", "unread",
        "Reply", "Sent", "Send failed", "No GPS fix", "GPS location",
        "On my way", "Yes", "No", "Need help", "Arrived", "Type message",
        "Map", "No positions yet", "Move to calibrate", "No target",
        "Time zone",
        "Provision", "Share Profile", "Receive Profile",
        "Waiting for receiver", "Searching...", "Transferring", "Done", "Failed", "Select device",
        "Advert (direct)", "Advert (flood)", "Advert sent",
        "Waypoints", "+ Mark here", "No waypoints yet", "Navigate", "Send", "Save", "Delete",
        "Waypoints full", "Waypoint marked", "Waypoint sent", "Waypoint deleted", "Saved to waypoints",
        "English", "Slovensko",
    };
    static const char* const RU_T[T_COUNT] = {
    "Сообщения", "Трек", "Статус", "Настройки", "Команда",
    "Батарея", "Инфо GPS", "Инфо Mesh",
    "Экран", "Bluetooth", "Настройки GPS", "Настройки Mesh", "Язык",
    "Конфиденциальность", "GPS в объявлении", "Звук", "Зуммер", "Инверсия", "Оповещения канала",
    "Вкл", "Выкл", "OK", "Нет", "Авто",
    "GPS", "Модуль", "Синхр. RTC",
    "Узел", "Мощность TX", "Делиться GPS", "Повтор", "Радио", "Статистика", "Соседи",
    "Статус", "Широта", "Долгота", "Спутники", "Высота", "Скорость",
    "Заряд", "Напряжение", "Ток",
    "Старт", "Стоп", "Очистить", "Нет GPS / нет трека", "Остановлен", "Ждём фикса",
    "Отслеживание", "Отслеживание запущено", "Ждём GPS фикса", "Отслеживание остановлено",
    "Трек очищен",
    "Сообщений нет", "Канал", "GPS канал", "непрочитано",
    "Ответить", "Отправлено", "Ошибка отправки", "Нет GPS фикса", "Местоположение GPS",
    "Уже в пути", "Да", "Нет", "Нужна помощь", "Прибыл", "Введите сообщение",
    "Карта", "Позиций нет", "Двигайтесь для калибровки", "Цели нет",
    "Часовой пояс",
    "Перенос настроек", "Поделиться профилем", "Получить профиль",
    "Ждём приёмника", "Поиск...", "Передача", "Готово", "Ошибка", "Выберите устройство",
    "Объявление (прямой)", "Объявление (потоп)", "Объявление отправлено",
    "Точки", "+ Отметить здесь", "Точек нет", "Навигация", "Отправить", "Сохранить", "Удалить",
    "Точки заполнены", "Точка отмечена", "Точка отправлена", "Точка удалена", "Сохранено в точках",
    "English", "Русский",
};
    if (id >= T_COUNT) return "";
    return (lang_ref() == RU) ? RU_T[id] : EN_T[id];
}

} // namespace i18n
