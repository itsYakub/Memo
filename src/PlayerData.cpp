#include "PlayerData.hpp"

PlayerData::PlayerData() : m_LevelCompleteState() {
    for(auto i : m_LevelCompleteState) {
        i.first = false;
        i.second = 0.0f;
    }
}

bool PlayerData::GetCompleteState(int index) { return m_LevelCompleteState.at(index).first; }
void PlayerData::SetCompleteState(int index, bool state) { m_LevelCompleteState.at(index).first = state; }

float PlayerData::GetCompleteTime(int index) { return m_LevelCompleteState.at(index).second; }
void PlayerData::SetCompleteTime(int index, float time) { m_LevelCompleteState.at(index).second = time; }

void PlayerData::SerializeData() {
    // TODO: implement file serialization
    // Maybe some JSON work, or TXT. For sure you need to implement some sort of good file streaming
    // Maybe try this project: https://github.com/nlohmann/json
}

void PlayerData::DeserializeData() {
    // TODO: implement file deserialization
}
