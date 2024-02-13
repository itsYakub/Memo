#include "Window.hpp"

#include "raylib.h"
#include "raygui.h"

#include "Debug.hpp"

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) <( b) ? (a) : (b))

float GetBufferScaling(Window& window) {
    return MIN((float) GetScreenWidth() / window.GetVirtualSize().x, (float) GetScreenHeight() / window.GetVirtualSize().y);
}

Window::Window() {
    SetTraceLogLevel(LOG_NONE);

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetConfigFlags(FLAG_VSYNC_HINT);

    InitWindow(1280, 960, TextFormat("Raylib %s - Memo - Version 1.0.0", RAYLIB_VERSION));
    InitAudioDevice();

    SetExitKey(0);

    GuiLoadStyleDefault();
    GuiLoadIcons("res/rguiicons/icon_set.rgi", true);

    MaximizeWindow();

    Debug::Log("Window instance created successfully");

    this->m_RendererTarget = LoadRenderTexture(400, 296); 

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

    CloseAudioDevice();
    CloseWindow();
}

Vector2 Window::GetVirtualMousePosition() {
    return m_VirtualMousePosition;
}

Vector2 Window::GetVirtualSize() {
     return (Vector2) { m_VirtualScreenWidth, m_VirtualScreenHeight }; 
}

Vector2 Window::GetVirtualCenter() {
     return (Vector2) { m_VirtualScreenWidth / 2, m_VirtualScreenHeight / 2 }; 
}

bool Window::ShouldClose() {
     return WindowShouldClose() || close_callback; 
}

void Window::CloseCallback() {
     close_callback = true; 
}

void Window::SetVirtualWindowBackgroundColor(unsigned char r, unsigned char g, unsigned char b) {
     this->m_RendererColor = Color { r, g ,b, 255 }; 
}

void Window::InitRenderBuffer() {
    BeginTextureMode(m_RendererTarget); 
    ClearBackground(m_RendererColor); 
}

void Window::CloseRenderBuffer() {
     EndTextureMode(); 
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
