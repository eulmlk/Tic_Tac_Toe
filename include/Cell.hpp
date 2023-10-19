#ifndef __CELL_HPP__
#define __CELL_HPP__

#include "Globals.hpp"

struct SDL_Renderer;
struct SDL_Rect;
struct SDL_Texture;

namespace TicTacToe {

class Cell {

public:
    Cell(SDL_Renderer *renderer, int index);
    ~Cell();

    void render();
    bool handleEvent(int x, int y);

    void setValue(CellSymbol value);

private:
    void initRect(int index);
    void initFonts();

private:
    SDL_Renderer *renderer;
    SDL_Rect *rect;
    SDL_Rect *rect2;

    CellSymbol value;

    SDL_Texture *textO;
    SDL_Texture *textX;
};

} // namespace TicTacToe

#endif