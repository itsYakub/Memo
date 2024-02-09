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

#include "ResourceMenager.hpp"

#include "SoundMenager.hpp"

#include "Settings.hpp"

SceneGameplay::SceneGameplay(const MatchTableDifficulty difficulty) : m_MatchTable(difficulty), m_CountdownTimer(COUNTDOWN_TIME), m_GameTime(0.0), m_GameplayState(STATE_COUNTDOWN), m_CountdownAfterPause(false) { }

SceneGameplay::~SceneGameplay() {
    Destroy();
}

void SceneGameplay::Init() {
    Window::Get().SetRendererBackgroundColor(245, 245, 245);

    Settings::Get().GetSettingB(GAMEPLAY_COUNTDOWN_AT_THE_BEGINNING) ? m_GameplayState = STATE_COUNTDOWN : m_GameplayState = STATE_GAMEPLAY;
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
                if(Settings::Get().GetSettingB(GAMEPLAY_COUNTDOWN_AFTER_PAUSE)) {
                    m_CountdownTimer.Reset(COUNTDOWN_TIME);
                    m_GameplayState = STATE_COUNTDOWN;
                }

                else if(!Settings::Get().GetSettingB(GAMEPLAY_COUNTDOWN_AFTER_PAUSE)) {
                    m_GameplayState = STATE_GAMEPLAY;
                }
            }

            break;

        case STATE_COMPLETE:
            switch(m_MatchTable.GetDifficulty()) 
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
            GuiSetStyle(DEFAULT, TEXT_SIZE, ResourceMenager::Get().GetCurrentFont().baseSize);
            GuiSetStyle(LABEL, TEXT_ALIGNMENT, DEFAULT);
            GuiSetStyle(DEFAULT, TEXT_WRAP_MODE, TEXT_WRAP_WORD);
            GuiLabel(Rectangle { 16, 216, 368, 48}, tip_text.c_str());
            GuiSetStyle(DEFAULT, TEXT_WRAP_MODE, TEXT_WRAP_NONE);

            break;
        }

        case STATE_GAMEPLAY: {
            DrawTextureEx(ResourceMenager::Get().GetTextureByName("background"), Vector2 { 0, 0 }, 0.0f, 10.0f, WHITE);

            for(auto& i : m_MatchTable.GetTable()) {
                i.Render();
            }

            if(GuiLabelButton(Rectangle{ 376, 0, 24, 24 }, GuiIconText(ICON_PLAYER_PAUSE, nullptr))) {
                m_GameplayState = STATE_PAUSED;

                SoundMenager::Get().PlaySoundFromCache("click");
            }

            if(Settings::Get().GetSettingB(GAMEPLAY_DISPLAY_TIME)) {
                GuiLabel(Rectangle { 8, 0, 120, 24 }, TextFormat("Time: %0.02fs", m_GameTime));
            }

            break;
        }

        case STATE_PAUSED: {        
            GuiSetStyle(LABEL, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);

            GuiSetStyle(DEFAULT, TEXT_SIZE, 32);
            GuiLabel(Rectangle { 136, 88, 128, 64 }, "Pause");
            GuiSetStyle(DEFAULT, TEXT_SIZE, ResourceMenager::Get().GetCurrentFont().baseSize);

            GuiSetStyle(LABEL, TEXT_ALIGNMENT, DEFAULT);
            
            if(GuiButton(Rectangle { 144, 168, 112, 24 }, GuiIconText(ICON_RESTART, "Resume"))) {
                m_GameplayState = STATE_GAMEPLAY;

                SoundMenager::Get().PlaySoundFromCache("click");
            }

            if(GuiButton(Rectangle { 144, 200, 112, 24 }, GuiIconText(ICON_EXIT, "Quit"))) {
                SceneMenager::Get().LoadScene(std::make_unique<SceneMainMenu>());

                SoundMenager::Get().PlaySoundFromCache("click");
            }

            break;
        }

        case STATE_COMPLETE: {
            GuiSetStyle(LABEL, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);

            GuiSetStyle(DEFAULT, TEXT_SIZE, 32);
            GuiLabel(Rectangle { 48, 80, 304, 64 }, "Level Complete!");
            GuiSetStyle(DEFAULT, TEXT_SIZE, ResourceMenager::Get().GetCurrentFont().baseSize);

            GuiLabel(Rectangle { 144, 152, 112, 24 }, GuiIconText(ICON_CLOCK, TextFormat("Time: %0.02fs", m_GameTime)));

            GuiSetStyle(LABEL, TEXT_ALIGNMENT, DEFAULT);
            
            if(GuiButton(Rectangle { 120, 192, 160, 24 }, GuiIconText(ICON_RESTART, "Play again"))) {
                SceneMenager::Get().LoadScene(std::make_unique<SceneGameplay>((MatchTableDifficulty) m_MatchTable.GetDifficultyValue()));

                SoundMenager::Get().PlaySoundFromCache("click");
            }

            if(GuiButton(Rectangle { 144, 224, 112, 24 }, GuiIconText(ICON_EXIT, "Quit"))) {
                SceneMenager::Get().LoadScene(std::make_unique<SceneMainMenu>());

                SoundMenager::Get().PlaySoundFromCache("click");
            }

            break;
        }
    }
        
}
