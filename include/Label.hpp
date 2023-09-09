#pragma once

#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_ttf.h"

using std::string;

class Label
{
public:
    Label(string p_text, int p_font_size, TTF_Font* p_font, SDL_Color& p_color, int p_x, int p_y);
    void set_text(string new_text);
    bool get_changed() {return changed;}
    const char* get_text() { return text.c_str(); }
    SDL_Color get_color() { return color; }
    TTF_Font* get_font() { return font; }
    SDL_Rect get_dst_rect(){ return dst_rect; };
    void set_texture(SDL_Texture* p_texture);
    SDL_Texture* get_texture(){ return texture; }
private:
    string text;
    int font_size;
    bool changed = true;
    TTF_Font *font;
    SDL_Color color;
    SDL_Texture* texture;
    SDL_Rect dst_rect;
};