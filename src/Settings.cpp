#include "Settings.hpp"

Settings::Settings() : 
// Section: Gameplay
m_GameplayDisplayTime(true), m_GameplayCountdownAtTheBeginning(true), m_GameplayCountdownAfterPause(false),
m_GameplayDeselectTime(0.4f),
// Section: IO
m_IOSaveOnGameExit(false), m_IOSaveOnLevelExit(true) {

}

float& Settings::GetSettingF(SettingList setting) {
    switch(setting) {
        case GAMEPLAY_DESELECT_TIME: return m_GameplayDeselectTime;
    }
}

bool& Settings::GetSettingB(SettingList setting) {
    switch(setting) {
        case GAMEPLAY_DISPLAY_TIME: return m_GameplayDisplayTime;
        case GAMEPLAY_COUNTDOWN_AT_THE_BEGINNING: return m_GameplayCountdownAtTheBeginning;
        case GAMEPLAY_COUNTDOWN_AFTER_PAUSE: return m_GameplayCountdownAfterPause;
        case IO_SAVE_ON_GAME_EXIT: return m_IOSaveOnGameExit;
        case IO_SAVE_ON_LEVEL_EXIT: return m_IOSaveOnLevelExit;
    }
}

void Settings::SetSettingB(SettingList setting, bool value) {
    switch(setting) {
        case GAMEPLAY_DISPLAY_TIME: m_GameplayDisplayTime = value; break;
        case GAMEPLAY_COUNTDOWN_AT_THE_BEGINNING: m_GameplayCountdownAtTheBeginning = value; break;
        case GAMEPLAY_COUNTDOWN_AFTER_PAUSE: m_GameplayCountdownAfterPause = value; break;
        case IO_SAVE_ON_GAME_EXIT: m_IOSaveOnGameExit = value; break;
        case IO_SAVE_ON_LEVEL_EXIT: m_IOSaveOnLevelExit = value; break;
    }
}

void Settings::SetSettingF(SettingList setting, float value) {
    switch(setting) {
        case GAMEPLAY_DESELECT_TIME: m_GameplayDeselectTime = value; break;
    }
}

