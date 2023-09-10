#pragma once

#include "SDL2/SDL_render.h"
#include "Window.hpp"
#include "Label.hpp"
#include "Button.hpp"

#include "SDL2/SDL.h"
#include <vector>

class GameLostWindow : public Window
{
public:
    GameLostWindow(SDL_Renderer* p_renderer, SDL_Window* p_window);
    void create_layout();
    bool loop();
    void show();
private:
    SDL_Texture* button_texture;
    const int border_w = 5;
    int pos_x, pos_y; //position in the parent window
    int size_w, size_h;

    Button* quit_button;
    Button* newgame_button;
    std::vector<Label> lines;

    SDL_Texture* dialog;

    void draw_border();
};