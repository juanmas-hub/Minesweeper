#pragma once
// estamos en game.h
#include <iostream>
#include "init.h"
#include "board.h"



void expandCells(Cell board[][columns], int row, int col)
{
	// Marca la celda actual como seleccionada
	board[row][col].wasSelected = true;

	// Si hay bombas alrededor no se debe expandir mas
	if (board[row][col].bombsAround != 0)
		return;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			int newRow = row - 1 + i;
			int newCol = col - 1 + j;

			// Comprobar si la celda está dentro de los límites y no ha sido seleccionada
			if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < columns && !board[newRow][newCol].wasSelected)
			{
				// Llamado recursivo con las nuevas coordenadas
				expandCells(board, newRow, newCol);
			}
		}
	}
}

int setCellStatus(Cell board[][columns], int row, int column)
{
    if (board[row][column].isBomb == true && board[row][column].flag == false)
        return -1;

	if (board[row][column].wasSelected == false)
		expandCells(board, row, column);

    return 1;
}

void setFlag(Cell board[][columns], int *count, int row, int column)
{
	if (board[row][column].wasSelected == false && board[row][column].isBomb == true)
		(*count)++;
	
	if (board[row][column].flag == true && board[row][column].isBomb == true)
		(*count)--;

    // Si no estaba marcada con flag
    if (board[row][column].wasSelected == false)
    {
        board[row][column].wasSelected = true;
        board[row][column].flag = true;
    }
    // Si estaba marcada con flag
    else if (board[row][column].wasSelected == true && board[row][column].flag == true)
    {
        board[row][column].wasSelected = false;
        board[row][column].flag = false;
    }
}

// Funcion de fin de juego
void endGame(SDLResources *resources, int i, bool *running)
{
	// Limpiar renderer
	SDL_SetRenderDrawColor(resources->renderer, 0, 0, 0, 255);
	SDL_RenderClear(resources->renderer);

	std::string text;
	SDL_Color color;

	if (i < 0)
	{
		color = { 255, 0, 30, 255 };    // Rojo
		text = "You've lost";
	}
	else
	{
		color = { 0, 200, 0, 255 };     // Verde
		text = "You've won";
	}

	if (setTexture(resources, text, color) < 0)
	{
		std::cout << "Error setting texture" << std::endl;
		return;
	}

	// Obtener el tamaño del texto
	int textWidth, textHeight;
	SDL_QueryTexture(resources->textTexture, nullptr, nullptr, &textWidth, &textHeight);

	// Calcular las posiciones X e Y para centrar el texto
	int x = (width - textWidth) / 2;
	int y = (height - textHeight) / 2;

	
	SDL_Rect rect = { x, y, textWidth, textHeight };

	// Renderizar la textura en la posición centrada
	SDL_RenderCopy(resources->renderer, resources->textTexture, nullptr, &rect);

	// Mostrar en pantalla
	SDL_RenderPresent(resources->renderer);

	// Pausar durante 3 segundos
	SDL_Delay(3000);

	*running = false;
}



// Controlador de eventos
void eventHandler(SDLResources *resources, Cell board[][columns], bool *running, int *count, SDL_Event event)
{
	while (SDL_PollEvent(&event))
	{
		// Si presiona con el mouse la X de arriba a la derecha
		if (event.type == SDL_QUIT)
			*running = false;

		// Si presiona con el mouse una casilla no seleccionada anteriormente
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			int row_selected = event.button.y / cellSize;
			int column_selected = event.button.x / cellSize;
			// c++ redondea hacia abajo predeterminadamente

			if (event.button.button == SDL_BUTTON_LEFT)
			{
				// Si la casilla selecionada era bomba terminamos el juego
				if (setCellStatus(board, row_selected, column_selected) < 0)
					endGame(resources, -1, running);
			}
			if (event.button.button == SDL_BUTTON_RIGHT)
			{
				setFlag(board, count, row_selected, column_selected);
			}
		}
	}
}

void gameLoop(SDLResources *resources, Cell board[][columns], int *count)
{
	SDL_Event event = {};
	bool running = true;
	
	while (running)
	{
		drawBoard(resources, board);
		eventHandler(resources, board, &running, count, event);
		
		if ((*count) == bombs_amount)
		{
			endGame(resources, 1, &running);
		}
    }


}
	

void chooseDifficulty(int *bombsAmount)
{
	int input;

	std::cout << "Easy: (1 - 80) | Medium: (81 - 150) | Hard: (+151)" << std::endl;
	
	std::cout << "choose the difficulty of the game: "; std::cin >> input;

	*bombsAmount = input;
}
