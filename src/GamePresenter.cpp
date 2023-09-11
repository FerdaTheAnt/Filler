#include "GamePresenter.hpp"

#include "RenderWindow.hpp"
#include "InfoWindow.hpp"
#include "NextLevelWindow.hpp"
#include "GameLostWindow.hpp"
#include "GameWonWindow.hpp"
#include "Game.hpp"

#include <iostream>
#include <vector>

GamePresenter::GamePresenter(Game& p_game, RenderWindow& p_view)
     : view(&p_view), game(&p_game)
{
    bubble_texture = view->loadTexture("../res/bubble.png");
    bludger_texture = view->loadTexture("../res/bludger.png");
    info_window = view->create_info_window();
    next_window = view->create_next_level_window();
    lose_window = view->create_lose_window();
    win_window = view->create_win_window();
}

void GamePresenter::close_presenter()
{
    if(bubble_texture != NULL)
        SDL_DestroyTexture(bubble_texture);
    if(bludger_texture != NULL)
        SDL_DestroyTexture(bludger_texture);
    if(info_window != nullptr)
        delete info_window;
    if(next_window != nullptr)
        delete next_window;
    if(lose_window != nullptr)
        delete lose_window;
    if(win_window != nullptr)
        delete win_window;
    if(game != nullptr)
        delete game;
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
    mouse_pressed = false;
    game->restart();
}

void GamePresenter::on_info_button_clicked()
{
    info_window->loop();
}

void GamePresenter::on_pause_button_clicked()
{
    view->pause_loop(*this);
}

void GamePresenter::level_win()
{
    mouse_pressed = false;
    next_window->loop(game);
    game->next_level();
}

void GamePresenter::game_win()
{
    if(win_window->loop(game) == true)
        on_newgame_button_clicked();
    else
        on_quit_button_clicked();
}

void GamePresenter::game_lost()
{
    if(lose_window->loop() == true)
        on_newgame_button_clicked();
    else
        on_quit_button_clicked();
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

    view->update_labels(game->get_lives(), 
                        game->get_bubbles_left(),
                        game->get_covered(), 
                        game->get_score(),
                        game->get_level());

    view->display();

    if(game->get_win() && !won)
    {
        if(game->get_level() < 3)
            level_win();
        else
        {
            game_win();
            won = true;
            SDL_Delay(200);
        }
    }
    else if(game->get_lose() && !lost)
    {
        game_lost();
        lost = true;
        SDL_Delay(200);
    }
}

void GamePresenter::run()
{
    view->main_loop(*this);
    view->close_window();
    close_presenter();
}