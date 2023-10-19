#ifndef __CPU_PLAYER_HPP__
#define __CPU_PLAYER_HPP__

#include "Globals.hpp"
#include <cstdlib>

namespace TicTacToe {

class CPUPlayer {

    struct move {
        int moveIndex;
        move *next;
    };

    struct moveEvalPair {
        int eval;
        int moveIndex;
    };

public:
    static inline int isGameOver(CellSymbol *board) {
        if (isXWinner(board))
            return SYM_X;

        if (isOWinner(board))
            return SYM_O;

        if (isBoardFull(board))
            return SYM_NONE;

        return -1;
    }

    static inline bool isXWinner(CellSymbol *board) {
        return searchWinIndices(board, SYM_X) && !searchWinIndices(board, SYM_O);
    }

    static inline bool isOWinner(CellSymbol *board) {
        return searchWinIndices(board, SYM_O) && !searchWinIndices(board, SYM_X);
    }

    static inline int getRandomMove(CellSymbol *board) {
        int moves[9], moveCount = 0;

        for (int i = 0; i < 9; i++) {
            if (board[i] == SYM_NONE)
                moves[moveCount++] = i;
        }

        int luckyMove = rand() % moveCount;

        return moves[luckyMove];
    }

    static inline int getSmartMove(CellSymbol *board, CellSymbol turn, int depth) {
        return searchMove(board, turn, depth).moveIndex;
    }

private:
    static inline bool isBoardFull(CellSymbol *board) {
        int count = 0;

        for (int i = 0; i < 9; ++i) {
            if (board[i] != SYM_NONE)
                ++count;
        }

        return count == 9;
    }

    static inline bool searchWinIndices(CellSymbol *board, CellSymbol key) {
        for (int i = 0; i < 8; ++i) {
            int count = 0;

            for (int j = 0; j < 3; ++j) {
                int index = winIndices[i][j];

                if (board[index] == key)
                    ++count;
            }

            if (count == 3)
                return true;
        }

        return false;
    }

    static inline move *generateMoves(CellSymbol *board) {
        move *head = nullptr;
        move *tail = nullptr;

        int indices[9];

        for (int i = 0; i < 9; ++i) {
            bool expression;
            do {
                indices[i] = rand() % 9;

                expression = false;
                for (int j = 0; j < i; ++j) {
                    expression = expression || (indices[i] == indices[j]);
                }
            } while (expression);
        }

        for (int i = 0; i < 9; i++) {
            int index = indices[i];

            if (board[index] == SYM_NONE) {
                move *curMove = new move({index, nullptr});

                addMove(curMove, head, tail);
            }
        }

        return head;
    }

    static inline void addMove(move *curMove, move *&head, move *&tail) {
        if (head == nullptr) {
            head = tail = curMove;
            return;
        }

        tail->next = curMove;
        tail = curMove;
    }

    static inline void freeMoves(move *head) {
        if (head == nullptr)
            return;

        while (head != nullptr) {
            move *curMove = head;
            head = head->next;

            delete curMove;
        }
    }

    static inline int evaluate(CellSymbol *board) {
        if (isXWinner(board))
            return 1;

        if (isOWinner(board))
            return -1;

        return 0;
    }

    static inline void makeMove(CellSymbol *board, int moveIndex, CellSymbol turn) {
        board[moveIndex] = turn;
    }

    static inline void unmakeMove(CellSymbol *board, int moveIndex) {
        board[moveIndex] = SYM_NONE;
    }

    static inline moveEvalPair searchMove(CellSymbol *board, CellSymbol turn, int depth) {
        if (depth == 0 || isGameOver(board) > -1)
            return {evaluate(board), -1};

        if (turn == SYM_X) {
            int maxScore = -2;
            move *head = generateMoves(board);
            int bestMove = -1;

            while (head != nullptr) {
                makeMove(board, head->moveIndex, turn);

                int eval = searchMove(board, SYM_O, depth - 1).eval;
                if (eval > maxScore) {
                    maxScore = eval;
                    bestMove = head->moveIndex;
                }

                unmakeMove(board, head->moveIndex);

                head = head->next;
            }

            freeMoves(head);

            return {maxScore, bestMove};
        } else if (turn == SYM_O) {
            int minScore = 2;
            move *head = generateMoves(board);
            int bestMove = -1;

            while (head != nullptr) {
                makeMove(board, head->moveIndex, turn);

                int eval = searchMove(board, SYM_X, depth - 1).eval;
                if (eval < minScore) {
                    minScore = eval;
                    bestMove = head->moveIndex;
                }

                unmakeMove(board, head->moveIndex);

                head = head->next;
            }

            freeMoves(head);

            return {minScore, bestMove};
        }

        return {0, -1};
    }

private:
    static inline const int winIndices[8][3] = {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8},
        {0, 3, 6},
        {1, 4, 7},
        {2, 5, 8},
        {0, 4, 8},
        {2, 4, 6}};
};

} // namespace TicTacToe

#endif