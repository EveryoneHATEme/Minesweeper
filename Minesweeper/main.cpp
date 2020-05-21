#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
    Game* game = new Game(1000, 600, "Minesweeper", 30);
    game->loop();
    return 0;
}   
