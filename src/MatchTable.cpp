#include "MatchTable.hpp"

#include <vector>
#include <cmath>
#include <algorithm>

#include "MatchTableObject.hpp"
#include "Timer.hpp"

MatchTable::MatchTable(const MatchTableDifficulty difficulty) {
    this->m_MatchTable = std::vector<MatchTableObject>(difficulty);
    this->m_SelectedElements = std::pair<int, int>(0, 0);
    this->m_SelectCount = 0;
    this->m_DeselectTimer = Timer(0.5f);

    std::vector<int> table_values = std::vector<int>(difficulty); /* Generating the initial values for a table */
    for(int i = 0; i < (int)table_values.size(); i++) {
        int random_value = 0;

        do {
            random_value = GetRandomValue(1, (int) table_values.size() / 2);
        } while(std::count(table_values.begin(), table_values.end(), random_value) >= 2);

        table_values[i] = random_value;
    }
    
    std::vector<MatchTableObject> table = std::vector<MatchTableObject>(difficulty); /* The main match table */
    for(int i = 0; i < (int) sqrt(difficulty); i++) {
        for(int j = 0; j < (int) sqrt(difficulty); j++) {
            int index = j + i * sqrt(difficulty);
            auto& table_object = table[index];

            table_object = MatchTableObject((Vector2){(float) (j * table_object.GetWidth() + 10 * j), (float) (i * table_object.GetHeight() + 10 * i)}, table_values[index], index);
        }
    }

    std::copy(table.begin(), table.end(), this->m_MatchTable.begin());
}

void MatchTable::MatchTableProcessInput(Vector2 mouse_position) {
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && m_SelectCount < 2) {
        for(auto& i : m_MatchTable) {
            if(CheckCollisionPointRec(mouse_position, (Rectangle) { (float) i.GetPosition().x, (float) i.GetPosition().y, (float) i.GetWidth(), (float) i.GetHeight()})) {
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