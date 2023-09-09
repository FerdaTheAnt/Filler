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
    bubble_scored.clear();
    spawn_bludgers(p_level);
    level = p_level;
    score = p_score;

    lives = level + 1;
    max_bubbles = 18 + 2*level;
    count_bubbles = 0;

    covered = 0;

    win = false;
    lose = false;
}

void Game::restart()
{
    init_level(1, 0);
}

void Game::next_level()
{
    init_level(++level, score);
}

void Game::spawn_bubble(float p_x, float p_y)
{
    if(++count_bubbles > max_bubbles && !win)
    {
        lose = true;
        return;
    }
    bubbles.emplace_back(p_x, p_y, 20);
    bubble_scored.emplace_back(false);
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

            if(!bubble_scored[index-1])
                count_bubble(index-1);
        }
        index++;
    }

    index = 1;
    int bubble_index = 0;
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
                ouch(bubble_index);
            bubble_index++;
        }
        bubble_index = 0;

        bludger.move();
        index++;
    }
}

void Game::count_bubble(int bubble_index)
{
    Bubble bubble = bubbles[bubble_index];
    int game_area = width*height;
    int bubble_area = bubble.get_area();
    covered += 100 * (float) bubble_area/game_area;
    bubble_scored[bubble_index] = true;
    //std::cout << "Area covered: " << covered << " %" <<std::endl;
    if(covered > 66.7)
    {
        win = true;
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

void Game::ouch(int bubble_index)
{
    if(--lives <= 0)
        lose = true;
    //std::cout << "Bubble popped. Lives remaining: " << --lives << std::endl;
    bubble_scored[bubble_index] = true;
}