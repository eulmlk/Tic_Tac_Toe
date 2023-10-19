#include "Cell.hpp"
#include <Globals.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

TicTacToe::Cell::Cell(SDL_Renderer *renderer, int index) {
    this->renderer = renderer;

    initRect(index);

    value = SYM_NONE;

    initFonts();
}

TicTacToe::Cell::~Cell() {
    delete rect;
    delete rect2;

    SDL_DestroyTexture(textO);
    SDL_DestroyTexture(textX);
}

void TicTacToe::Cell::render() {
    if (SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255))
        SDL_Log("Error Setting Draw Color for Renderer: %s", SDL_GetError());

    if (SDL_RenderFillRect(renderer, rect))
        SDL_Log("Error Drawing Cell at (%i, %i): %s", rect->x, rect->y, SDL_GetError());

    int success = 0;

    if (value == SYM_X)
        success = SDL_RenderCopy(renderer, textX, nullptr, rect2);
    else if (value == SYM_O)
        success = SDL_RenderCopy(renderer, textO, nullptr, rect2);

    if (success)
        SDL_Log("Error Drawing X/O at (%i, %i): %s", rect->x, rect->y, SDL_GetError());
}

bool TicTacToe::Cell::handleEvent(int x, int y) {
    if (value != SYM_NONE)
        return false;

    if (rect->x < x && rect->x + 150 > x) {
        if (rect->y < y && rect->y + 150 > y) {
            value = Globals::playerTurn;

            return true;
        }
    }

    return false;
}

void TicTacToe::Cell::setValue(CellSymbol value) {
    this->value = value;
}

void TicTacToe::Cell::initRect(int index) {
    int xoff = index % 3;
    int yoff = index / 3;

    rect = new SDL_Rect({350, 50, 150, 150});

    rect->x += xoff * 175;
    rect->y += yoff * 175;

    rect2 = new SDL_Rect({rect->x + 20, rect->y + 10, 110, 130});
}

void TicTacToe::Cell::initFonts() {
    TTF_Font *font = TTF_OpenFont("assets/Roboto-Black.ttf", 130);

    if (font == nullptr) {
        SDL_Log("Error loading font: %s", TTF_GetError());
        return;
    }

    SDL_Surface *surfaceO = TTF_RenderText_Blended(font, "O", {0, 0, 0, 255});
    SDL_Surface *surfaceX = TTF_RenderText_Blended(font, "X", {0, 0, 0, 255});

    textO = SDL_CreateTextureFromSurface(renderer, surfaceO);
    textX = SDL_CreateTextureFromSurface(renderer, surfaceX);

    SDL_FreeSurface(surfaceO);
    SDL_FreeSurface(surfaceX);

    TTF_CloseFont(font);
}
