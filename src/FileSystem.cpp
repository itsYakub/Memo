#include "FileSystem.hpp"

#include <fstream>
#include <filesystem>

#include "json.hpp"

#include "Debug.hpp"

FileSystem::FileSystem() : DEFAULT_FILE_PATH("data.json") {

}

nlohmann::json& FileSystem::GetJson() {
    return m_Json;
}


const std::string& FileSystem::GetDefaultFilePath() {
    return DEFAULT_FILE_PATH;
}

bool FileSystem::DataFileExists() {
    return std::filesystem::exists(DEFAULT_FILE_PATH);
}

void FileSystem::SerializeJson() {
    std::ofstream json_output(DEFAULT_FILE_PATH);
    json_output << m_Json << std::endl;
    json_output.close();
}

void FileSystem::DeserializeJson() {
    if(!DataFileExists()) {
        CreateNewDataFile();

        return;
    }

    std::ifstream json_input(DEFAULT_FILE_PATH);
    m_Json = nlohmann::json::parse(json_input);
    json_input.close();
}

void FileSystem::CreateNewDataFile() {
    if(DataFileExists()) {
        Debug::Log("The file " + DEFAULT_FILE_PATH + " exists!");

        return;
    }

    m_Json["player"] = {
        { "level_finish", { false, false, false } },
        { "level_best_time", { 0.0, 0.0, 0.0 } }
    };

    m_Json["settings"] = {
        { "gameplay_display_time", true },
        { "gameplay_countdown_at_the_beginning", true },
        { "gameplay_countdown_after_pause", false },
        { "io_save_on_game_exit", true },
        { "io_save_on_level_exit", true },
        { "gameplay_deselect_time", 0.4 }
    };

    std::fstream json_output = std::fstream(DEFAULT_FILE_PATH, std::fstream::out);
    json_output << m_Json;
    json_output.close();
}
