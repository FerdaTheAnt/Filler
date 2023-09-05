#include<iostream>

#include "Bubble.hpp"
#include "Button.hpp"
#include "SDL2/SDL.h"

#include "RenderWindow.hpp"
#include "SDL2/SDL_events.h"
#include "SDL2/SDL_pixels.h"
#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_surface.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_video.h"

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
    :window(NULL), renderer(NULL)
{
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);

    if(window == NULL)
    {
        std::cerr << "Window failed to initialize. Error: " << SDL_GetError() << std::endl;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    init_ui();
}

SDL_Texture* RenderWindow::loadTexture(const char* p_path)
{
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, p_path);

    if (texture == NULL) 
    {
        std::cerr << "Failed to load texture. Error: " << SDL_GetError() << std::endl;
    }
    return texture;
}

void RenderWindow::clean()
{
    if(button_texture != NULL)
        SDL_DestroyTexture(button_texture);
    if(quit_button != nullptr)
        delete quit_button;
    if(pause_button != nullptr)
        delete pause_button;
    if(info_button != nullptr)
        delete info_button;
    if(newgame_button != nullptr)
        delete newgame_button;
    if(score != nullptr)
        delete score;
    if(lives != nullptr)
        delete lives;
    SDL_DestroyWindow(this->window);
}

void RenderWindow::init_ui()
{
    button_texture = loadTexture("../res/buttons.png");

    int w_width, w_height;
    SDL_GetWindowSize(this->window, &w_width, &w_height);
    int button_width = 0.1*w_width;

    newgame_button = new Button(button_texture, button_type::NEW_GAME, button_width, 50, 0, 0);
    info_button = new Button(button_texture, button_type::INFO, button_width, 50, w_width/2 - button_width, 0);
    pause_button = new Button(button_texture, button_type::PAUSE, button_width, 50, w_width/2, 0);
    quit_button = new Button(button_texture, button_type::QUIT, button_width, 50, w_width - button_width, 0);

    font = TTF_OpenFont("../res/AXCART.TTF", 40);
    SDL_Color my_white = {248, 248, 247, 255};

    SDL_Surface* score_surface = TTF_RenderText_Solid(font, "Score: 0", my_white);

    SDL_Texture* score_texture = SDL_CreateTextureFromSurface(renderer, score_surface);
    SDL_FreeSurface(score_surface);

    score = new Label("Score 0", 50, font, my_white, score_texture, button_width + 20, 0, button_width, 50);

    SDL_Surface* lives_surface = TTF_RenderText_Solid(font, "Lives: 2", my_white);

    SDL_Texture* lives_texture = SDL_CreateTextureFromSurface(renderer, lives_surface);
    SDL_FreeSurface(lives_surface);

    lives = new Label("Lives: 2", 50, font, my_white, lives_texture, w_width/2 + button_width + 20, 0, button_width, 50);
}

void RenderWindow::render_menu()
{
    render(newgame_button->get_src_rect(), newgame_button->get_dst_rect(), newgame_button->get_texture());
    render(pause_button->get_src_rect(), pause_button->get_dst_rect(), pause_button->get_texture());
    render(info_button->get_src_rect(), info_button->get_dst_rect(), info_button->get_texture());
    render(quit_button->get_src_rect(), quit_button->get_dst_rect(), quit_button->get_texture());
    
    render(*score);
    render(*lives);
}

void RenderWindow::render_border(int p_border, int width, int height)
{
    SDL_SetRenderDrawColor(renderer, 248, 248, 247, 255);

    SDL_Rect border[4];
    //left
    border[0].x = 0;
    border[0].y = menu_height;
    border[0].w = p_border;
    border[0].h = height;

    //right
    border[1].x = width-p_border;
    border[1].y = menu_height;
    border[1].w = p_border;
    border[1].h = height;

    //top
    border[2].x = 0;
    border[2].y = menu_height;
    border[2].w = width;
    border[2].h = p_border;

    //bottom
    border[3].x = 0;
    border[3].y = menu_height + height - p_border;
    border[3].w = width;
    border[3].h = p_border;

    SDL_RenderDrawRects(renderer, border, 4);
    SDL_RenderFillRects(renderer, border, 4);
}

void RenderWindow::clear()
{
    SDL_SetRenderDrawColor(renderer, 61, 63, 53, 255);
    SDL_RenderClear(renderer);
}

void RenderWindow::render(const SDL_Rect& p_src, const SDL_Rect& p_dst, SDL_Texture* p_tex)
{
    SDL_Rect src;
    src.h = p_src.h;
    src.w = p_src.w;
    src.x = p_src.x;
    src.y = p_src.y;

    SDL_Rect dst;
    dst.h = p_dst.h;
    dst.w = p_dst.w;
    dst.x = p_dst.x;
    dst.y = p_dst.y;
    SDL_RenderCopy(renderer, p_tex, &src, &dst);
}

void RenderWindow::render(Label& label)
{
    SDL_Rect dst_rect;
    dst_rect.h = label.get_dst_rect().h;
    dst_rect.w = label.get_dst_rect().w;
    dst_rect.x = label.get_dst_rect().x;
    dst_rect.y = label.get_dst_rect().y;

    if(label.get_changed())
    {
        SDL_Surface* label_surface = TTF_RenderText_Solid(label.get_font(), label.get_text(), label.get_color());

        SDL_Texture* label_texture = SDL_CreateTextureFromSurface(renderer, label_surface);
        label.set_texture(label_texture);
        SDL_FreeSurface(label_surface);
    }

    SDL_RenderCopy(renderer, label.get_texture(), NULL, &dst_rect);
}

void RenderWindow::render(Bubble& bubble, SDL_Texture* p_tex)
{
    SDL_Rect src;
    src.h = bubble.get_src_rect().h;
    src.w = bubble.get_src_rect().w;
    src.x = bubble.get_src_rect().x;
    src.y = bubble.get_src_rect().y;

    SDL_Rect dst;
    dst.h = bubble.get_dst_rect().h;
    dst.w = bubble.get_dst_rect().w;
    dst.x = bubble.get_dst_rect().x;
    dst.y = bubble.get_dst_rect().y;

    SDL_RenderCopy(renderer, p_tex, &src, &dst);

    //SDL_RenderDrawRect(renderer, &dst);
}

void RenderWindow::render(Bludger& bludger, SDL_Texture* p_tex)
{
    SDL_Rect src;
    src.h = bludger.get_src_rect().h;
    src.w = bludger.get_src_rect().w;
    src.x = bludger.get_src_rect().x;
    src.y = bludger.get_src_rect().y;

    SDL_Rect dst;
    dst.h = bludger.get_dst_rect().h;
    dst.w = bludger.get_dst_rect().w;
    dst.x = bludger.get_dst_rect().x;
    dst.y = bludger.get_dst_rect().y;

    SDL_RenderCopy(renderer, p_tex, &src, &dst);

    //SDL_RenderDrawRect(renderer, &dst);
}
void RenderWindow::display()
{
    SDL_RenderPresent(renderer);
}

void RenderWindow::main_loop(GamePresenter& presenter)
{
    int w_width, w_height;
    SDL_GetWindowSize(this->window, &w_width, &w_height);
    const int FPS = 60;
    const int frame_delay = 1000 / FPS;

    Uint32 frame_start;
    int frame_time;

    SDL_Event e;
    SDL_Rect mouse_point;
    mouse_point.w = 1;
    mouse_point.h = 1;

    bool running = true;
    while(running){

        frame_start = SDL_GetTicks();

        while(SDL_PollEvent(&e))
        {
            switch(e.type)
            {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    mouse_point.x = e.button.x;
                    mouse_point.y = e.button.y;
                    if(e.button.y > menu_height)
                        presenter.on_mouse_clicked(e.button.x, e.button.y);
                    else if (SDL_HasIntersection(&mouse_point, &quit_button->get_dst_rect()))
                        presenter.on_quit_button_clicked();
                    else if (SDL_HasIntersection(&mouse_point, &pause_button->get_dst_rect()))
                        presenter.on_pause_button_clicked();
                    else if (SDL_HasIntersection(&mouse_point, &info_button->get_dst_rect()))
                        presenter.on_info_button_clicked();
                    else if (SDL_HasIntersection(&mouse_point, &newgame_button->get_dst_rect()))
                        presenter.on_newgame_button_clicked();
                    break;
                case SDL_MOUSEMOTION:
                    presenter.on_mouse_dragged(e.button.x, e.button.y);
                    break;
                case SDL_MOUSEBUTTONUP:
                    presenter.on_mouse_released();
                    break;
                default:
                    break;
            }           
        }
        //presenter.on_mouse_pressed();
        presenter.update();

        frame_time = SDL_GetTicks() - frame_start;
        if(frame_time < frame_delay)
        {
            SDL_Delay(frame_delay - frame_time);
        }
    }
}

void RenderWindow::pause_loop(GamePresenter& presenter)
{
    SDL_Event e;

    SDL_Rect mouse_point;
    mouse_point.w = 1;
    mouse_point.h = 1;

    bool paused = true;
    while(paused)
    {
        while(SDL_PollEvent(&e))
        {
            switch(e.type)
            {
                case SDL_QUIT:
                    presenter.on_quit_button_clicked();
                    paused = false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    mouse_point.x = e.button.x;
                    mouse_point.y = e.button.y;
                    if (SDL_HasIntersection(&mouse_point, &quit_button->get_dst_rect()))
                    {
                        presenter.on_quit_button_clicked();
                        paused = false;
                    }
                    else if (SDL_HasIntersection(&mouse_point, &pause_button->get_dst_rect()))
                        paused = false;
                    else if (SDL_HasIntersection(&mouse_point, &info_button->get_dst_rect()))
                        presenter.on_info_button_clicked();
                    else if (SDL_HasIntersection(&mouse_point, &newgame_button->get_dst_rect()))
                    {
                        presenter.on_newgame_button_clicked();
                        paused = false;
                    }   
                    break;
            }
            if(!paused)
                break;
        }
    }
}