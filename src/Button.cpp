#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_render.h"

#include "Button.hpp"

Button::Button(SDL_Texture* p_tex, button_type p_type, int p_width, int p_height, int p_x, int p_y)
:texture(p_tex), type(p_type), hover(false)
{
    dst_rect.x = p_x;
    dst_rect.y = p_y;
    dst_rect.h = p_height;
    dst_rect.w = p_width;

    src_rect.h = src_height;
    src_rect.w = src_width;
    src_rect.x = 0;
    switch(type)
    {
        case button_type::NEW_GAME:
            src_rect.y = 0;
            break;
        case button_type::PAUSE:
            src_rect.y = src_height;
            break;
        case button_type::INFO:
            src_rect.y = 2*src_height;
            break;
        case button_type::QUIT:
            src_rect.y = 3*src_height;
            break;
        case button_type::CLOSE:
            src_rect.y = 4*src_height;
            break;
        case button_type::NEXT_LEVEL:
            src_rect.y = 5*src_height;
            break;
    }
}

SDL_Texture* Button::get_texture()
{
    return texture;
}

SDL_Rect& Button::get_src_rect()
{
    if(hover)
    {
        src_rect.x = src_width;
    }
    else 
    {
        src_rect.x = 0;
    }
    return src_rect;
}

SDL_Rect& Button::get_dst_rect()
{
    return dst_rect;
}