#include "Window.hpp"

#include "raylib.h"

#include "Debug.hpp"

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) <( b) ? (a) : (b))

float GetBufferScaling(Window& window) {
    return MIN((float) GetScreenWidth() / window.GetRendererSize().x, (float) GetScreenHeight() / window.GetRendererSize().y);
}

Window::Window() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetConfigFlags(FLAG_VSYNC_HINT);

    InitWindow(1280, 960, "Raylib 5.0.0 - Match Game - Version 1.0.0");

    SetExitKey(0);

    Debug::Log("Window instance created successfully");

    this->m_RendererTarget = LoadRenderTexture(384, 284);

    this->m_WindowWidth = GetScreenWidth();
    this->m_WindowHeight = GetScreenHeight();

    this->m_VirtualScreenWidth = m_RendererTarget.texture.width;
    this->m_VirtualScreenHeight = m_RendererTarget.texture.height;

    this->m_VirtualMousePosition = Vector2 { 0, 0 };

    this->close_callback = false;
}

Window::~Window() {
    Debug::Log("Closing window...");

    UnloadRenderTexture(m_RendererTarget);
    CloseWindow();
}

void Window::Update() {
    m_WindowWidth = GetScreenWidth();
    m_WindowHeight = GetScreenHeight();

    m_VirtualMousePosition.x = (GetMousePosition().x - (m_WindowWidth - (m_VirtualScreenWidth * GetBufferScaling(*this))) * 0.5f) / GetBufferScaling(*this);
    m_VirtualMousePosition.y = (GetMousePosition().y - (m_WindowHeight - (m_VirtualScreenHeight * GetBufferScaling(*this))) * 0.5f) / GetBufferScaling(*this);

    SetMouseOffset(-(m_WindowWidth - (m_VirtualScreenWidth * GetBufferScaling(*this))) * 0.5f, -(m_WindowHeight - (m_VirtualScreenHeight * GetBufferScaling(*this))) * 0.5f);
    SetMouseScale(1 / GetBufferScaling(*this), 1 / GetBufferScaling(*this));
}

void Window::Draw() {
    BeginDrawing();
    
    ClearBackground(BLACK);

    DrawTexturePro(m_RendererTarget.texture, (Rectangle) { 0.0f, 0.0f, (float) m_VirtualScreenWidth, (float) -m_VirtualScreenHeight },
                (Rectangle) { (m_WindowWidth - ((float) m_VirtualScreenWidth * GetBufferScaling(*this))) * 0.5f, (m_WindowHeight - ((float) m_VirtualScreenHeight * GetBufferScaling(*this))) * 0.5f,
                (float) m_VirtualScreenWidth * GetBufferScaling(*this), (float) m_VirtualScreenHeight * GetBufferScaling(*this) }, (Vector2) { 0, 0 }, 0.0f, WHITE);

    EndDrawing();
}
