#include "Window.hpp"

#include "Label.hpp"
#include "Button.hpp"

#include "SDL2/SDL_image.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_ttf.h"
#include<iostream>

void Window::clear()
{
    SDL_SetRenderDrawColor(renderer, 61, 63, 53, 255);
    SDL_RenderClear(renderer);
}

void Window::display()
{
    SDL_RenderPresent(renderer);
}

void Window::set_render(SDL_Renderer* ren)
{
    renderer = ren;
}

void Window::set_window(SDL_Window* win)
{
    window = win;
}

void Window::render(const SDL_Rect& p_src, const SDL_Rect& p_dst, SDL_Texture* p_tex)
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

SDL_Texture* Window::loadTexture(const char* p_path)
{
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, p_path);

    if (texture == NULL) 
    {
        std::cerr << "Failed to load texture. Error: " << SDL_GetError() << std::endl;
    }
    return texture;
}

void Window::render(Label& label)
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