#include "ResourceMenager.hpp"

#include <unordered_map>

#include "raylib.h"
#include "raygui.h"

#include "Debug.hpp"

ResourceMenager::ResourceMenager() {
    Debug::Log("Resource menager initialized successfully");
}

ResourceMenager::~ResourceMenager() {
    Debug::Log("Closing Resource menager...");

    for(auto i : m_TextureList) {
        UnloadTexture(i.second);
    }

    for(auto i : m_SoundList) {
        UnloadSound(i.second);
    }

    UnloadFont(m_CurrentFont);
}

void ResourceMenager::InsertTexture(const std::string path, const std::string name) {
    m_TextureList.insert(std::make_pair(name, LoadTexture(path.c_str())));

    IsTextureReady(GetTextureByName(name)) ? 
        Debug::Log("Texture: \"" + name + "\" from: \"" + path + "\" loaded successfully") : 
        Debug::Err("Couldn't load the texture: \"" + name + "\" from the path: \"" + path + "\"");
}

void ResourceMenager::InsertSound(const std::string path, const std::string name) {
    m_SoundList.insert(std::make_pair(name, LoadSound(path.c_str())));
    IsSoundReady(GetSoundByName(name)) ? 
        Debug::Log("Sound: \"" + name + "\" from: \"" + path + "\" loaded successfully") : 
        Debug::Err("Couldn't load the sound: \"" + name + "\" from the path: \"" + path + "\"");
}

void ResourceMenager::InsertFont(const std::string path) {
    m_CurrentFont = LoadFontEx(path.c_str(), 16, 0, 256);

    if(IsFontReady(m_CurrentFont)) {
        Debug::Log("Font: \"" + path + "\" loaded successfully");
    } else {
        Debug::Err("Couldn't load the font: \"" + path + "\"");
        return;
    }

    GuiSetFont(m_CurrentFont);
    GuiSetStyle(DEFAULT, TEXT_SIZE, m_CurrentFont.baseSize);
}

Texture2D& ResourceMenager::GetTextureByName(const std::string name) {
    auto texture = m_TextureList.find(name);

    if(texture != m_TextureList.end()) {
        return texture->second;
    }
}

Sound& ResourceMenager::GetSoundByName(const std::string name) {
    auto sound = m_SoundList.find(name);

    if(sound != m_SoundList.end()) {
        return sound->second;
    }
}


Font& ResourceMenager::GetCurrentFont() {
    return m_CurrentFont;
}

void ResourceMenager::PlaySoundByName(const std::string name) {
    PlaySound(GetSoundByName(name));
}
