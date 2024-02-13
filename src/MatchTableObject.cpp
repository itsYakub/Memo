#include "MatchTableObject.hpp"

#include "raylib.h"

#include "Window.hpp"
#include "ResourceMenager.hpp"

#include "Debug.hpp"

MatchTableObject::MatchTableObject(Vector2 position, int ID, int index) : m_Position(position), m_IsSelected(false), m_IsPicked(false), m_ID(ID), m_Index(index) {

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

// TODO: Fix the texture rendering ASAP
void MatchTableObject::Render() {
    auto& resource = ResourceMenager::Get();

    // Default object rendering: if the object isn't selected, nor picked
    if(!GetSelectState() && !GetPickState()) {
        // Object text aligning
        int text_length_w = MeasureTextEx(resource.GetCurrentFont(), TextFormat("%c", '?'), resource.GetCurrentFont().baseSize, 1.0f).x;
        int text_length_h = MeasureTextEx(resource.GetCurrentFont(), TextFormat("%c", '?'), resource.GetCurrentFont().baseSize, 1.0f).y;

        //DrawRectangle(m_Position.x, m_Position.y, WIDTH, HEIGHT, RED);
        //DrawRectangleLines(m_Position.x, m_Position.y, WIDTH, HEIGHT, MAROON);
        DrawTexturePro(resource.GetTextureByName("table_card_back"), Rectangle { 0, 0, WIDTH, HEIGHT }, Rectangle { m_Position.x, m_Position.y, WIDTH, HEIGHT }, Vector2 { 0, 0 }, 0.0f, WHITE );
        DrawTextEx(resource.GetCurrentFont(), TextFormat("%c", '?'), Vector2 { m_Position.x + WIDTH * 0.5f - text_length_w * 0.5f, m_Position.y + HEIGHT * 0.5f - text_length_h * 0.5f }, resource.GetCurrentFont().baseSize, 1.0f, BLACK);

        // Highlight: if the mouse is hovering on the object, it get's highed
        if(CheckCollisionPointRec(GetMousePosition(), Rectangle { m_Position.x, m_Position.y, WIDTH, HEIGHT })) {
           DrawRectangleLines(m_Position.x, m_Position.y, WIDTH, HEIGHT, WHITE);
        }
    }

    // Select object rendering: if the object is selected and not rendered
    if(GetSelectState()) {
        // Object text aligning
        int text_length_w = MeasureTextEx(resource.GetCurrentFont(), TextFormat("%i", m_ID), resource.GetCurrentFont().baseSize, 2.0f).x;
        int text_length_h = MeasureTextEx(resource.GetCurrentFont(), TextFormat("%i", m_ID), resource.GetCurrentFont().baseSize, 2.0f).y;

        //DrawRectangle(m_Position.x, m_Position.y, WIDTH, HEIGHT, WHITE);
        //DrawRectangleLines(m_Position.x, m_Position.y, WIDTH, HEIGHT, LIGHTGRAY);
        DrawTexturePro(resource.GetTextureByName("table_card_front"), Rectangle { 0, 0, WIDTH, HEIGHT }, Rectangle { m_Position.x, m_Position.y, WIDTH, HEIGHT }, Vector2 { 0, 0 }, 0.0f, WHITE );
        DrawTextEx(resource.GetCurrentFont(), TextFormat("%i", m_ID), Vector2 { m_Position.x + WIDTH * 0.5f - text_length_w * 0.5f, m_Position.y + HEIGHT * 0.5f - text_length_h * 0.5f }, resource.GetCurrentFont().baseSize, 1.0f, BLACK);
    }

    // If the card is picked, it won't be rendered; it just dissapeared
}
