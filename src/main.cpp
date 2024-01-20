#include <iostream>
#include <array>
#include <cmath>
#include <algorithm>

#include "raylib.h"

class MatchTableObject {
private:
    Vector2 m_Position;

    const static int M_WIDTH = 64;
    const static int M_HEIGHT = 96;

    bool m_IsSelected;
    bool m_IsPicked;

    int m_ID;
    int m_Index;

public:
    MatchTableObject() { };
    MatchTableObject(const MatchTableObject&) = delete;
    MatchTableObject(Vector2 position, int ID, int index);

    inline Vector2 GetPosition() { return m_Position; }

    inline int GetWidth() { return M_WIDTH; }
    inline int GetHeight() { return M_HEIGHT; }

    inline bool GetSelectState() { return m_IsSelected; }
    void Select();
    void Deselect();

    inline bool GetPickState() { return m_IsPicked; }
    void Pick();
    
    inline int GetID() { return m_ID; }
    inline int GetIndex() { return m_Index; }

    void Render();
};

MatchTableObject::MatchTableObject(Vector2 position, int ID, int index) {
    this->m_Position = position;

    this->m_IsSelected = false;
    this->m_IsPicked = false;

    this->m_ID = ID;

    this->m_Index = index;
}

void MatchTableObject::Select() {
    if(GetSelectState()) return;

    this->m_IsSelected = true;
}

void MatchTableObject::Deselect() {
    if(!GetSelectState()) return;

    this->m_IsSelected = false;
}

void MatchTableObject::Pick() {
    if(GetPickState() || !GetSelectState()) return;

    this->m_IsSelected = false;
    this->m_IsPicked = true;
}

void MatchTableObject::Render() {
    Color color_object = GREEN;
    Color color_letters = BLACK;

    if(GetPickState()) {
        color_object = Fade(GREEN, 0.5f);
        color_letters = Fade(BLACK, 0.5f);
    }

    DrawRectangle(this->m_Position.x, this->m_Position.y, MatchTableObject::M_WIDTH, MatchTableObject::M_HEIGHT, color_object);

    if(GetSelectState() || GetPickState()) {
        DrawText(TextFormat("%i", this->m_ID), this->m_Position.x, this->m_Position.y, 32, color_letters);
    }
}

int main(int, char**) {
    const int match_table_size = 16; /* The size of the table */

    SetConfigFlags(FLAG_VSYNC_HINT);
    SetTraceLogLevel(LOG_NONE);
    InitWindow(640, 480, "Raylib-5.0.0 - Match Game - v.1.0.0");

    std::array<int, match_table_size> match_table_values; /* Generating the initial values for a table */
    for(int i = 0; i < (int)match_table_values.size(); i++) {
        int random_value = 0;

        do {
            random_value = GetRandomValue(1, match_table_values.size() / 2);
        } while(std::count(match_table_values.begin(), match_table_values.end(), random_value) >= 2);

        match_table_values[i] = random_value;
    }
    
    std::array<MatchTableObject, match_table_values.size()> match_table; /* The main match table */
    for(int i = 0; i < (int) (match_table.size() / sqrt(match_table.size())); i++) {
        for(int j = 0; j < (int) (match_table.size() / sqrt(match_table.size())); j++) {
            int index = j + i * (match_table.size() / sqrt(match_table.size()));
            auto& table_object = match_table[index];

            table_object = MatchTableObject((Vector2){(float) (j * table_object.GetWidth() + 10 * j), (float) (i * table_object.GetHeight() + 10 * i)}, match_table_values[index], index);
        }
    }

    int match_table_selects_count = 0;
    std::pair<int, int> match_table_selected_index = { 0, 0 };

    while (!WindowShouldClose()) {
        
        /* Update */

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            for(auto& i : match_table) {
                if(CheckCollisionPointRec(GetMousePosition(), (Rectangle) { (float) i.GetPosition().x, (float) i.GetPosition().y, (float) i.GetWidth(), (float) i.GetHeight()})) {
                    if(i.GetSelectState()) {
                        break;
                    }

                    i.Select();
                    
                    match_table_selects_count == 0 ? match_table_selected_index.first = i.GetIndex() : match_table_selected_index.second = i.GetIndex();
                    match_table_selects_count++;
                }
            }
        }

        if(match_table_selects_count >= 2) {
            auto& match_table_first = match_table[match_table_selected_index.first];
            auto& match_table_second = match_table[match_table_selected_index.second];

            if(match_table_first.GetID() == match_table_second.GetID()) {
                match_table_first.Pick();
                match_table_second.Pick();
            }

            else {
                match_table_first.Deselect();
                match_table_second.Deselect();
            }

            match_table_selects_count = 0;
        }

        /* Render */

        BeginDrawing();

        ClearBackground(RAYWHITE);

        for(auto& i : match_table) {
            i.Render();
        }

        EndDrawing();
    }

    CloseWindow();
}
