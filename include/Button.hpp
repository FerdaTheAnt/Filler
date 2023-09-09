#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_rect.h"

enum class button_type
{
    QUIT,
    PAUSE,
    INFO,
    NEW_GAME,
    CLOSE,
    NEXT_LEVEL
};

class Button
{
public:
    Button(SDL_Texture* p_tex, button_type p_type, int p_width, int p_height, int p_x = 0, int p_y = 0);
    ~Button(){};
    SDL_Texture* get_texture();
    SDL_Rect& get_dst_rect();
    SDL_Rect& get_src_rect();
    void on_hovered(){hover = true;}
    void not_hovered(){hover = false;}
    void set_position(int p_x, int p_y);
protected:
    int src_width = 476;
    int src_height = 192;
    SDL_Texture* texture;
    SDL_Rect src_rect, dst_rect;
    button_type type;
    bool hover;
    bool selected;
};