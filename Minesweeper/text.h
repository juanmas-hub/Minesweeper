#pragma once
#include <string>
#include "SDL.h"
#include "SDL_ttf.h"

SDL_Color selectSDLColor(int bombsAmount)
{
    SDL_Color color;
    switch (bombsAmount) {
    case 1: color = { 0,   0,  255, 255 }; break; // Azul
    case 2: color = { 0,  128,   0, 255 }; break; // Verde
    case 3: color = { 255,   0,   0, 255 }; break; // Rojo
    case 4: color = { 0,   0, 128, 255 }; break; // Azul oscuro
    case 5: color = { 128,   0,   0, 255 }; break; // Rojo oscuro
    case 6: color = { 0, 128, 128, 255 }; break; // Cyan oscuro
    case 7: color = { 0,   0,   0, 255 }; break; // Negro
    case 8: color = { 128, 128, 128, 255 }; break; // Gris
    default: color = { 0,   0,   0,   0 }; break; // Transparente
    }
    return color;

}

int setTexture(SDLResources *resources, std::string text, SDL_Color color)
{
	resources->textSurface = TTF_RenderText_Solid(resources->font, text.c_str(), color);
    if (!resources->textSurface)
    {
        std::cout << "TTF_RenderText_Solid() failed\n";
        TTF_CloseFont(resources->font);
        TTF_Quit();
        return -1;
    }

    resources->textTexture = SDL_CreateTextureFromSurface(resources->renderer, resources->textSurface);
    SDL_FreeSurface(resources->textSurface);
    if (!resources->textTexture) 
    {
        std::cout << "SDL_CreateTextureFromSurface() failed\n";
        TTF_CloseFont(resources->font);
        TTF_Quit();
        return -1;
    }

    return 1;
}
