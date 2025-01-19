// estamos en main.cpp
#include <SDL.h>
#include <stdio.h>
#include "Init.h"
#include "game.h"
#include "board.h"


int main(int argc, char* args[]) 
{
    chooseDifficulty(&bombs_amount);

    SDLResources resources;
    game_init(&resources);

    Cell board[rows][columns];
    board_init(board);

    int count = 0;
    gameLoop(&resources, board, &count);

    SDL_cleanup(&resources);

    return 0;
}
