#pragma once

#include "SDL2/SDL_render.h"
#include "Window.hpp"
#include "Label.hpp"
#include "Button.hpp"

#include <vector>
#include "SDL2/SDL.h"

class InfoWindow : public Window
{
public:
    InfoWindow(SDL_Renderer* p_renderer, SDL_Window* p_window);
    void create_layout();
    void loop();
    void show();
private:
    const int border_w = 5;
    int pos_x, pos_y; //position in the parent window
    int size_w, size_h;
    std::vector<Label> lines;
    SDL_Texture* button_texture;
    Button* close_button;
    SDL_Texture* dialog;

    void draw_border();
};