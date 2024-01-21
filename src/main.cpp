#include "raylib.h"

#include "MatchTableObject.hpp"
#include "MatchTable.hpp"

int main(int, char**) {
    SetConfigFlags(FLAG_VSYNC_HINT);
    SetTraceLogLevel(LOG_NONE);
    InitWindow(640, 640, "Raylib-5.0.0 - Match Game - v.1.0.0");
    
    MatchTable match_table(DIFFICULTY_EASY);

    while (!WindowShouldClose()) {
        
        /* Update */

        MatchTableProcessInput(match_table);

        if(IsKeyPressed(KEY_R)) {
            match_table = MatchTable(DIFFICULTY_EASY);
        }

        /* Render */

        BeginDrawing();

        ClearBackground(RAYWHITE);

        for(auto& i : match_table.GetTable()) {
            i.Render();
        }

        EndDrawing();
    }

    CloseWindow();

    return(0);
}
