#include "MainWindow.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>

using namespace TicTacToe;

int main() {
    system("clear");
    srand(time(0) + clock());

    if (SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    if (TTF_Init()) {
        SDL_Log("Failed to initialize SDL_TTF: %s", SDL_GetError());
        return 1;
    }

    MainWindow window;

    window.run();

    TTF_Quit();

    SDL_Quit();

    return 0;
}