#include <memory>

#include "Window.hpp"
#include "MatchTable.hpp"

#include "Debug.hpp"

#include "SceneMenager.hpp"
#include "SceneSplashScreen.hpp"

#include "SoundMenager.hpp"

#include "ResourceMenager.hpp"

#include "Settings.hpp"

// TODO:
// - implement the basics of the IO system: saving progress, saving settings
// - build the system that makes the final game directory (official build and all the resources)
// - bug-fix, code clean-up / optimizations
// - RELEASE

class Game {
private:
    Window& window = Window::Get();
    SceneMenager& scene_menager = SceneMenager::Get();
    SoundMenager& sound_menager = SoundMenager::Get();
    ResourceMenager& resource_menager = ResourceMenager::Get();
    Settings& settings = Settings::Get();

public:
    Game() {
        Debug::Log("Game instance created successfully");

        sound_menager.LoadSoundToCache("res/sfx/kenney_ui-audio/Audio/click1.ogg", "click");

        resource_menager.InsertFont("res/font/Peaberry-Font-v2.0/Peaberry Font Family/Peaberry Base/PeaberryBase.ttf");

        resource_menager.InsertTexture("res/txt/raylib_128x128.png", "raylib_logo");
        resource_menager.InsertTexture("res/txt/table_card_back.png", "table_card_back");
        resource_menager.InsertTexture("res/txt/table_card_front.png", "table_card_front");
        resource_menager.InsertTexture("res/txt/table_background_main.png", "background");

        scene_menager.LoadScene(std::make_unique<SceneSplashScreen>());

        while(!window.ShouldClose()) {
            Update();
            Render();
        }

        Debug::Log("Closing game...");
    }

private:
    void Update() {
        window.Update();
        scene_menager.UpdateScene();
    }

    void Render() {
        window.RendererBegin();
        
        scene_menager.RenderScene();

        window.RendererEnd();

        window.Draw();
    }
};

int main(int, char**) {
    Game();

    return(0);
}
