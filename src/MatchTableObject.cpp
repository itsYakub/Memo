#include "MatchTableObject.hpp"

#include "raylib.h"

#include "Window.hpp"
#include "Debug.hpp"

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
    if(!GetSelectState() && !GetPickState()) {
        int text_length_w = MeasureTextEx(GetFontDefault(), TextFormat("%c", '?'), GetFontDefault().baseSize, 2.0f).x;
        int text_length_h = MeasureTextEx(GetFontDefault(), TextFormat("%c", '?'), GetFontDefault().baseSize, 2.0f).y;

        DrawRectangle(m_Position.x, m_Position.y, WIDTH, HEIGHT, RED);
        DrawRectangleLines(m_Position.x, m_Position.y, WIDTH, HEIGHT, MAROON);
        DrawText(TextFormat("%c", '?'), m_Position.x + WIDTH * 0.5f - text_length_w * 0.5f, m_Position.y + HEIGHT * 0.5f - text_length_h * 0.5f, GetFontDefault().baseSize, BLACK);
    }

    if(GetSelectState()) {
        int text_length_w = MeasureTextEx(GetFontDefault(), TextFormat("%i", m_ID), GetFontDefault().baseSize, 2.0f).x;
        int text_length_h = MeasureTextEx(GetFontDefault(), TextFormat("%i", m_ID), GetFontDefault().baseSize, 2.0f).y;

        DrawRectangleLines(m_Position.x, m_Position.y, WIDTH, HEIGHT, LIGHTGRAY);
        DrawText(TextFormat("%i", m_ID), m_Position.x + WIDTH * 0.5f - text_length_w * 0.5f, m_Position.y + HEIGHT * 0.5f - text_length_h * 0.5f, GetFontDefault().baseSize, BLACK);
    }
}

void MatchTableObject::Unload() {

}