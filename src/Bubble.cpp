#include "Bludger.hpp"

#include <cmath>

#include "GameArea.hpp"
#include "Bubble.hpp"
#include "RoundEntity.hpp"
#include "SDL2/SDL_rect.h"

const float PI = 3.14159265;
static const float WALL_ELASTIC = 0.3;
static const float OTHER_ELASTIC = 0.8; 

Bubble::Bubble(float p_x, float p_y, float p_radius)
    :RoundEntity(p_x, p_y, p_radius, WALL_ELASTIC, OTHER_ELASTIC)
{
    v_x = 0;
    v_y = 0;
}

void Bubble::grow()
{
    if(growing)
    {
        this->radius++;
    }
}

void Bubble::pop()
{
    stopGrowth();
    this->radius = 0;
}

float Bubble::get_area()
{
    return PI*radius*radius;
}

void Bubble::move()
{
    if(!growing)
    {
        x += v_x;
        y += v_y;
        v_y += gravity;
    }
}

void Bubble::resolve_boundary_collision(int width, int height, GameArea& border)
{
    if (growing && (2*radius > width - 2*border.border_w || 2*radius > height - 2*border.border_w)) {
        stopGrowth();
    }
    RoundEntity::resolve_boundary_collision(width, height, border);
}

void Bubble::resolve_bubble_collision(Bubble &other)
{
    if(!detect_round_collision(other))
        return;

    if(growing)
    {
        stopGrowth();
        return;
    }
    if(other.growing)
    {
        other.stopGrowth();
        return;
    }

    RoundEntity::resolve_round_collision(other);
}

void Bubble::resolve_bludger_collision(Bludger& bludger)
{
    if(growing)
    {
        pop();
    }
    else
    {
        RoundEntity::resolve_round_collision(bludger);
    }
}

SDL_Rect Bubble::get_dst_rect()
{
    //decimal numbers chosen in order to fit the texture better
    SDL_Rect dst_rect;
    dst_rect.x = x - 1.06*radius;
    dst_rect.y = y - 1.06*radius;
    dst_rect.h = 2.12*radius;
    dst_rect.w = 2.12*radius;

    return dst_rect;
}

SDL_Rect Bubble::get_src_rect()
{
    SDL_Rect src_rect;
    src_rect.x = 0;
    src_rect.y = 0;
    src_rect.h = 680;
    src_rect.w = 680;

    return src_rect;
}