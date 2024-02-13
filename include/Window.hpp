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

    Vector2 GetVirtualMousePosition();

    Vector2 GetVirtualSize();
    Vector2 GetVirtualCenter();
    
    bool ShouldClose();
    void CloseCallback();

    void SetVirtualWindowBackgroundColor(unsigned char r, unsigned char g, unsigned char b);
    
    void InitRenderBuffer();
    void CloseRenderBuffer();
    
    void Update();
    void Draw();
};
