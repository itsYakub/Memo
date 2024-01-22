#include "raylib.h"

#include "MatchTableObject.hpp"
#include "MatchTable.hpp"
#include "Window.hpp"

int main(int, char**) {
    Window window = Window();
    MatchTable match_table = MatchTable(DIFFICULTY_EASY);

    while (!WindowShouldClose()) {
        
        /* Update */

        window.WindowUpdate();
        MatchTableProcessInput(match_table, window.GetVirtualMousePosition());

        if(IsKeyPressed(KEY_R)) {
            match_table = MatchTable(DIFFICULTY_EASY);
        }

        /* Render */

        window.RendererBegin();

        ClearBackground(RAYWHITE);

        for(auto& i : match_table.GetTable()) {
            i.Render();
        }

        window.RendererEnd();
        
        window.WindowDraw();
    }

    return(0);
}
