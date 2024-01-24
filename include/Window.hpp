#pragma once

#include "raylib.h"

class Window {
private:
    int m_WindowWidth;
    int m_WindowHeight;

    int m_VirtualScreenWidth;
    int m_VirtualScreenHeight;

    RenderTexture2D m_RendererTarget;

    Vector2 m_VirtualMousePosition;

    Color m_RendererColor;

    bool close_callback;

    Window();
    ~Window();
public:

    static Window& Get() { static Window instance; return instance; }

    inline Vector2 GetVirtualMousePosition() { return m_VirtualMousePosition; }

    inline Vector2 GetRendererSize() { return (Vector2){ (float) m_VirtualScreenWidth, (float) m_VirtualScreenHeight }; }
    inline Vector2 GetRendererCenter() { return (Vector2) { GetRendererSize().x / 2, GetRendererSize().y / 2 }; }
    
    inline bool ShouldClose() { return WindowShouldClose() || close_callback; }
    inline void CloseCallback() { close_callback = true; }

    void Update();

    inline void SetRendererBackgroundColor(unsigned char r, unsigned char g, unsigned char b) { this->m_RendererColor = Color { r, g ,b, 255 }; }
    
    inline void RendererBegin() { BeginTextureMode(m_RendererTarget); ClearBackground(m_RendererColor); }
    inline void RendererEnd() { EndTextureMode(); }
    
    void Draw();
};