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

void MatchTableProcessInput(MatchTable& table, Vector2 mouse_position) {
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && table.GetSelectedCount() < 2) {
        for(auto& i : table.GetTable()) {
            if(CheckCollisionPointRec(mouse_position, (Rectangle) { (float) i.GetPosition().x, (float) i.GetPosition().y, (float) i.GetWidth(), (float) i.GetHeight()})) {
                if(i.GetPickState()) {
                    break;
                }

                else if(i.GetSelectState()) {
                    i.Deselect();

                    table.SetSelectedCount(table.GetSelectedCount() - 1);

                    break;
                }

                i.Select();
                
                table.GetSelectedCount() == 0 ? table.GetSelectedPair().first = i.GetIndex() : table.GetSelectedPair().second = i.GetIndex();
                table.SetSelectedCount(table.GetSelectedCount() + 1);
            }
        }
    }

    if(table.GetSelectedCount() >= 2) {
        auto& match_table_first = table.GetTable()[table.GetSelectedPair().first];
        auto& match_table_second = table.GetTable()[table.GetSelectedPair().second];

        table.GetDeselectTimer().TimerProcess();

        if(match_table_first.GetID() == match_table_second.GetID()) {
            match_table_first.Pick();
            match_table_second.Pick();

            table.SetSelectedCount(0);
        }

        else {
            if(table.GetDeselectTimer().TimerFinished()) {
                match_table_first.Deselect();
                match_table_second.Deselect();

                table.SetSelectedCount(0);

                table.GetDeselectTimer() = Timer(0.5f);
            }
        }
    }
}