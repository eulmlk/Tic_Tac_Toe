#include "Button.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

TicTacToe::Button::Button(SDL_Renderer *renderer, int x, int y, const char *text) {
    this->renderer = renderer;
    this->rect = new SDL_Rect({x, y, 235, 75});

    initTexture(text);

    int width = strlen(text) * 20 + 5;
    int offset = (235 - width) / 2;
    this->rect2 = new SDL_Rect({x + offset, y + 5, width, 65});
}

TicTacToe::Button::~Button() {
    delete rect;
    delete rect2;

    SDL_DestroyTexture(texture);
}

void TicTacToe::Button::render() {
    if (SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255))
        SDL_Log("Error Setting Draw Color for Renderer: %s", SDL_GetError());

    if (SDL_RenderFillRect(renderer, rect))
        SDL_Log("Error Drawing Button: %s", SDL_GetError());

    if (SDL_RenderCopy(renderer, texture, nullptr, rect2))
        SDL_Log("Error Drawing Button's Label: %s", SDL_GetError());
}

bool TicTacToe::Button::actionPerformed(int x, int y) {
    if (rect->x > x || rect->x + rect->w < x)
        return false;

    if (rect->y > y || rect->y + rect->h < y)
        return false;

    return true;
}

void TicTacToe::Button::initTexture(const char *text) {
    TTF_Font *font = TTF_OpenFont("assets/RobotoMono-Bold.ttf", 60);

    if (font == nullptr) {
        SDL_Log("Error loading font: %s", TTF_GetError());
        return;
    }

    SDL_Surface *surface = TTF_RenderText_Blended(font, text, {255, 255, 0, 255});

    texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
}
