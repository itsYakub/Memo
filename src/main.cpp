// ==============================================================================
// "Memo" version 1.0.0
// Made by: Yakub (https://github.com/itsYakub)
// ==============================================================================
// The project is licenced under the MIT Licence.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.
// ==============================================================================

#include "Window.hpp"

#include "SceneMenager.hpp"
#include "SceneSplashScreen.hpp"

#include "Settings.hpp"
#include "FileSystem.hpp"
#include "ResourceMenager.hpp"

#include "Debug.hpp"

// TODO:
// - bug-fix, code clean-up / optimizations
// - RELEASE

class Game {
private:
    Window& window = Window::Get();
    SceneMenager& scene_menager = SceneMenager::Get();
    ResourceMenager& resource_menager = ResourceMenager::Get();
    FileSystem& file_system = FileSystem::Get();

public:
    Game() {
        Debug::Log("Game instance created successfully");

        file_system.DeserializeJson();

        resource_menager.InsertFont("res/font/Peaberry-Font-v2.0/Peaberry Font Family/Peaberry Base/PeaberryBase.ttf");

        resource_menager.InsertSound("res/sfx/kenney_ui-audio/Audio/click1.ogg", "click");

        resource_menager.InsertTexture("res/txt/raylib_128x128.png", "raylib_logo");
        resource_menager.InsertTexture("res/txt/table_card_back.png", "table_card_back");
        resource_menager.InsertTexture("res/txt/table_card_front.png", "table_card_front");
        resource_menager.InsertTexture("res/txt/table_background_main.png", "background");

        scene_menager.LoadScene(new SceneSplashScreen());

        while(!window.ShouldClose()) {
            Update();
            Render();
        }

        if(Settings::Get().GetSettingB(IO_SAVE_ON_GAME_EXIT)) {
            file_system.SerializeJson();
        }

        Debug::Log("Closing game...");
    }

private:
    void Update() {
        window.Update();
        scene_menager.UpdateScene();
    }

    void Render() {
        window.InitRenderBuffer();
        
        scene_menager.RenderScene();

        window.CloseRenderBuffer();

        window.Draw();
    }
};

int main(int, char**) {
    Game game = Game();

    return(0);
}
