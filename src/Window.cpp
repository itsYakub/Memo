#include "Window.hpp"

#include "raylib.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) <( b) ? (a) : (b))

float GetBufferScaling(Window& window) {
    return MIN((float) GetScreenWidth() / window.GetRendererSize().x, (float) GetScreenHeight() / window.GetRendererSize().y);
}

Window::Window() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetConfigFlags(FLAG_VSYNC_HINT);

    SetTraceLogLevel(LOG_NONE);

    InitWindow(1024, 786, "Raylib 5.0.0 - Match Game - Version 1.0.0 ( 60FPS )");

    SetExitKey(0);

    this->m_RendererTarget = LoadRenderTexture(640, 480);

    this->m_WindowWidth = GetScreenWidth();
    this->m_WindowHeight = GetScreenHeight();

    this->m_VirtualScreenWidth = m_RendererTarget.texture.width;
    this->m_VirtualScreenHeight = m_RendererTarget.texture.height;

    this->m_VirtualMousePosition = Vector2 { 0, 0 };

}
Window::~Window() {
    UnloadRenderTexture(m_RendererTarget);
    CloseWindow();
}

void Window::WindowUpdate() {
    SetWindowTitle(TextFormat("Raylib 5.0.0 - Match Game - Version 1.0.0 ( %iFPS )", GetFPS));

    m_WindowWidth = GetScreenWidth();
    m_WindowHeight = GetScreenHeight();

    m_VirtualMousePosition.x = (GetMousePosition().x - (m_WindowWidth - (m_VirtualScreenWidth * GetBufferScaling(*this))) * 0.5f) / GetBufferScaling(*this);
    m_VirtualMousePosition.y = (GetMousePosition().y - (m_WindowHeight - (m_VirtualScreenHeight * GetBufferScaling(*this))) * 0.5f) / GetBufferScaling(*this);
}

void Window::WindowDraw() {
    BeginDrawing();
    
    ClearBackground(BLACK);

    DrawTexturePro(m_RendererTarget.texture, (Rectangle) { 0.0f, 0.0f, (float) m_VirtualScreenWidth, (float) -m_VirtualScreenHeight },
                (Rectangle) { (m_WindowWidth - ((float) m_VirtualScreenWidth * GetBufferScaling(*this))) * 0.5f, (m_WindowHeight - ((float) m_VirtualScreenHeight * GetBufferScaling(*this))) * 0.5f,
                (float) m_VirtualScreenWidth * GetBufferScaling(*this), (float) m_VirtualScreenHeight * GetBufferScaling(*this) }, (Vector2) { 0, 0 }, 0.0f, WHITE);

    EndDrawing();
}
