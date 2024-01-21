#pragma once

#include <vector>
#include <utility>

#include "MatchTableObject.hpp"
#include "Timer.hpp"

enum MatchTableDifficulty {
    DIFFICULTY_EASY = 16,
    DIFFICULTY_NORMAL = 64,
    DIFFICULTY_HARD = 256
};

class MatchTable {
private:
    std::vector<MatchTableObject> m_MatchTable;

    std::pair<int, int> m_SelectedElements;
    int m_SelectCount;

    Timer m_DeselectTimer;
    
public:
    MatchTable(const MatchTableDifficulty difficulty);
    
    inline std::vector<MatchTableObject>& GetTable() { return m_MatchTable; }
    inline std::pair<int, int>& GetSelectedPair() { return m_SelectedElements; }

    inline int GetSelectedCount() { return m_SelectCount; }
    inline void SetSelectedCount(int value) { m_SelectCount = value; }

    inline Timer& GetDeselectTimer() { return m_DeselectTimer; }
};

void MatchTableProcessInput(MatchTable& table);
