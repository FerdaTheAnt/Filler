#pragma once

#include "Label.hpp"

#include "SDL2/SDL.h"
#include "SDL2/SDL_render.h"

class Window
{
public:
    Window(SDL_Renderer* p_renderer, SDL_Window* p_window)
    :renderer(p_renderer), window(p_window){}
    SDL_Texture* loadTexture(const char* p_path);
    void render(const SDL_Rect& p_src, const SDL_Rect& p_dst, SDL_Texture* p_tex);
    void render(Label& label);
    void set_window(SDL_Window* win);
    void set_render(SDL_Renderer* ren);
    void display();
    void clear();
protected:
    SDL_Renderer* renderer;
    SDL_Window* window;
};