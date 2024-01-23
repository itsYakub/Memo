#include "Window.hpp"
#include "MatchTable.hpp"

#include "Debug.hpp"

#include "Scene.hpp"
#include "SceneMenager.hpp"
#include "SceneMainMenu.hpp"

class Game {
private:
    Window& window = Window::Get();
    SceneMenager& scene_menager = SceneMenager::Get();

public:
    Game() {
        Debug::Log("Game instance created successfully");

        scene_menager.LoadScene(new SceneMainMenu());

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
    Game game = Game();

    return(0);
}
