#pragma once

#include "Bubble.hpp"
#include "RoundEntity.hpp"

#include "SDL2/SDL_rect.h"

class Bubble;

class Bludger : public RoundEntity
{
public:
    Bludger(float p_x, float p_y);
    SDL_Rect get_src_rect() override;
    SDL_Rect get_dst_rect() override;
};