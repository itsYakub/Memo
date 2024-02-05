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
}

void ResourceMenager::InsertTexture(const std::string path, const std::string name) {
    m_TextureList.insert(std::make_pair(name, LoadTexture(path.c_str())));
}

void ResourceMenager::InsertFont(const std::string path) {
    m_CurrentFont = LoadFontEx(path.c_str(), 16, 0, 256);
    GuiSetFont(m_CurrentFont);
    GuiSetStyle(DEFAULT, TEXT_SIZE, m_CurrentFont.baseSize);
}

Texture2D& ResourceMenager::GetTextureByName(const std::string name) {
    auto texture = m_TextureList.find(name);

    if(texture != m_TextureList.end()) {
        return texture->second;
    }
}

Font& ResourceMenager::GetCurrentFont() {
    return m_CurrentFont;
}
