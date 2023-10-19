#include "Menu.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

static inline SDL_Color activeColor = {128, 255, 255, 255};
static inline SDL_Color normalColor = {128, 255, 128, 255};

TicTacToe::Menu::Menu(SDL_Renderer *renderer, const char **items, int itemCount, int x, int y) {
    this->renderer = renderer;
    this->itemCount = itemCount;
    this->isVisible = false;
    this->activeItem = -1;

    initRects(x, y);
    initTextures(items);
}

TicTacToe::Menu::~Menu() {
    for (int i = 0; i < itemCount; ++i) {
        delete rects[i];
        delete rects2[i];

        SDL_DestroyTexture(textures[i]);
    }

    delete[] rects;
    delete[] rects2;
    delete[] textures;
}

void TicTacToe::Menu::render() {
    if (!isVisible)
        return;

    for (int i = 0; i < itemCount; i++) {
        SDL_Color color = i == activeItem ? activeColor : normalColor;

        if (SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a))
            SDL_Log("Error Setting Draw Color for Renderer: %s", SDL_GetError());

        if (SDL_RenderFillRect(renderer, rects[i]))
            SDL_Log("Error Drawing Menu: %s", SDL_GetError());

        if (SDL_RenderCopy(renderer, textures[i], nullptr, rects2[i]))
            SDL_Log("Error Drawing Menu Item %i: %s", i + 1, SDL_GetError());
    }

    if (SDL_SetRenderDrawColor(renderer, 32, 32, 32, 255))
        SDL_Log("Error Setting Draw Color for Renderer: %s", SDL_GetError());

    for (int i = 0; i < itemCount; i++) {
        if (SDL_RenderDrawRect(renderer, rects[i]))
            SDL_Log("Error Drawing Menu Borders: %s", SDL_GetError());
    }
}

void TicTacToe::Menu::setActiveItem(int activeItem) {
    this->activeItem = activeItem;
}

void TicTacToe::Menu::setVisible(bool isVisible) {
    this->isVisible = isVisible;
}

void TicTacToe::Menu::toggleVisible() {
    isVisible = !isVisible;
}

int TicTacToe::Menu::actionPerformed(int x, int y) {
    if (!isVisible)
        return -1;

    for (int i = 0; i < itemCount; ++i) {
        if (rects[i]->x > x || rects[i]->x + rects[i]->w < x)
            continue;

        if (rects[i]->y > y || rects[i]->y + rects[i]->h < y)
            continue;

        return i;
    }

    return -1;
}

void TicTacToe::Menu::initRects(int x, int y) {
    this->rects = new SDL_Rect *[itemCount];
    this->rects2 = new SDL_Rect *[itemCount];

    for (int i = 0; i < itemCount; i++) {
        rects[i] = new SDL_Rect({x, y - (40 * i), 175, 40});
    }
}

void TicTacToe::Menu::initTextures(const char **items) {
    TTF_Font *font = TTF_OpenFont("assets/RobotoMono-Bold.ttf", 30);

    textures = new SDL_Texture *[itemCount];

    if (font == nullptr) {
        SDL_Log("Error loading font: %s", TTF_GetError());
        return;
    }

    for (int i = 0; i < itemCount; ++i) {
        SDL_Surface *surface = TTF_RenderText_Blended(font, items[i], {255, 0, 0, 255});

        textures[i] = SDL_CreateTextureFromSurface(renderer, surface);

        SDL_FreeSurface(surface);

        int width = strlen(items[i]) * 16 + 5;
        int offset = (175 - width) / 2;

        rects2[i] = new SDL_Rect({rects[i]->x + offset, rects[i]->y + 5, width, 30});
    }

    TTF_CloseFont(font);
}
