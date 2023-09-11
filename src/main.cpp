#include "RenderWindow.hpp"
#include "GamePresenter.hpp"
#include "Game.hpp"

#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    RenderWindow window("Filler v1.0", 1280, 770);
    Game game(1280, 720);

    GamePresenter presenter(game, window);
    presenter.run();

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return 0;
}

//TODO:
//add border to game board - done, but not optimal
//UI with buttons - in progress
//dialog for loss, next level and win
//FPS management