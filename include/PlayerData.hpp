#pragma once

#include <array>

class PlayerData {
private:
    std::array<bool, 3> m_LevelComplete;
    std::array<float, 3> m_LevelTopTime;

    PlayerData() { }

public:
    static PlayerData& Get() { static PlayerData instance; return instance; }

    inline bool GetCompleteState(int index) { return m_LevelComplete.at(index); }
    inline void SetCompleteState(int index, bool state) { m_LevelComplete.at(index) = state; }

    inline float GetCompleteTime(int index) { return m_LevelTopTime.at(index); }
    inline void SetCompleteTime(int index, float time) { m_LevelTopTime.at(index) = time; }
};