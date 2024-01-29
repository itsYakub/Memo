#pragma once

#include <string>
#include <unordered_map>

#include "raylib.h"

class ResourceMenager {
private:
    std::unordered_map<std::string, Texture2D> m_TextureList;

    ResourceMenager();
    ~ResourceMenager();
public:
    static ResourceMenager& Get() { static ResourceMenager instance; return instance; }
    
    void InsertTexture(Texture2D texture, const std::string name);
    Texture2D& GetTextureByName(const std::string name);
};