#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include "RenderWindow.hpp"
#include "SDL2/SDL_events.h"
#include "SDL2/SDL_render.h"

int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    RenderWindow window("Filler v1.0", 1280, 820);
    Game game(1280, 720);

    GamePresenter presenter(game, window);
    window.main_loop(presenter);
    window.clean();

    presenter.close_presenter();

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return 0;
}

//TODO:
//fix physics - hopefully done, though very buggy in powershell
//fix spaces between sprites - done
//add border to game board - done, but not optimal
//add other game elements - bludger
//UI with buttons - in progress
//dialog for loss, next level and win
//FPS management