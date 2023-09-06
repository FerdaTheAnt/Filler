#include "GamePresenter.hpp"
#include "Game.hpp"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_timer.h"
#include <iostream>
#include <vector>

GamePresenter::GamePresenter(Game& p_game, RenderWindow& p_view)
     : game(&p_game), view(&p_view)
{
    bubble_texture = view->loadTexture("../res/bubble.png");
    bludger_texture = view->loadTexture("../res/bludger.png");
}

void GamePresenter::close_presenter()
{
    if(bubble_texture != NULL)
        SDL_DestroyTexture(bubble_texture);
    if(bludger_texture != NULL)
        SDL_DestroyTexture(bludger_texture);
}

void GamePresenter::on_mouse_clicked(float p_x, float p_y)
{
    mouse_pressed = true;
    game->spawn_bubble(p_x, p_y);
}

void GamePresenter::on_mouse_dragged(float p_x, float p_y)
{
    if(mouse_pressed)
    {
        game->get_current_bubble().shift(p_x, p_y);
    }
}

void GamePresenter::on_mouse_pressed()
{
    if(mouse_pressed)
    {
        game->get_current_bubble().grow();
    }
}
void GamePresenter::on_mouse_released()
{
    if(mouse_pressed)
    {
        mouse_pressed = false;
        game->release_bubble();
    }
}

void GamePresenter::on_quit_button_clicked()
{
    SDL_Event e;
    e.type = SDL_QUIT;
    SDL_PushEvent(&e);
}

void GamePresenter::on_newgame_button_clicked()
{
    game->restart();
}

void GamePresenter::on_info_button_clicked()
{
    std::cout << "info button clicked, window popup TODO." << std::endl;
}

void GamePresenter::on_pause_button_clicked()
{
    view->pause_loop(*this);
}

void GamePresenter::update()
{
    game->update();
    view->clear();
    view->render_menu();
    view->render_border(game->get_border(), 1280, 720);
    std::vector<Bubble> bubbles = game->get_bubbles();
    if(!bubbles.empty())
    {
        for(Bubble& bubble : bubbles)
        {
            view->render(bubble, this->bubble_texture);
        }
    }
    std::vector<Bludger> bludgers = game->get_bludgers();
    if(!bludgers.empty())
    {
        for(Bludger& bludger : bludgers)
        {
            view->render(bludger, this->bludger_texture);
        }
    }
    view->update_labels(game->get_lives());
    view->display();
}