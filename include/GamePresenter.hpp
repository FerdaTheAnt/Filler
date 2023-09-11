#pragma once

#include "RenderWindow.hpp"
#include "InfoWindow.hpp"
#include "NextLevelWindow.hpp"
#include "GameLostWindow.hpp"
#include "GameWonWindow.hpp"
#include "Game.hpp"

class RenderWindow;

class GamePresenter
{
public:
    GamePresenter(Game& p_game, RenderWindow& p_view);
    void close_presenter();
    void run();
    //temp
    void update();
    void on_mouse_clicked(float p_x, float p_y);
    void on_mouse_dragged(float p_x, float p_y);
    void on_mouse_released();
    void on_pause_button_clicked();
    void on_info_button_clicked();
    void on_quit_button_clicked();
    void on_newgame_button_clicked();
    void level_win();
    void game_win();
    void game_lost();
private:
    bool mouse_pressed = false;

    SDL_Texture* bubble_texture;
    SDL_Texture* bludger_texture;

    RenderWindow* view;
    InfoWindow* info_window;
    NextLevelWindow* next_window;
    GameLostWindow* lose_window;
    GameWonWindow* win_window;

    Game* game;

    bool won = false;
    bool lost = false;
};