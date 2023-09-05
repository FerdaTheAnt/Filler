#include "Bubble.hpp"

#include "Game.hpp"
#include <algorithm>
#include <vector>
#include <iostream>

Game::Game(unsigned int p_width, unsigned int p_height, int p_border)
    :width(p_width), height(p_height)
{
    border.border_w = p_border;
    border.top = 100;
    border.bottom = 820;
    border.right = 1280 - p_border;
    init_level(1, 0);
}

void Game::init_level(int p_level, int p_score)
{
    bubbles.clear();
    spawn_bludgers(p_level);
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

void Game::spawn_bludgers(int p_level)
{
    float x, y;
    bludgers.clear();
    for(int i = 0; i < p_level+1; i++)
    {
        x = (rand() % (width - 2*border.border_w) + border.border_w);
        y = (rand() % (height - 2*border.border_w) + border.top + border.border_w);
        bludgers.emplace_back(x, y);
    }
}

void Game::update()
{
    int index = 1;
    for(Bubble& bubble : bubbles)
    {
        bubble.resolve_boundary_collision(width, height, border);
        for(unsigned int i = index; i < bubbles.size(); i++)
        {
            bubble.resolve_bubble_collision(bubbles[i]);
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

    index = 1;
    for(Bludger& bludger : bludgers)
    {
        bludger.resolve_boundary_collision(width, height, border);
        for(unsigned int i = index; i < bludgers.size(); i++)
            {
                bludger.resolve_round_collision(bludgers[i]);
            }

        for(Bubble& bubble : bubbles)
        {
            if(bludger.resolve_bubble_collision(bubble) == true)
                ouch();
        }
        
        bludger.move();
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

std::vector<Bludger>& Game::get_bludgers()
{
    return bludgers;
}

bool Game::making_bubble()
{
    if(!bubbles.empty())
    {
        return get_current_bubble().get_growing();
    }
    return false;
}

void Game::ouch()
{
    std::cout << "Bubble popped. Lives remaining: " << --lives << std::endl;
}