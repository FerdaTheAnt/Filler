# Filler
A clone of SimianLogic's game Filler. Made using C++ and SDL2 library.
## Descripiton
I am trying to follow Model-View-Presenter (MVP) design pattern and so far I have divided the classes as follows:
* View: RenderWindow, Button
* Presenter: GamePresenter
* Model: Game, Bubble, Bludger
RenderWindow runs in a loop where it handles displaying game objects and buttons to screen and receives user input and filters it to GamePresenter. GamePresenter then carries out corresponding action and updates game model. Game implements the rules by storing the necessary information about remaining lives, states of bubbles and by updating their physics.