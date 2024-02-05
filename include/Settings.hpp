#pragma once

#include <string>

enum SettingList {
    GAMEPLAY_DISPLAY_TIME,
    GAMEPLAY_COUNTDOWN_AT_THE_BEGINNING,
    GAMEPLAY_COUNTDOWN_AFTER_PAUSE,
    GAMEPLAY_DESELECT_TIME,
};

class Settings {
private:
    // Section: Gameplay
    bool m_GameplayDisplayTime; // Setting name: "GAMEPLAY_DISPLAY_TIME"
    bool m_GameplayCountdownAtTheBeginning; // Setting name: "GAMEPLAY_COUNTDOWN_AT_THE_BEGINNING"
    bool m_GameplayCountdownAfterPause; // Setting name: "GAMEPLAY_COUNTDOWN_AFTER_PAUSE"

    float m_GameplayDeselectTime; // Setting name: "GAMEPLAY_DESELECT_TIME"

    // Total list of settings:
    // 1. Gameplay:
    // > `GAMEPLAY_DISPLAY_TIME` - displaying time in the top-left corner of the screen (Default: `true`);
    // > `GAMEPLAY_COUNTDOWN_AT_THE_BEGINNING` - switches on/off the 3s time countdown at the beginnnig of the game (Default: `true`);
    // > `GAMEPLAY_COUNTDOWN_AFTER_PAUSE` - switches on/off the 3s time countdown after exiting the pause (Default: `false`);
    // > `GAMEPLAY_DESELECT_TIME` - time in which the incorretly selected cards are deselected (Default: `0.4f`);
    Settings();
public:
    static Settings& Get() { static Settings instance; return instance; }

    float& GetSettingF(SettingList setting);
    bool& GetSettingB(SettingList setting);
    
    void SetSettingF(SettingList setting, float value);
    void SetSettingB(SettingList setting, bool value);
};