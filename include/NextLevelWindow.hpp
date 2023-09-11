#pragma once

#include "Window.hpp"
#include "Label.hpp"
#include "Button.hpp"
#include "Game.hpp"

#include "SDL2/SDL.h"
#include "SDL2/SDL_render.h"
#include <vector>

class NextLevelWindow : public Window
{
public:
    NextLevelWindow(SDL_Renderer* p_renderer, SDL_Window* p_window);
    ~NextLevelWindow();
    void create_layout();
    void loop(Game* game);
    void show();
private:
    int level = 0, bubbles_left = 0, lives = 0, score = 0;
    
    const int border_w = 5;
    int pos_x, pos_y; //position in the parent window
    int size_w, size_h;
    std::vector<Label> lines;
    Button* next_level_button;
    SDL_Texture* dialog;

    void draw_border();
};