#include "ResourceMenager.hpp"

#include <unordered_map>

#include "raylib.h"

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

void ResourceMenager::InsertTexture(Texture2D texture, const std::string name) {
    if(IsTextureReady(texture)) {
        m_TextureList.insert(std::make_pair(name, texture));
    }
}

Texture2D& ResourceMenager::GetTextureByName(const std::string name) {
    if(auto texture = m_TextureList.find(name); texture != m_TextureList.end()) {
        return texture->second;
    }
}
