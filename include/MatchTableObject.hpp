#pragma once

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