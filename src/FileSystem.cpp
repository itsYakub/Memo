#include "FileSystem.hpp"

#include <fstream>
#include <filesystem>

#include "json.hpp"

#include "Debug.hpp"

FileSystem::FileSystem() : DEFAULT_FILE_PATH("data.json") {

}

const std::string& FileSystem::GetDefaultFilePath() {
    return DEFAULT_FILE_PATH;
}

bool FileSystem::DataFileExists() {
    return std::filesystem::exists(DEFAULT_FILE_PATH);
}

void FileSystem::CreateNewDataFile() {
    // This is just a double-check
    // Firstly we check if there's a file in the main.cpp
    // But if someone uses this function without checking it previously, there's another checkpoint
    if(DataFileExists()) {
        Debug::Log("The file " + DEFAULT_FILE_PATH + " exists!");

        return;
    }
    
    nlohmann::json json;

    json["player"] = {
        { "level_finish", { false, false, false } },
        { "level_best_time", { 0.0, 0.0, 0.0 } }
    };

    json["settings"] = {
        { "gameplay_display_time", true },
        { "gameplay_countdown_at_the_beginning", true },
        { "gameplay_countdown_after_pause", false },
        { "io_save_on_game_exit", true },
        { "io_save_on_level_exit", true },
        { "gameplay_deselect_time", 0.4 }
    };

    std::fstream json_output = std::fstream(DEFAULT_FILE_PATH, std::fstream::out);
    json_output << json;
    json_output.close();
}
