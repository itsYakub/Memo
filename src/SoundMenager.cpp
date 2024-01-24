#include "SoundMenager.hpp"

#include "raylib.h"

#include "Debug.hpp"

SoundMenager::SoundMenager() {
    InitAudioDevice();

    Debug::Log("Sound Menager loaded successfully");
}

SoundMenager::~SoundMenager() {
    Debug::Log("Closing Sound Menager...");

    for(auto i : m_SoundCache) {
        UnloadSound(i.second);
    }

    CloseAudioDevice();
}

void SoundMenager::LoadSoundToCache(const std::string path, const std::string name) {
    m_SoundCache.insert(std::make_pair(name, LoadSound(path.c_str())));
    Debug::Log("Sound: \"" + name + "\" from: \"" + path + "\" loaded successfully");
}

void SoundMenager::PlaySoundFromCache(const std::string name) {
    if(auto sound = m_SoundCache.find(name); sound != m_SoundCache.end()) {
        PlaySound(sound->second);
    }
} 

