#pragma once

#include "Window.hpp"
#include "InfoWindow.hpp"
#include "NextLevelWindow.hpp"
#include "GameLostWindow.hpp"
#include "GameWonWindow.hpp"
#include "Button.hpp"
#include "Label.hpp"
#include "GamePresenter.hpp"

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_ttf.h"

class GamePresenter;

class RenderWindow : public Window
{
public:
    RenderWindow(const char* p_title, int p_w, int p_h);
    void render_border(int border, int width, int height);
    void render_menu();
    void init_ui();
    void render(Bubble& bubble, SDL_Texture* p_pex);
    void render(Bludger& bludger, SDL_Texture* p_tex);
    void close_window();
    InfoWindow* create_info_window();
    NextLevelWindow* create_next_level_window();
    GameLostWindow* create_lose_window();
    GameWonWindow* create_win_window();

    void buttons_not_hovered();
    void update_labels(int p_lives = 2, int p_bubbles_left = 0, float p_cleared = 0, int p_score = 0, int p_level = 1);
    void main_loop(GamePresenter& presenter);
    void pause_loop(GamePresenter& presenter);
private:
    const int menu_height = 50;

    SDL_Texture* score_texture;
    Label* cleared, *score, *bubbles_left, *lives, *level;
    Button* quit_button, *pause_button, *info_button, *newgame_button;
    TTF_Font* font, *big_font;
    SDL_Window* window;
    SDL_Renderer* renderer;
};