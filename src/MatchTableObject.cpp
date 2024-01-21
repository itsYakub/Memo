#include "MatchTableObject.hpp"
#include "raylib.h"

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
