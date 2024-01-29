#include <memory>

#include "Window.hpp"
#include "MatchTable.hpp"

#include "Debug.hpp"

#include "SceneMenager.hpp"
#include "SceneMainMenu.hpp"

#include "SoundMenager.hpp"

#include "ResourceMenager.hpp"

class Game {
private:
    Window& window = Window::Get();
    SceneMenager& scene_menager = SceneMenager::Get();
    SoundMenager& sound_menager = SoundMenager::Get();
    ResourceMenager& resource_menager = ResourceMenager::Get();

public:
    Game() {
        Debug::Log("Game instance created successfully");

        // resource_menager.InsertTexture(LoadTexture("res/txt/table_card_back.png"), "table_card_back");
        // resource_menager.InsertTexture(LoadTexture("res/txt/table_card_front.png"), "table_card_front");

        scene_menager.LoadScene(std::make_unique<SceneMainMenu>());

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
