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

#include <memory>

#include "Window.hpp"
#include "MatchTable.hpp"

#include "Debug.hpp"

#include "SceneMenager.hpp"
#include "SceneSplashScreen.hpp"

#include "SoundMenager.hpp"

#include "ResourceMenager.hpp"

#include "Settings.hpp"

#include "FileSystem.hpp"

#include "PlayerData.hpp"

// TODO:
// - implement the basics of the IO system: saving progress, saving settings
// - bug-fix, code clean-up / optimizations
// - RELEASE

// I have a stupid idea in which I would completely ditch the "PlayerData" class and just use "FileSystem"
// It would require me to build a getter and setter for the json object in the FileSystem class
// and then to access them from the respected functions.
// Probably at the game's launch I'd automatically deserialize the data file to the json object and then serialize it when needed. 

class Game {
private:
    Window& window = Window::Get();
    SceneMenager& scene_menager = SceneMenager::Get();
    SoundMenager& sound_menager = SoundMenager::Get();
    ResourceMenager& resource_menager = ResourceMenager::Get();
    FileSystem& file_system = FileSystem::Get();

public:
    Game() {
        Debug::Log("Game instance created successfully");

        if(!file_system.DataFileExists()) file_system.CreateNewDataFile();

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
