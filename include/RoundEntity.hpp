#pragma once

#include "SDL2/SDL.h"

#include "GameArea.hpp"

class RoundEntity
{
public:
    RoundEntity(float p_x, float p_y, float p_radius = 0, float p_wall_elastic = 1.0, float p_other_elastic = 1.0);
    virtual void move();
    virtual SDL_Rect get_src_rect() {SDL_Rect dst; return dst;};
    virtual SDL_Rect get_dst_rect() { SDL_Rect src; return src;};
    virtual void resolve_boundary_collision(int width, int height, GameArea& border);
    virtual void resolve_round_collision(RoundEntity &other);
protected:
    float x, y;
    float radius;
    float v_x = 0, v_y = 0;
    float wall_elastic;
    float other_elastic;
    bool detect_round_collision(RoundEntity &other);
};