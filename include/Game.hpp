#pragma once

#include "Bubble.hpp"
#include "Bludger.hpp"

#include <vector>

class Game
{
public:
    Game(float p_width, float p_heightt, int border = 10);
    void spawn_bubble(float p_x, float p_y);
    void restart();
    void release_bubble();
    bool making_bubble();
    Bubble& get_current_bubble();
    void update();
    std::vector<Bubble>& get_bubbles();
    int get_border(){return border;}
private:
    float width, height;
    int border;
    int level, score;

    int lives, maxBubbles, countBubbles;
    float covered;

    bool win;

    bool growing_bubble = false;

    std::vector<Bubble> bubbles;
    std::vector<Bludger> bludgers;

    void init_level(int p_level, int p_score);
};