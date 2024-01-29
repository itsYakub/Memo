#pragma once

#include "raylib.h"

class MatchTableObject {
private:
    Vector2 m_Position;

    bool m_IsSelected;
    bool m_IsPicked;

    int m_ID;
    int m_Index;

public:
    const static int SPACING = 1;
    const static int WIDTH = 24;
    const static int HEIGHT = 32;

    MatchTableObject(Vector2 position, int ID, int index);

    inline Vector2 GetPosition() { return m_Position; }

    inline bool GetSelectState() { return m_IsSelected; }
    void Select();
    void Deselect();

    inline bool GetPickState() { return m_IsPicked; }
    void Pick();
    
    inline int GetID() { return m_ID; }
    inline int GetIndex() { return m_Index; }

    void Render();
};