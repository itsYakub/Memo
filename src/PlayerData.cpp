#include "PlayerData.hpp"

#include <fstream>

#include "json.hpp"

#include "FileSystem.hpp"
#include "Debug.hpp"

PlayerData::PlayerData() {
    DeserializePlayerData();
}

PlayerData::~PlayerData() {
    SerializePlayerData();
}

bool PlayerData::GetCompleteState(int index) { return m_LevelCompleteState.at(index).first; }
void PlayerData::SetCompleteState(int index, bool state) { m_LevelCompleteState.at(index).first = state; }

float PlayerData::GetCompleteTime(int index) { return m_LevelCompleteState.at(index).second; }
void PlayerData::SetCompleteTime(int index, float time) { m_LevelCompleteState.at(index).second = time; }

void PlayerData::SerializePlayerData() {
    if(!FileSystem::Get().DataFileExists()) {
        return;
    }

    std::ifstream json_input("data.json");
    nlohmann::json json = nlohmann::json::parse(json_input);
    json_input.close();

    for(int i = 0; i < (int) m_LevelCompleteState.size(); i++) {
        json["player"]["level_finish"][i] = m_LevelCompleteState.at(i).first;
        json["player"]["level_best_time"][i] = m_LevelCompleteState.at(i).second;
    }

    std::ofstream json_output("data.json");
    json_output << json << std::endl;
    json_output.close();

    Debug::Log("Player data serialized successfully!");
}

void PlayerData::DeserializePlayerData() {
    if(!FileSystem::Get().DataFileExists()) {
        return;
    }

    std::ifstream json_input("data.json");
    nlohmann::json json = nlohmann::json::parse(json_input);

    for(int i = 0; i < (int) m_LevelCompleteState.size(); i++) {
        m_LevelCompleteState.at(i).first = json["player"]["level_finish"][i];
        m_LevelCompleteState.at(i).second = json["player"]["level_best_time"][i];
    }

    json_input.close();

    Debug::Log("Player data deserialized successfully!");
}
