#include "Bludger.hpp"

#include "RoundEntity.hpp"
#include "SDL2/SDL_rect.h"

#include <cstdlib>
#include <cmath>

static const float BLUDGER_RADIUS = 15.0;
static const float BLUDGER_VELOCITY = 5.0;

Bludger::Bludger(float p_x, float p_y)
:RoundEntity(p_x, p_y, BLUDGER_RADIUS)
{
    //int sign = 1;
    int sign = rand() % 100;
    (sign > 50) ? sign = 1 : sign = -1;
    float direction = sign * (rand() % 100) * 0.01; //generate random number between 0 and 1 
    v_x = direction * BLUDGER_VELOCITY;
    v_y = (1-direction) * BLUDGER_VELOCITY;
}

SDL_Rect Bludger::get_dst_rect()
{
    //1.52
    SDL_Rect dst_rect;
    dst_rect.w = 2*1.53*BLUDGER_RADIUS;
    dst_rect.h = 2*1.53*BLUDGER_RADIUS;
    dst_rect.x = x - 1.53*BLUDGER_RADIUS;
    dst_rect.y = y - 1.53*BLUDGER_RADIUS;
    return dst_rect;
}

SDL_Rect Bludger::get_src_rect()
{
    SDL_Rect src_rect;
    src_rect.x = 0;
    src_rect.y = 0;
    src_rect.w = 85;
    src_rect.h = 85;
    return src_rect;
}

bool Bludger::resolve_bubble_collision(Bubble& bubble)
{
    if(detect_round_collision(bubble))
    {
        if(!bubble.get_growing())
        {
            RoundEntity::resolve_round_collision(bubble);
            float vel_norm = sqrt(v_x*v_x + v_y*v_y);
            v_x *= BLUDGER_VELOCITY/vel_norm;
            v_y *= BLUDGER_VELOCITY/vel_norm;
            return false;
        }
        else
        {
            bubble.pop();
            return true;
        }
    }
    return false;
}