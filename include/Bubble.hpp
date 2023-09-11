#pragma once

#include "GameArea.hpp"
#include "RoundEntity.hpp"
#include "Bludger.hpp"

#include "SDL2/SDL_rect.h"

class Bludger;

class Bubble : public RoundEntity
{
public:
    Bubble(float p_x, float p_y, float p_radius = 10);
    void grow();
    void pop();
    void move() override;
    void shift(float p_x, float p_y)
    {
        if(growing)
        {
            x = p_x;
            y = p_y;
        }
    }
    float get_area();
    void stopGrowth()
    {
        growing = false;
    }
    bool get_growing(){return growing;}
    SDL_Rect get_src_rect() override;
    SDL_Rect get_dst_rect() override;
    void resolve_boundary_collision(int width, int height, GameArea& border) override;
    void resolve_bubble_collision(Bubble& other);
private:
    const float gravity = 0.1;
    bool growing = true;
};