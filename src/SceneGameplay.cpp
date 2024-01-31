#include "SceneGameplay.hpp"

#include <memory>

#include "raylib.h"
#include "raygui.h"

#include "MatchTable.hpp"
#include "Window.hpp"
#include "Debug.hpp"

#include "SceneMenager.hpp"
#include "SceneMainMenu.hpp"

#include "PlayerData.hpp"

SceneGameplay::SceneGameplay(const MatchTableDifficulty difficulty) : m_MatchTable(difficulty), m_CountdownTimer(COUNTDOWN_TIME), m_GameTime(0.0), m_GameplayState(STATE_COUNTDOWN) { }

SceneGameplay::~SceneGameplay() {
    Destroy();
}

void SceneGameplay::Init() {
    Window::Get().SetRendererBackgroundColor(235, 235, 235);
}

void SceneGameplay::Destroy() {

}

void SceneGameplay::Update() {
    switch(m_GameplayState) {
        case STATE_COUNTDOWN:
            m_CountdownTimer.Process();

            if(m_CountdownTimer.Finished() || (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_SPACE))) {
                m_GameplayState = STATE_GAMEPLAY;
            }

            break;

        case STATE_GAMEPLAY:
            m_MatchTable.Update();
            m_GameTime += GetFrameTime();

            if(IsKeyPressed(KEY_ESCAPE)) {
                m_GameplayState = STATE_PAUSED;
            }

            if(m_MatchTable.GetCompleteState()) {
                m_GameplayState = STATE_COMPLETE;
            }

            break;
        
        case STATE_PAUSED:
            if(IsKeyPressed(KEY_ESCAPE)) {
                // TODO: add an option to switch post-pause countdown on and off in the settings
                // For now, let's stay with the countdown

                m_CountdownTimer = Timer(COUNTDOWN_TIME);
                m_GameplayState = STATE_COUNTDOWN;
            }

            break;

        case STATE_COMPLETE:
            switch(m_MatchTable.GetDifficulty()) {
                case DIFFICULTY_EASY: 
                    if(!PlayerData::Get().GetCompleteState(0)) 
                        PlayerData::Get().SetCompleteState(0, true); 

                    if(PlayerData::Get().GetCompleteTime(0) >= m_GameTime || PlayerData::Get().GetCompleteTime(0) == 0.0f) 
                        PlayerData::Get().SetCompleteTime(0, m_GameTime); 

                    break;

                case DIFFICULTY_NORMAL: 
                    if(!PlayerData::Get().GetCompleteState(1)) 
                        PlayerData::Get().SetCompleteState(1, true); 

                    if(PlayerData::Get().GetCompleteTime(1) >= m_GameTime || PlayerData::Get().GetCompleteTime(1) == 0.0f) 
                        PlayerData::Get().SetCompleteTime(1, m_GameTime); 

                    break;

                case DIFFICULTY_HARD: 
                    if(!PlayerData::Get().GetCompleteState(2)) 
                        PlayerData::Get().SetCompleteState(2, true); 

                    if(PlayerData::Get().GetCompleteTime(2) >= m_GameTime || PlayerData::Get().GetCompleteTime(2) == 0.0f) 
                        PlayerData::Get().SetCompleteTime(2, m_GameTime); 

                    break;
            }

            break;
    }
}

void SceneGameplay::Render() {
    switch(m_GameplayState) {
        case STATE_COUNTDOWN: {
            std::string countdown_text = std::to_string(m_CountdownTimer.GetTimeI() + 1);
            std::string tip_text = "Press SPACE, ESC or ENTER to skip the countdown...";
            
            GuiSetStyle(LABEL, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);

            GuiSetStyle(DEFAULT, TEXT_SIZE, 64);
            GuiLabel(Rectangle { 96, 72, 208, 144 }, countdown_text.c_str());
            GuiSetStyle(DEFAULT, TEXT_SIZE, 10);
            GuiLabel(Rectangle { 40, 216, 320, 24}, tip_text.c_str());

            GuiSetStyle(LABEL, TEXT_ALIGNMENT, DEFAULT);

            break;
        }

        case STATE_GAMEPLAY: {
            for(auto& i : m_MatchTable.GetTable()) {
                i.Render();
            }

            if(GuiLabelButton(Rectangle{ 376, 0, 24, 24 }, GuiIconText(ICON_PLAYER_PAUSE, nullptr))) {
                m_GameplayState = STATE_PAUSED;
            }

            GuiLabel(Rectangle { 0, 0, 120, 24 }, TextFormat("Time: %0.02fs", m_GameTime));

            break;
        }

        case STATE_PAUSED: {
            GuiSetStyle(LABEL, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);

            GuiSetStyle(DEFAULT, TEXT_SIZE, 32);
            GuiLabel(Rectangle { 136, 88, 128, 64 }, "Pause");
            GuiSetStyle(DEFAULT, TEXT_SIZE, 10);
            
            if(GuiButton(Rectangle { 144, 168, 112, 24 }, GuiIconText(ICON_RESTART, "Resume"))) {
                m_GameplayState = STATE_GAMEPLAY;
            }

            if(GuiButton(Rectangle { 144, 200, 112, 24 }, GuiIconText(ICON_EXIT, "Quit"))) {
                SceneMenager::Get().LoadScene(std::make_unique<SceneMainMenu>());
            }

            break;
        }

        case STATE_COMPLETE: {
            GuiSetStyle(LABEL, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);

            GuiSetStyle(DEFAULT, TEXT_SIZE, 32);
            GuiLabel(Rectangle { 96, 64, 208, 80 }, "Level Complete!");
            GuiSetStyle(DEFAULT, TEXT_SIZE, 10);

            GuiLabel(Rectangle { 144, 152, 112, 24 }, GuiIconText(ICON_CLOCK, TextFormat("Time: %0.02fs", m_GameTime)));

            GuiSetStyle(LABEL, TEXT_ALIGNMENT, DEFAULT);
            
            if(GuiButton(Rectangle { 144, 192, 112, 24 }, GuiIconText(ICON_RESTART, "Play again"))) {
                SceneMenager::Get().LoadScene(std::make_unique<SceneGameplay>((MatchTableDifficulty) m_MatchTable.GetDifficultyValue()));
            }

            if(GuiButton(Rectangle { 144, 224, 112, 24 }, GuiIconText(ICON_EXIT, "Quit"))) {
                SceneMenager::Get().LoadScene(std::make_unique<SceneMainMenu>());
            }

            break;
        }
    }
        
}
