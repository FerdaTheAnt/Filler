#pragma once

#include "SDL2/SDL_render.h"
#include "Window.hpp"
#include "Label.hpp"
#include "Button.hpp"
#include "Game.hpp"

#include "SDL2/SDL.h"
#include <vector>

class GameWonWindow : public Window
{
public:
    GameWonWindow(SDL_Renderer* p_renderer, SDL_Window* p_window, Game* game);
    void create_layout();
    bool loop();
    void show();
private:
    int final_score;
    
    const int border_w = 5;
    int pos_x, pos_y; //position in the parent window
    int size_w, size_h;
    std::vector<Label> lines;
    SDL_Texture* button_texture;
    Button* newgame_button;
    Button* close_button;
    SDL_Texture* dialog;

    void draw_border();
};