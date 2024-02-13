#pragma once

#include <string>
#include <unordered_map>

#include "raylib.h"

class ResourceMenager {
private:
    std::unordered_map<std::string, Texture2D> m_TextureList;
    std::unordered_map<std::string, Sound> m_SoundList;

    Font m_CurrentFont;

    ResourceMenager();
    ~ResourceMenager();
public:
    static ResourceMenager& Get() { static ResourceMenager instance; return instance; }
    
    void InsertTexture(const std::string path, const std::string name);
    void InsertSound(const std::string path, const std::string name);
    void InsertFont(const std::string path);

    Texture2D& GetTextureByName(const std::string name);
    Sound& GetSoundByName(const std::string name);
    Font& GetCurrentFont();

    void PlaySoundByName(const std::string name);
};
