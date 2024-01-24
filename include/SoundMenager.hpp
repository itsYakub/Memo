#pragma once

#include <string>
#include <unordered_map>

#include "raylib.h"

class SoundMenager {
private:
    std::unordered_map<std::string, Sound> m_SoundCache;

    SoundMenager();
    ~SoundMenager();
public:
    static SoundMenager& Get() { static SoundMenager instance; return instance; }

    void LoadSoundToCache(const std::string path, const std::string name);

    void PlaySoundFromCache(const std::string name);
};