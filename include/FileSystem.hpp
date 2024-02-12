#pragma once

#include <string>

class FileSystem {
private:
    const std::string DEFAULT_FILE_PATH;

    FileSystem();

public:
    static FileSystem& Get() { static FileSystem instance; return instance; }

    const std::string& GetDefaultFilePath();
    bool DataFileExists();
    void CreateNewDataFile();
};