#ifndef __GLOBAL_VALUES_HPP__
#define __GLOBAL_VALUES_HPP__

namespace TicTacToe {

enum Difficulty {
    DF_EASY,
    DF_MEDIUM,
    DF_HARD
};

enum CellSymbol {
    SYM_NONE,
    SYM_X,
    SYM_O
};

class Globals {

public:
    static inline CellSymbol playerTurn = SYM_NONE;
    static inline CellSymbol playAs = SYM_X;
    static inline CellSymbol lastPlayAs = SYM_NONE;
    static inline CellSymbol startAs = SYM_X;
    static inline CellSymbol winner = SYM_NONE;
    static inline bool isTwoPlayersMode = false;
    static inline Difficulty difficulty = DF_EASY;
    static inline bool isDraw = false;
    static inline bool isPlaying = false;
};

} // namespace TicTacToe

#endif