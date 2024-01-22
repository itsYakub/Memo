#include "Window.hpp"
#include "MatchTable.hpp"

#include "Scene.hpp"
#include "SceneMenager.hpp"
#include "SceneGameplay.hpp"

class Game {
private:
    Window& window = Window::Get();
    SceneGameplay gameplay = SceneGameplay(DIFFICULTY_EASY);

public:
    Game() {
        SceneMenager::Get().LoadScene(&gameplay);

        while(!window.ShouldClose()) {
            Update();
            Render();
        }
    }

private:
    void Update() {
        window.Update();
        SceneMenager::Get().UpdateScene();
    }

    void Render() {
        window.RendererBegin();
        
        SceneMenager::Get().RenderScene();

        window.RendererEnd();

        window.Draw();
    }
};

int main(int, char**) {
    Game game = Game();

    return(0);
}
