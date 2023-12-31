#include "InfoWindow.hpp"

#include "Window.hpp"
#include "Button.hpp"
#include "Label.hpp"

#include "SDL2/SDL.h"
#include "SDL2/SDL_events.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_pixels.h"
#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_video.h"
#include <iostream>

InfoWindow::InfoWindow(SDL_Renderer* p_renderer, SDL_Window* p_window)
:Window(p_renderer, p_window)
{
    create_layout();
}

void InfoWindow::create_layout()
{
    int parent_w, parent_h;
    SDL_GetWindowSize(window, &parent_w, &parent_h);

    size_w = parent_w/3;
    size_h = parent_h/3;

    pos_x = 0.5*(parent_w - size_w);
    pos_y = 0.5*(parent_h - size_h);

    //set up a texture rectangle to draw to
    dialog = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, size_w, size_h);

    TTF_Font* font = TTF_OpenFont("../res/AXCART.TTF", 18);
    TTF_Font* big_font = TTF_OpenFont("../res/AXCART.TTF", 24);
    SDL_Color my_white = {248, 248, 247, 255};

    int line_h = 20;
    lines.push_back(Label("Game Rules", 24, big_font, my_white, 2*border_w, 2*border_w));
    lines.push_back(Label("Grow bubbles using mouse.", 18, font, my_white, 2*border_w, line_h + 3*border_w));
    lines.push_back(Label("If a ball hits the bubble", 18, font, my_white, 2*border_w, 2*line_h + 3*border_w));
    lines.push_back(Label("bubble will pop and you lose one life.", 18, font, my_white, 2*border_w, 3*line_h + 3*border_w));
    lines.push_back(Label("If you manage to release the bubble", 18, font, my_white, 2*border_w, 4*line_h + 3*border_w));
    lines.push_back(Label("it becomes solid. The goal is", 18, font, my_white, 2*border_w, 5*line_h + 3*border_w));
    lines.push_back(Label("to cover 2/3 of screen with bubbles.", 18, font, my_white, 2*border_w, 6*line_h + 3*border_w));

    SDL_Texture* button_texture = IMG_LoadTexture(renderer, "../res/buttons.png");
    int button_w = 0.3*size_w;
    int button_h = 0.4*button_w;
    close_button = new Button(button_texture, button_type::CLOSE, button_w, button_h,
                             0.5*size_w - 0.5*button_w,
                            size_h - 1.5*button_h);
}

void InfoWindow::show()
{
    SDL_SetRenderTarget(renderer, dialog);
    SDL_SetRenderDrawColor(renderer, 61, 63, 53, 255);
    SDL_RenderClear(renderer);

    draw_border();

    for(Label& line : lines)
    {
        render(line);
    }
    render(close_button->get_src_rect(), close_button->get_dst_rect(), close_button->get_texture());
    
    SDL_SetRenderTarget(renderer, NULL);

    SDL_Rect dst = {pos_x, pos_y, size_w, size_h};
    SDL_RenderCopy(renderer, dialog, NULL, &dst);
    SDL_RenderPresent(renderer);
}

InfoWindow::~InfoWindow()
{
    if(close_button != nullptr)
        delete close_button;
    if(dialog != nullptr)
        SDL_DestroyTexture(dialog);
}

void InfoWindow::draw_border()
{
    SDL_SetRenderDrawColor(renderer, 248, 248, 247, 255);

    SDL_Rect border[4];
    //left
    border[0].x = 0;
    border[0].y = 0;
    border[0].w = border_w;
    border[0].h = size_h;

    //right
    border[1].x = size_w-border_w;
    border[1].y = 0;
    border[1].w = border_w;
    border[1].h = size_h;

    //top
    border[2].x = 0;
    border[2].y = 0;
    border[2].w = size_w;
    border[2].h = border_w;

    //bottom
    border[3].x = 0;
    border[3].y = size_h - border_w;
    border[3].w = size_w;
    border[3].h = border_w;

    SDL_RenderDrawRects(renderer, border, 4);
    SDL_RenderFillRects(renderer, border, 4);
}

void InfoWindow::loop()
{
    bool running = true;

    SDL_Rect mouse_point;
    mouse_point.h = 1;
    mouse_point.w = 1;

    SDL_Rect button_rect = close_button->get_dst_rect();
    button_rect.x += pos_x;
    button_rect.y += pos_y;

    SDL_Event e;

    while(running)
    {
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
                    if (SDL_HasIntersection(&mouse_point, &button_rect))
                        running = false;
                    break;
                case SDL_MOUSEMOTION:
                    mouse_point.x = e.button.x;
                    mouse_point.y = e.button.y;
                    if(SDL_HasIntersection(&mouse_point, &button_rect))
                    {
                        close_button->on_hovered();
                    }
                    else
                        close_button->not_hovered();
                    break;
            }
        }
        show();
    }
}