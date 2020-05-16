#include <SFML/Graphics.hpp>
#include "CGame.h"

int main()
{
    CGame* game = new CGame(600, 600, "Minesweeper", 30);
    game->loop();
    return 0;
}
