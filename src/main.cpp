#include "raylib.h"

#include "Window.hpp"

#include "SceneGameplay.hpp"

class Game {
private:
    Window window = Window();
    SceneGameplay scene_gameplay = SceneGameplay();

public:
    Game() {
        scene_gameplay.Init(&window);

        while(!window.ShouldClose()) {
            Update();
            Render();
        }
    }

private:
    void Update() {
        window.Update();
        scene_gameplay.Update();
    }

    void Render() {
        window.RendererBegin();

        window.Clear(RAYWHITE);
        
        scene_gameplay.Render();

        window.RendererEnd();

        window.Draw();
    }
};

int main(int, char**) {
    Game game = Game();

    return(0);
}
