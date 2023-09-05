#pragma once

struct GameArea
{
    unsigned int border_w = 10;
    //coords for the walls within window
    unsigned int top = 100;
    unsigned int left = 0;
    unsigned int right = 1280 - border_w;
    unsigned int bottom = 720 - border_w;
};