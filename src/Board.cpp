#include "Board.hpp"
#include "CPUPlayer.hpp"
#include "Cell.hpp"
#include <SDL2/SDL.h>

TicTacToe::Board::Board(SDL_Renderer *renderer) {
    this->renderer = renderer;

    rect = new SDL_Rect({350, 50, 500, 500});

    cells = new Cell *[9];

    for (int i = 0; i < 9; ++i) {
        cells[i] = new Cell(renderer, i);
    }

    initBoard();
}

TicTacToe::Board::~Board() {
    for (int i = 0; i < 9; ++i) {
        delete cells[i];
    }

    delete[] cells;
    delete rect;
}

void TicTacToe::Board::initBoard() {
    for (int i = 0; i < 9; ++i) {
        cellValues[i] = SYM_NONE;
        cells[i]->setValue(SYM_NONE);
    }
}

int TicTacToe::Board::isGameOver() {
    return CPUPlayer::isGameOver(cellValues);
}

void TicTacToe::Board::makeMove(int moveIndex) {
    cellValues[moveIndex] = Globals::playerTurn;

    Globals::playerTurn = Globals::playerTurn == SYM_X ? SYM_O : SYM_X;
}

void TicTacToe::Board::makeCPUMove() {
    int moveIndex = -1;
    if (Globals::difficulty == DF_EASY) {
        moveIndex = CPUPlayer::getRandomMove(cellValues);
    } else if (Globals::difficulty == DF_MEDIUM) {
        moveIndex = CPUPlayer::getSmartMove(cellValues, Globals::playerTurn, 2);
    } else if (Globals::difficulty == DF_HARD) {
        moveIndex = CPUPlayer::getSmartMove(cellValues, Globals::playerTurn, -1);
    }

    cellValues[moveIndex] = Globals::playerTurn;
    cells[moveIndex]->setValue(Globals::playerTurn);

    Globals::playerTurn = Globals::playerTurn == SYM_X ? SYM_O : SYM_X;
}

void TicTacToe::Board::render() {
    if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255))
        SDL_Log("Error Setting Draw Color for Renderer: %s", SDL_GetError());

    if (SDL_RenderFillRect(renderer, rect))
        SDL_Log("Error Drawing Board: %s", SDL_GetError());

    for (int i = 0; i < 9; ++i) {
        cells[i]->render();
    }
}

void TicTacToe::Board::handleEvent(int x, int y) {
    if (Globals::playerTurn == SYM_NONE)
        return;

    if (Globals::playAs != Globals::playerTurn && !Globals::isTwoPlayersMode)
        return;

    bool isMoveMade = false;

    for (int i = 0; i < 9; ++i) {
        if (cells[i]->handleEvent(x, y)) {
            makeMove(i);
            isMoveMade = true;
            break;
        }
    }

    int winner = isGameOver();
    if (winner > -1) {
        Globals::isDraw = winner == SYM_NONE;
        Globals::winner = (CellSymbol)winner;
        Globals::playerTurn = SYM_NONE;
        Globals::isPlaying = false;
        return;
    }

    if (!Globals::isTwoPlayersMode && isMoveMade)
        makeCPUMove();

    winner = isGameOver();
    if (winner > -1) {
        Globals::isDraw = winner == SYM_NONE;
        Globals::winner = (CellSymbol)winner;
        Globals::playerTurn = SYM_NONE;
        Globals::isPlaying = false;
        return;
    }
}
