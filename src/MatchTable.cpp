#include "MatchTable.hpp"

#include <vector>
#include <cmath>
#include <algorithm>

#include "MatchTableObject.hpp"
#include "Window.hpp"
#include "Timer.hpp"
#include "Debug.hpp"

MatchTable::MatchTable(const MatchTableDifficulty difficulty) : m_MatchTable(), m_Difficulty(difficulty), m_SelectedElements(std::pair<int, int>(0, 0)), m_SelectCount(0), m_DeselectTimer(DESELECT_TIME) {
    const int diff_value = difficulty;
    const int diff_value_sqrt = sqrt(difficulty);

    std::vector<int> values = std::vector<int>(difficulty);
    for(int i = 0; i < diff_value_sqrt; i++) {
        for(int j = 0; j < diff_value_sqrt; j++) {
            int index = j + i * diff_value_sqrt;
            int random_value = 0;

            do {
                random_value = GetRandomValue(1, diff_value / 2);
            } while(std::count(values.begin(), values.end(), random_value) >= 2);

            values[index] = random_value;
            
            Vector2 position;
            // Formula: position at (0,0) + the center of the screen - the half of the size of the whole table
            position.x = (float) (j * MatchTableObject::WIDTH + MatchTableObject::SPACING * j) + (Window::Get().GetRendererCenter().x) - (0.5f * (diff_value_sqrt * MatchTableObject::WIDTH + (diff_value_sqrt - 1) * MatchTableObject::SPACING));
            position.y = (float) (i * MatchTableObject::HEIGHT + MatchTableObject::SPACING * i) + (Window::Get().GetRendererCenter().y) - (0.5f * (diff_value_sqrt * MatchTableObject::HEIGHT + (diff_value_sqrt - 1) * MatchTableObject::SPACING));

            m_MatchTable.push_back(MatchTableObject(position, random_value, index));
        }
    }

    Debug::Log("Match table created successfully");
}

void MatchTable::Update() {
    ProcessInput();
    CheckTableState();
}

bool MatchTable::GetCompleteState() {
    for(auto i : m_MatchTable) {
        if(!i.GetPickState()) {
            return false;
        }
    }

    return true;
}

void MatchTable::ProcessInput() {
    if((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsKeyPressed(KEY_ENTER)) && m_SelectCount < 2) {
        for(auto& i : m_MatchTable) {
            if(CheckCollisionPointRec(GetMousePosition(), (Rectangle) { (float) i.GetPosition().x, (float) i.GetPosition().y, (float) MatchTableObject::WIDTH, (float) MatchTableObject::HEIGHT})) {
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
}

void MatchTable::CheckTableState() {
    if(GetSelectedCount() < 2) return;

    auto& match_table_first = m_MatchTable[m_SelectedElements.first];
    auto& match_table_second = m_MatchTable[m_SelectedElements.second];

    m_DeselectTimer.Process();

    if(match_table_first.GetID() == match_table_second.GetID()) {
        match_table_first.Pick();
        match_table_second.Pick();

        m_SelectCount = 0;
    }

    else if(m_DeselectTimer.Finished()) {
        match_table_first.Deselect();
        match_table_second.Deselect();

        m_SelectCount = 0;

        m_DeselectTimer = Timer(DESELECT_TIME);
    }
}
