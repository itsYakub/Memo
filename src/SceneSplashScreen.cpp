#include "SceneSplashScreen.hpp"

#include <memory>
#include <string>

#include "Window.hpp"
#include "SceneMainMenu.hpp"
#include "SceneMenager.hpp"

SceneSplashScreen::SceneSplashScreen() : m_SplashScreenTimer(5.0f) { }

void SceneSplashScreen::Init() {
    Window::Get().SetRendererBackgroundColor(235, 235, 235);
}

void SceneSplashScreen::Destroy() {

}

void SceneSplashScreen::Update() {
    m_SplashScreenTimer.Process();

    if(m_SplashScreenTimer.Finished()) {
        SceneMenager::Get().LoadScene(std::make_unique<SceneMainMenu>());
    }
}

void SceneSplashScreen::Render() {
    auto& window = Window::Get();

    // I've copied it straight from the examples...
    DrawRectangle(window.GetRendererSize().x / 2 - 64, window.GetRendererSize().y / 2 - 64, 128, 128, BLACK);
    DrawRectangle(window.GetRendererSize().x  / 2 - 56, window.GetRendererSize().y/ 2 - 56, 112, 112, RAYWHITE);
    DrawText("raylib", window.GetRendererSize().x  / 2 - 22, window.GetRendererSize().y / 2 + 24, 25, BLACK);

    std::string spashscreen_text_1 = "Powered by...";
    std::string spashscreen_text_2 = "A simple and easy-to-use library\nto enjoy videogames programming.";

    int text_one_pos_x = window.GetRendererCenter().x - MeasureTextEx(GetFontDefault(), spashscreen_text_1.c_str(), 10, 1).x * 0.5f;
    int text_one_pos_y = window.GetRendererCenter().y - MeasureTextEx(GetFontDefault(), spashscreen_text_1.c_str(), 10, 1).y * 0.5f - 80;

    int text_two_pos_x = window.GetRendererCenter().x - MeasureTextEx(GetFontDefault(), spashscreen_text_2.c_str(), 10, 1).x * 0.5f;
    int text_two_pos_y = window.GetRendererCenter().y - MeasureTextEx(GetFontDefault(), spashscreen_text_2.c_str(), 10, 1).y * 0.5f + 90;
    
    DrawText(spashscreen_text_1.c_str(), text_one_pos_x, text_one_pos_y, 10, BLACK);
    DrawText(spashscreen_text_2.c_str(), text_two_pos_x, text_two_pos_y, 10, BLACK);
}
