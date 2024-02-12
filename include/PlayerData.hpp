#pragma once

#include <array>
#include <utility>

class PlayerData {
private:
    // - First element of the `m_LevelCompleteState` stands for the complete state of the level
    // - Second element of the `m_LevelCompleteState` stands for the best time the player has gotten
    std::array<std::pair<bool, float>, 3> m_LevelCompleteState; 

    PlayerData();
    ~PlayerData();

public:
    static PlayerData& Get() { static PlayerData instance; return instance; }

    bool GetCompleteState(int index);
    void SetCompleteState(int index, bool state);

    float GetCompleteTime(int index);
    void SetCompleteTime(int index, float time);

    void SerializePlayerData(); // In other words: save the player's data to the save file
    void DeserializePlayerData(); // In other words: load the player's data from the save file
};