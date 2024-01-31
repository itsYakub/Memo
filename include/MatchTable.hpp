#pragma once

#include <vector>
#include <utility>
#include <cmath>

#include "raylib.h"

#include "MatchTableObject.hpp"
#include "Timer.hpp"

enum MatchTableDifficulty {
    DIFFICULTY_EASY = 16,
    DIFFICULTY_NORMAL = 36,
    DIFFICULTY_HARD = 64
};

class MatchTable {
private:
    std::vector<MatchTableObject> m_MatchTable;

    MatchTableDifficulty m_Difficulty;

    std::pair<int, int> m_SelectedElements;
    int m_SelectCount;

    const float DESELECT_TIME = 0.25f;
    Timer m_DeselectTimer;
    
public:
    MatchTable() = delete;
    MatchTable(const MatchTableDifficulty difficulty);

    void Update();

    inline MatchTableDifficulty GetDifficulty() { return m_Difficulty; }
    inline int GetDifficultyValue() { return m_Difficulty; }

    inline std::vector<MatchTableObject>& GetTable() { return m_MatchTable; }

    bool GetCompleteState();

    inline std::pair<int, int>& GetSelectedPair() { return m_SelectedElements; }
    inline int GetSelectedCount() { return m_SelectCount; }
    inline void SetSelectedCount(int value) { m_SelectCount = value; }

    inline Timer& GetDeselectTimer() { return m_DeselectTimer; }

    inline Vector2 GetTableArea() { return { ((float) sqrt(m_Difficulty) * MatchTableObject::WIDTH) + ((float) (sqrt(m_Difficulty) - 1) * 10), ((float) sqrt(m_Difficulty) * MatchTableObject::HEIGHT) + ((float) (sqrt(m_Difficulty) - 1) * 10) }; }

    void ProcessInput();
    void CheckTableState();
};
