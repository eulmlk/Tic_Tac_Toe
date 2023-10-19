#ifndef __MAIN_WINDOW_HPP__
#define __MAIN_WINDOW_HPP__

struct SDL_Renderer;
struct SDL_Window;

namespace TicTacToe {

class Board;
class Button;
class Menu;

class MainWindow {

public:
    MainWindow();
    ~MainWindow();

    void run();

private:
    void render();
    void renderStatusText();
    void handleEvent(int x, int y);

    void createButtons();

    void handleButtonEvents(int x, int y);
    bool handleMenuEvents(int x, int y);

private:
    SDL_Renderer *renderer;
    SDL_Window *window;

    Board *board;

    Button *playerModeButton;
    Button *difficultyButton;
    Button *playAsButton;
    Button *startAsButton;
    Button *newGameButton;

    Menu *playerModeMenu;
    Menu *difficultyMenu;
    Menu *playAsMenu;
    Menu *startAsMenu;

    char *statusText;
};

} // namespace TicTacToe

#endif