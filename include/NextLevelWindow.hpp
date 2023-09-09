#pragma once

#include "SDL2/SDL_render.h"
#include "Window.hpp"
#include "Label.hpp"
#include "Button.hpp"
#include "Game.hpp"

#include "SDL2/SDL.h"
#include <vector>

class NextLevelWindow : public Window
{
public:
    NextLevelWindow(SDL_Renderer* p_renderer, SDL_Window* p_window, Game* game);
    void create_layout();
    void loop();
    void show();
private:
    int level, bubbles_left, lives, score;
    
    const int border_w = 5;
    int pos_x, pos_y; //position in the parent window
    int size_w, size_h;
    std::vector<Label> lines;
    SDL_Texture* button_texture;
    Button* next_level_button;
    SDL_Texture* dialog;

    void draw_border();
};