#pragma once

#include "Bludger.hpp"
#include "SDL2/SDL_rect.h"

class Bubble
{
public:
    Bubble(float p_x, float p_y, float p_radius = 10);
    void grow();
    void pop();
    void collide();
    void move();
    void shift(float p_x, float p_y)
    {
        if(growing)
        {
            x = p_x;
            y = p_y;
        }
    }
    float getArea();
    void stopGrowth()
    {
        growing = false;
    }
    bool get_growing(){return growing;}
    SDL_Rect get_src_rect();
    SDL_Rect get_dst_rect();
    void resolveBoundaryCollision(int width, int height, int border);
    void resolveBubbleCollision(Bubble& other);
    void resolveBludgerCollision(Bludger& bludger);
private:
    const float elasticity = 0.8;
    const float friction = 0.3;
    const float gravity = 0.1;
    bool growing = true;
    float x, y, radius;
    float v_x, v_y;

    bool detectRoundObjCollision(float other_x, float other_y, float other_radius);
};