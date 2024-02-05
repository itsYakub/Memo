#include "Settings.hpp"

Settings::Settings() : 
// Section: Gameplay
m_GameplayDisplayTime(true), m_GameplayCountdownAtTheBeginning(true), m_GameplayCountdownAfterPause(false),
m_GameplayDeselectTime(0.4f) {

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
    }
}

void Settings::SetSettingB(SettingList setting, bool value) {
    switch(setting) {
        case GAMEPLAY_DISPLAY_TIME: m_GameplayDisplayTime = value; break;
        case GAMEPLAY_COUNTDOWN_AT_THE_BEGINNING: m_GameplayCountdownAtTheBeginning = value; break;
        case GAMEPLAY_COUNTDOWN_AFTER_PAUSE: m_GameplayCountdownAfterPause = value; break;
    }
}

void Settings::SetSettingF(SettingList setting, float value) {
    switch(setting) {
        case GAMEPLAY_DESELECT_TIME: m_GameplayDeselectTime = value; break;
    }
}

