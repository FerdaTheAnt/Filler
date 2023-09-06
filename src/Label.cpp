#include "Label.hpp"
#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_ttf.h"

#include <string>

using std::string;

Label::Label(string p_text, 
            int p_font_size, 
            TTF_Font* p_font,
            SDL_Color& p_color,
            SDL_Texture* p_texture,
            int p_x, 
            int p_y, 
            int p_w, 
            int p_h)
:text(p_text), font_size(p_font_size), font(p_font), color(p_color), texture(p_texture)
{
    dst_rect.x = p_x;
    dst_rect.y = p_y;
    dst_rect.w = p_w;
    dst_rect.h = p_h;
}

void Label::set_text(string new_text)
{
    if(text != new_text)
    {
        text = new_text;
        changed = true;
    }
}

void Label::set_texture(SDL_Texture* p_texture)
{
    if(texture != nullptr)
        SDL_DestroyTexture(texture);
    texture = p_texture;
}