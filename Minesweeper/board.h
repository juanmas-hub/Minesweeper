#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "text.h"

const int columns = 26;
const int rows = 32;
const int cellSize = 16;
int bombs_amount = 10;

struct Cell
{
	SDL_Rect rect;
    int bombsAround = 0;
	bool isBomb = false;
	bool flag = false;
	bool wasSelected = false;

};

// Funciones Auxiliares
void generateRandomCoordinates(int& row, int& col)
{
    row = std::rand() % rows;
    col = std::rand() % columns;
}

int count_bombs_around(Cell board[][columns], int row, int col)
{
    int count = 0;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            int newRow = row - 1 + i;
            int newCol = col - 1 + j;
            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < columns)
            {
                if (board[newRow][newCol].isBomb == true)
                    count++;
            }
        }
    }

    // Si la celda que analizamos es una bomba, resto uno porque no hay que tomarla en cuenta
    if (row >= 0 && row < rows && col >= 0 && col < columns && board[row][col].isBomb == true)
        count--;

    return count;

}


// Funciones de configuración del tablero
void setCellsPosition(Cell board[][columns]) {
    int xSum = 0;
    int ySum = 0;

    for (int row = 0; row < rows; row++) {
        xSum = 0;

        for (int col = 0; col < columns; col++) {
            board[row][col].rect.x = xSum;
            board[row][col].rect.y = ySum;
            xSum += cellSize;

            board[row][col].rect.h = cellSize;
            board[row][col].rect.w = cellSize;
        }

        ySum += cellSize;
    }
}

void setBombs(Cell board[][columns])
{
    // Inicializar la semilla
    std::srand(std::time(0));

    int row, col;
    for (int i = 0; i < bombs_amount; i++)
    {
        generateRandomCoordinates(row, col);

        if (board[row][col].isBomb)
            i--;

        else
        {
            board[row][col].isBomb = true;
        }
    }
}

void setNums(Cell board[][columns])
{
    for (int row = 0; row < rows; row++) {
        {
            for (int col = 0; col < columns; col++)
            {
                int count = count_bombs_around(board, row, col);
                board[row][col].bombsAround = count;
            }
        }
    }
}

int board_init(Cell board[][columns])
{
    setCellsPosition(board); 

    setBombs(board);

    setNums(board);

    return 1;
}

// Funciones relacionadas a la interfaz
void drawCell(SDLResources *resources, Cell board[][columns], int row, int col)
{
    // Llenamos la celda
    SDL_RenderFillRect(resources->renderer, &board[row][col].rect);

    // Dibujamos su contorno en blanco
    SDL_SetRenderDrawColor(resources->renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(resources->renderer, &board[row][col].rect);
}

void drawNumber(SDLResources *resources, Cell board[][columns], int row, int col)
{
    // Dibujamos el fondo de la celda antes de dibujar el número
    SDL_SetRenderDrawColor(resources->renderer, 255, 255, 255, 255); 
    SDL_RenderFillRect(resources->renderer, &board[row][col].rect); 
   
    std::string text = std::to_string(board[row][col].bombsAround);

    // Elegimos el color para el numero
    SDL_Color color = selectSDLColor(board[row][col].bombsAround);

    // Surface y textura
    setTexture(resources, text, color);

    // Renderizar la textura
    SDL_RenderCopy(resources->renderer, resources->textTexture, NULL, &board[row][col].rect);

    // Liberamos la textura después de usarla
    SDL_DestroyTexture(resources->textTexture);
}



void drawBoard(SDLResources *resources, Cell board[][columns])
{
    // Limpiar renderer
    SDL_SetRenderDrawColor(resources->renderer, 0, 0, 0, 255);
    SDL_RenderClear(resources->renderer);
    
    for (int row = 0; row < rows; ++row) {

        for (int col = 0; col < columns; ++col) {

            // Si la celda tiene bombas alrededor
            if (board[row][col].wasSelected && !board[row][col].flag && board[row][col].bombsAround > 0)
            {
                drawNumber(resources, board, row, col);
                continue;
            }

            if (board[row][col].wasSelected && !board[row][col].flag && board[row][col].bombsAround == 0)
                SDL_SetRenderDrawColor(resources->renderer, 255, 255, 255, 255); // Blanco para celdas ya seleccionadas
            
            else if (board[row][col].flag) 
                SDL_SetRenderDrawColor(resources->renderer, 255, 0, 0, 255); // Rojo para celdas marcadas

            else 
                SDL_SetRenderDrawColor(resources->renderer, 200, 200, 200, 255); // Gris para celdas no seleccionadas

            drawCell(resources, board, row, col);
        }
    }

    
    SDL_RenderPresent(resources->renderer);
}
