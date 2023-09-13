# Filler
A clone of SimianLogic's game Filler. Made using C++ and SDL2 library.
## Game objective
Use mouse to spawn a bubble. Grow it by holding the mouse button. When mouse is released, the bubble becomes solid, the covered area is counted and game physics starts applying to it. If a bludger touches a growing bubble, the bubble pops, player loses one life and no area is added. Level is beaten when 2/3 of game area are covered. In the next level you are met with one more bludger to avoid. Win 3 levels to beat the game.
## Descripiton
I am trying to follow Model-View-Presenter (MVP) design pattern and so far I have divided the classes as follows:
* View: RenderWindow, Button, Label, all of somethingWindow
* Presenter: GamePresenter
* Model: Game, Bubble, Bludger

RenderWindow runs in a loop where it handles displaying game objects and other elements to screen and receives user input (mouseclicks) and filters it to GamePresenter. GamePresenter then carries out corresponding action and updates game model. Game implements the rules by storing the necessary information about remaining lives, states of bubbles and by updating their physics. When necessary criteria are met, GamePresenter invokes corresponding somethingWindow loop and waits for response.

**Remark:** Game is now designed for 1920x1080 resolution and does not provide scaling

Compile (Windows) either with CMake or use following command from build directory

g++ -o filler.exe -I../include -L../lib ../src/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf