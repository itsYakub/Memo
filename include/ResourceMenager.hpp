#pragma once

#include <string>
#include <unordered_map>

#include "raylib.h"

class ResourceMenager {
private:
    std::unordered_map<std::string, Texture2D> m_TextureList;
    Font m_CurrentFont;

    ResourceMenager();
    ~ResourceMenager();
public:
    static ResourceMenager& Get() { static ResourceMenager instance; return instance; }
    
    void InsertTexture(const std::string path, const std::string name);
    void InsertFont(const std::string path);
    Texture2D& GetTextureByName(const std::string name);
    Font& GetCurrentFont();
};