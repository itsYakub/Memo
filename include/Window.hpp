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
public:
    Window();
    ~Window();
    
    inline Vector2 GetVirtualMousePosition() { return m_VirtualMousePosition; }

    inline Vector2 GetWindowSize() { return (Vector2){ (float) m_WindowWidth, (float) m_WindowHeight }; }
    inline Vector2 GetRendererSize() { return (Vector2){ (float) m_VirtualScreenWidth, (float) m_VirtualScreenHeight }; }

    void WindowUpdate();
    
    inline void RendererBegin() { BeginTextureMode(m_RendererTarget); }
    inline void RendererEnd() { EndTextureMode(); }
    
    void WindowDraw();
};