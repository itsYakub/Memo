#include "SceneSplashScreen.hpp"

#include <string>
#include <cmath>

#include "Window.hpp"

#include "SceneMainMenu.hpp"
#include "SceneMenager.hpp"

#include "ResourceMenager.hpp"

SceneSplashScreen::SceneSplashScreen() : m_SplashScreenTimer(3.0f) { }

void SceneSplashScreen::Init() {
    Window::Get().SetVirtualWindowBackgroundColor(245, 245, 245);
}

void SceneSplashScreen::Destroy() {

}

void SceneSplashScreen::Update() {
    m_SplashScreenTimer.Process();

    if(m_SplashScreenTimer.Finished() || (GetKeyPressed())) {
        SceneMenager::Get().LoadScene(new SceneMainMenu());
    }
}

void SceneSplashScreen::Render() {
    auto& window = Window::Get();
    auto& resources = ResourceMenager::Get();
    
    Vector2 raylib_logo_pos = { (float) round(window.GetVirtualCenter().x - resources.GetTextureByName("raylib_logo").width / 2), (float) round(window.GetVirtualCenter().y - resources.GetTextureByName("raylib_logo").height / 2) };
    DrawTextureRec(resources.GetTextureByName("raylib_logo"), Rectangle { 0.0, 0.0, (float) resources.GetTextureByName("raylib_logo").width, (float) resources.GetTextureByName("raylib_logo").height}, raylib_logo_pos, WHITE);

    std::string splashscreen_text_1 = "Powered by...";
    std::string splashscreen_text_2 = "A simple and easy-to-use library\nto enjoy videogames programming.";
    std::string splashscreen_text_3 = "Press any key to continue...";

    int text_one_pos_x = window.GetVirtualCenter().x - MeasureTextEx(GetFontDefault(), splashscreen_text_1.c_str(), 10, 1).x * 0.5f;
    int text_one_pos_y = window.GetVirtualCenter().y - MeasureTextEx(GetFontDefault(), splashscreen_text_1.c_str(), 10, 1).y * 0.5f - 80;

    int text_two_pos_x = window.GetVirtualCenter().x - MeasureTextEx(GetFontDefault(), splashscreen_text_2.c_str(), 10, 1).x * 0.5f;
    int text_two_pos_y = window.GetVirtualCenter().y - MeasureTextEx(GetFontDefault(), splashscreen_text_2.c_str(), 10, 1).y * 0.5f + 90;
    
    DrawText(splashscreen_text_1.c_str(), text_one_pos_x, text_one_pos_y, 10, BLACK);
    DrawText(splashscreen_text_2.c_str(), text_two_pos_x, text_two_pos_y, 10, BLACK);
    DrawText(splashscreen_text_3.c_str(), 0, 0, 2, LIGHTGRAY);
}
