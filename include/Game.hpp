#pragma once

#include "GameArea.hpp"
#include "Bubble.hpp"
#include "Bludger.hpp"

#include <vector>

class Game
{
public:
    Game(unsigned int p_width, unsigned int p_height, int p_border = 10);
    void spawn_bubble(float p_x, float p_y);
    void restart();
    void release_bubble();
    bool making_bubble();
    Bubble& get_current_bubble();
    void update();
    void count_bubble(int bubble_index);
    std::vector<Bubble>& get_bubbles();
    std::vector<Bludger>& get_bludgers();
    int get_border(){return border.border_w;}
    int get_lives(){return lives;}
    float get_covered(){return covered;}
    bool get_win(){return win;}
    bool get_lose(){return lose;}
private:
    unsigned int width, height;
    int level, score;

    GameArea border;

    int lives, max_bubbles, count_bubbles;
    float covered;

    bool win, lose;

    bool growing_bubble = false;

    std::vector<Bubble> bubbles;
    std::vector<bool> bubble_scored;
    std::vector<Bludger> bludgers;

    void init_level(int p_level, int p_score);
    void spawn_bludgers(int p_level);
    void ouch(int bubble_index);
};