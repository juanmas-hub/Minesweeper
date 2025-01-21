#pragma once
#include <iostream>
#include <SDL.h>
#include "SDL_ttf.h"

const int width = 416;
const int height = 512;
const int font_size = 10;

struct SDLResources
{
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

    // SDL_ttf
    TTF_Font* font = nullptr;
    SDL_Surface* textSurface = nullptr;
    SDL_Texture* textTexture = nullptr;
};

// Inicializar SDL
int init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize. SDL_Error : \n";
        std::cout << SDL_GetError();
        return -1;   // No se pudo iniciar SDL
    }

    if (TTF_Init() == -1)
    {
        std:: cout << "Error initializing SDL_ttf\n";
        return -1;
    }
    return 1;    // SDL se inicializo correctamente
}

// Limpiar la memoria utilizada por SDL
void SDL_cleanup(SDLResources *resources) {
    
    if (resources->renderer) 
    {
        SDL_DestroyRenderer(resources->renderer);
        resources->renderer = nullptr;
    }

    if (resources->window) 
    {
        SDL_DestroyWindow(resources->window);
        resources->window = nullptr;
    }

    if (resources->font) 
    {
        TTF_CloseFont(resources->font);
        resources->font = nullptr;
    }

    if (resources->textSurface)
    {
        SDL_FreeSurface(resources->textSurface);
        resources->textSurface = nullptr;
    }

    if (resources->textTexture)
    {
        SDL_DestroyTexture(resources->textTexture);
        resources->textTexture = nullptr;
    }

    TTF_Quit();
    SDL_Quit();
}



// Crear ventana SDL
int createWindow(SDLResources *resources) 
{
    resources->window = SDL_CreateWindow("Minesweeper", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        width, height, SDL_WINDOW_SHOWN);

    if(resources->window == nullptr)
    {
        std::cout << "SDL couldn´t create the window, SDL_Error:\n";
        std::cout << SDL_GetError();
        return -1;   // No se pudo crear la ventana
    }
    return 1;    // Se creo la ventana correctamente
}

// Crear renderer SDL
int createRenderer(SDLResources *resources) 
{
    resources->renderer = SDL_CreateRenderer(resources->window, -1, SDL_RENDERER_ACCELERATED);

    if (resources->renderer == nullptr)
    {
        std::cout << "SDL couldn´t create the renderer, SDL_Error:\n";
        std::cout << SDL_GetError();
        return -1;  // No se pudo crear el renderer
    }

    // Elegimos el color para el "pincel" en formato RGB
    SDL_SetRenderDrawColor(resources->renderer, 0, 0, 0, 255);

    // Actualizamos el renderer
    SDL_RenderClear(resources->renderer);

    return 1;   // Se creo el renderer correctamente
}

int load_font(SDLResources *resources) 
{

    resources->font = TTF_OpenFont("arial.ttf", font_size);

    if (!resources->font) 
    {
        std::cout << "Error loading font\n";
        return -1;
    }

    return 0;
}

// Creacion de la interfaz
int game_init(SDLResources* resources)
{
    resources->renderer = nullptr;

    resources->window = nullptr;

    if (init() < 0)
        return -1;  


    if(createWindow(resources) < 0)
    {
        SDL_cleanup(resources);
        return -1;
    }


    if (createRenderer(resources) < 0)
    {
        SDL_cleanup(resources);
        return -1;
    }

    if (load_font(resources) != 0) {
    SDL_cleanup(resources);
    return -1;
    }


    return 1;
}
