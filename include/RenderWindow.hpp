#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_render.h"

#include "GamePresenter.hpp"
#include "Button.hpp"

class GamePresenter;

class RenderWindow
{
public:
    RenderWindow(const char* p_title, int p_w, int p_h);
    SDL_Texture* loadTexture(const char* p_path);
    void render_border(int border, int width, int height);
    void render_menu();
    void init_ui();
    void render(const SDL_Rect& p_src, const SDL_Rect& p_dst, SDL_Texture* p_tex);
    void render(Bubble& bubble, SDL_Texture* p_pex);
    void display();
    void clean();
    void clear();
    void main_loop(GamePresenter& presenter);
    void pause_loop(GamePresenter& presenter);
private:
    const int menu_height = 100;
    Button* quit_button, *pause_button, *info_button, *newgame_button;
    SDL_Window* window;
    SDL_Renderer* renderer;
};