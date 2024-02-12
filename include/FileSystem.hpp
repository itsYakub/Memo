#pragma once

#include <string>

#include "json.hpp"

class FileSystem {
private:
    const std::string DEFAULT_FILE_PATH;

    nlohmann::json m_Json;

    FileSystem();

public:
    static FileSystem& Get() { static FileSystem instance; return instance; }

    nlohmann::json& GetJson();

    const std::string& GetDefaultFilePath();
    bool DataFileExists();

    void SerializeJson();
    void DeserializeJson();
    void CreateNewDataFile();
};