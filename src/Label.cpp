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
            int p_x, 
            int p_y
            )
:text(p_text), font_size(p_font_size), font(p_font), color(p_color), texture(nullptr)
{
    dst_rect.x = p_x;
    dst_rect.y = p_y;
    dst_rect.w = 0;
    dst_rect.h = 0;
    TTF_SizeText(font, text.c_str(), &dst_rect.w, &dst_rect.h);
}

void Label::set_text(string new_text)
{
    if(text != new_text)
    {
        text = new_text;
        TTF_SizeText(font, text.c_str(), &dst_rect.w, &dst_rect.h);
        changed = true;
    }
}

void Label::set_texture(SDL_Texture* p_texture)
{
    if(texture != nullptr)
        SDL_DestroyTexture(texture);
    texture = p_texture;
}