#include "Bubble.hpp"

#include "Game.hpp"
#include <algorithm>
#include <vector>
#include <iostream>

Game::Game(float p_width, float p_height, int p_border)
    :width(p_width), height(p_height), border(p_border)
{
    init_level(1, 0);
}

void Game::init_level(int p_level, int p_score)
{
    bubbles.clear();
    level = p_level;
    score = p_score;

    lives = level + 1;
    maxBubbles = 18 + 2*level;
    countBubbles = 0;

    covered = 0;

    win = false;
}

void Game::restart()
{
    init_level(1, 0);
}

void Game::spawn_bubble(float p_x, float p_y)
{
    bubbles.emplace_back(p_x, p_y, 20);
}

void Game::update()
{
    int index = 1;
    for(Bubble& bubble : bubbles)
    {
        bubble.resolveBoundaryCollision(width, height, border);
        for(int i = index; i < bubbles.size(); i++)
        {
            bubble.resolveBubbleCollision(bubbles[i]);
        }
        
        if(bubble.get_growing())
        {
            bubble.grow();
        }
        else
        {
            bubble.move();
        }
        index++;
    }
}

Bubble& Game::get_current_bubble()
{
    if(bubbles.empty())
    {
        std::cerr << "Bubbles empty"<<std::endl;
    }
    return bubbles.back();
}

void Game::release_bubble()
{
    get_current_bubble().stopGrowth();
}

std::vector<Bubble>& Game::get_bubbles()
{
    return bubbles;
}

bool Game::making_bubble()
{
    if(!bubbles.empty())
    {
        return get_current_bubble().get_growing();
    }
    return false;
}