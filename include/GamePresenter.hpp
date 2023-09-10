#pragma once

#include "Game.hpp"
#include "InfoWindow.hpp"
#include "NextLevelWindow.hpp"
#include "GameLostWindow.hpp"
#include "RenderWindow.hpp"
#include "SDL2/SDL_render.h"

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
    void on_mouse_pressed();
    void on_pause_button_clicked();
    void on_info_button_clicked();
    void on_quit_button_clicked();
    void on_newgame_button_clicked();
    void level_win();
    void game_lost();
private:
    bool mouse_pressed = false;
    SDL_Texture* bubble_texture;
    SDL_Texture* bludger_texture;
    Game* game;
    RenderWindow* view;
    InfoWindow* info_window;
    NextLevelWindow* next_window;
    GameLostWindow* lose_window;
    bool lost = false;
};