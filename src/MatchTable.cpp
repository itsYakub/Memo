#include "MatchTable.hpp"

#include <vector>
#include <cmath>
#include <algorithm>

#include "MatchTableObject.hpp"
#include "Timer.hpp"
#include "Debug.hpp"

MatchTable::MatchTable(const MatchTableDifficulty difficulty) {
    this->m_MatchTable = std::vector<MatchTableObject>(difficulty);
    this->m_SelectedElements = std::pair<int, int>(0, 0);
    this->m_SelectCount = 0;
    this->m_DeselectTimer = Timer(0.5f);

    std::vector<int> values = std::vector<int>(difficulty); 
    for(int i = 0; i < (int) sqrt(difficulty); i++) {
        for(int j = 0; j < (int) sqrt(difficulty); j++) {
            int index = j + i * sqrt(difficulty);
            int random_value = 0;

            do {
                random_value = GetRandomValue(1, (int) m_MatchTable.size() / 2);
            } while(std::count(values.begin(), values.end(), random_value) >= 2);

            values[index] = random_value;
            m_MatchTable[index] = MatchTableObject((Vector2){(float) (j * m_MatchTable[index].GetWidth() + 10 * j), (float) (i * m_MatchTable[index].GetHeight() + 10 * i)}, random_value, index);
        }
    }

    Debug::Log("Match table created successfully");
}

void MatchTable::MatchTableProcessInput() {
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && m_SelectCount < 2) {
        for(auto& i : m_MatchTable) {
            if(CheckCollisionPointRec(GetMousePosition(), (Rectangle) { (float) i.GetPosition().x, (float) i.GetPosition().y, (float) i.GetWidth(), (float) i.GetHeight()})) {
                if(i.GetPickState()) {
                    break;
                }

                else if(i.GetSelectState()) {
                    i.Deselect();

                    m_SelectCount--;

                    break;
                }

                i.Select();
                
                m_SelectCount == 0 ? m_SelectedElements.first = i.GetIndex() : m_SelectedElements.second = i.GetIndex();
                m_SelectCount++;
            }
        }
    }

    if(GetSelectedCount() >= 2) {
        auto& match_table_first = m_MatchTable[m_SelectedElements.first];
        auto& match_table_second = m_MatchTable[m_SelectedElements.second];

        m_DeselectTimer.TimerProcess();

        if(match_table_first.GetID() == match_table_second.GetID()) {
            match_table_first.Pick();
            match_table_second.Pick();

            m_SelectCount = 0;
        }

        else {
            if(m_DeselectTimer.TimerFinished()) {
                match_table_first.Deselect();
                match_table_second.Deselect();

                m_SelectCount = 0;

                m_DeselectTimer = Timer(0.5f);
            }
        }
    }
}