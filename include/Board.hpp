#ifndef __BOARD_HPP__
#define __BOARD_HPP__

#include "Globals.hpp"

struct SDL_Renderer;
class GlobalValues;
struct SDL_Rect;

namespace TicTacToe {

class Cell;

class Board {
public:
    Board(SDL_Renderer *renderer);
    ~Board();

    void initBoard();
    int isGameOver();

    void render();
    void handleEvent(int x, int y);

    void makeCPUMove();

private:
    void makeMove(int moveIndex);

private:
    SDL_Renderer *renderer;
    CellSymbol cellValues[9];

    Cell **cells;
    SDL_Rect *rect;
};

} // namespace TicTacToe

#endif