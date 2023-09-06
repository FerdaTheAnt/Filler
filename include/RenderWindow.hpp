#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_render.h"

#include "GamePresenter.hpp"
#include "Button.hpp"
#include "Label.hpp"
#include "SDL2/SDL_ttf.h"

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
    void render(Label& label);
    void render(Bludger& bludger, SDL_Texture* p_tex);
    void display();
    void clean();
    void clear();
    void update_labels(int p_lives = 2, int p_score = 0, int p_bubbles_left = 0);
    void main_loop(GamePresenter& presenter);
    void pause_loop(GamePresenter& presenter);
private:
    const int menu_height = 100;
    SDL_Texture* button_texture;
    SDL_Texture* score_texture;
    Label* score;
    Label* lives;
    Button* quit_button, *pause_button, *info_button, *newgame_button;
    TTF_Font* font;
    SDL_Window* window;
    SDL_Renderer* renderer;
};