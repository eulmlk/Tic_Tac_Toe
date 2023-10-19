#include "MainWindow.hpp"
#include "Board.hpp"
#include "Button.hpp"
#include "Globals.hpp"
#include "Menu.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

using namespace TicTacToe;

static inline const char *playerModeItems[] = {"One Player", "Two Player"};
static inline const char *difficultyItems[] = {"Easy", "Medium", "Hard"};
static inline const char *playAsItems[] = {"- X -", "- O -"};

static inline const char *statusTexts[] = {"Welcome!!", "X's Turn!!", "O's Turn!!", "X Wins!!",
                                           "O Wins!!", "Draw!!", "You Win!!", "You Lose!!"};

MainWindow::MainWindow() {
    window = SDL_CreateWindow("Tic Tac Toe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 675, 0);

    if (window == nullptr)
        SDL_Log("Error Creating Window: %s", SDL_GetError());
    else
        SDL_Log("Window Created Successfully!!");

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == nullptr)
        SDL_Log("Error Creating Renderer: %s", SDL_GetError());
    else
        SDL_Log("Renderer Created Successfully!!");

    board = new Board(renderer);

    createButtons();

    statusText = (char *)statusTexts[0];
}

MainWindow::~MainWindow() {
    delete board;

    delete playAsButton;
    delete startAsButton;
    delete playerModeButton;
    delete difficultyButton;
    delete newGameButton;

    delete playerModeMenu;
    delete difficultyMenu;
    delete playAsMenu;
    delete startAsMenu;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void TicTacToe::MainWindow::render() {
    if (SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255))
        SDL_Log("Error Setting Draw Color for Renderer: %s", SDL_GetError());

    if (SDL_RenderClear(renderer))
        SDL_Log("Error Clearing Render: %s", SDL_GetError());

    board->render();

    playerModeButton->render();
    difficultyButton->render();
    playAsButton->render();
    startAsButton->render();
    newGameButton->render();

    int playerModeActive = Globals::isTwoPlayersMode;
    int difficultyActive = Globals::difficulty;
    int playAsActive = Globals::playAs - 1;
    int startAsActive = Globals::startAs - 1;

    playerModeMenu->setActiveItem(playerModeActive);
    playerModeMenu->render();

    difficultyMenu->setActiveItem(difficultyActive);
    difficultyMenu->render();

    playAsMenu->setActiveItem(playAsActive);
    playAsMenu->render();

    startAsMenu->setActiveItem(startAsActive);
    startAsMenu->render();

    renderStatusText();

    SDL_RenderPresent(renderer);
}

void TicTacToe::MainWindow::renderStatusText() {
    if (Globals::isPlaying) {
        statusText = (char *)statusTexts[Globals::playerTurn];
    } else if (Globals::winner != SYM_NONE) {
        if (Globals::isTwoPlayersMode) {
            statusText = (char *)statusTexts[Globals::winner + 2];
        } else if (Globals::lastPlayAs == SYM_NONE) {
            Globals::lastPlayAs = Globals::playAs;
            statusText = (char *)(Globals::lastPlayAs == Globals::winner ? statusTexts[6] : statusTexts[7]);
        }
    } else if (Globals::isDraw) {
        statusText = (char *)statusTexts[5];
    }

    TTF_Font *font = TTF_OpenFont("assets/RobotoMono-Bold.ttf", 60);

    if (font == nullptr) {
        SDL_Log("Error loading font: %s", TTF_GetError());
        return;
    }

    SDL_Surface *surface = TTF_RenderText_Blended(font, statusText, {0, 0, 0, 255});
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    int width = strlen(statusText) * 45;
    int offset = (500 - width) / 2;

    SDL_Rect statusRect = {350 + offset, 575, width, 75};

    if (SDL_RenderCopy(renderer, texture, nullptr, &statusRect))
        SDL_Log("Error Rendering Text: %s", SDL_GetError());

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
}

void TicTacToe::MainWindow::handleEvent(int x, int y) {
    board->handleEvent(x, y);

    if (Globals::playerTurn != SYM_NONE)
        return;

    if (handleMenuEvents(x, y))
        return;

    handleButtonEvents(x, y);
}

void TicTacToe::MainWindow::createButtons() {
    playerModeButton = new Button(renderer, 60, 295, "Player Mode");
    difficultyButton = new Button(renderer, 60, 525, "Difficulty");
    playAsButton = new Button(renderer, 905, 175, "Play As");
    startAsButton = new Button(renderer, 905, 350, "Start As");
    newGameButton = new Button(renderer, 905, 525, "New Game");

    playerModeMenu = new Menu(renderer, playerModeItems, 2, 90, 255);
    difficultyMenu = new Menu(renderer, difficultyItems, 3, 90, 485);
    playAsMenu = new Menu(renderer, playAsItems, 2, 935, 135);
    startAsMenu = new Menu(renderer, playAsItems, 2, 935, 310);
}

void TicTacToe::MainWindow::handleButtonEvents(int x, int y) {
    if (playerModeButton->actionPerformed(x, y)) {
        playerModeMenu->toggleVisible();

        difficultyMenu->setVisible(false);
        playAsMenu->setVisible(false);
        startAsMenu->setVisible(false);
        return;
    }

    if (difficultyButton->actionPerformed(x, y)) {
        difficultyMenu->toggleVisible();

        playerModeMenu->setVisible(false);
        playAsMenu->setVisible(false);
        startAsMenu->setVisible(false);
        return;
    }

    if (playAsButton->actionPerformed(x, y)) {
        playAsMenu->toggleVisible();

        playerModeMenu->setVisible(false);
        difficultyMenu->setVisible(false);
        startAsMenu->setVisible(false);
        return;
    }

    if (startAsButton->actionPerformed(x, y)) {
        startAsMenu->toggleVisible();

        playerModeMenu->setVisible(false);
        difficultyMenu->setVisible(false);
        playAsMenu->setVisible(false);
        return;
    }

    playerModeMenu->setVisible(false);
    difficultyMenu->setVisible(false);
    playAsMenu->setVisible(false);
    startAsMenu->setVisible(false);

    if (newGameButton->actionPerformed(x, y)) {
        board->initBoard();

        Globals::playerTurn = Globals::startAs;
        Globals::isPlaying = true;
        Globals::lastPlayAs = SYM_NONE;

        if (Globals::startAs != Globals::playAs && !Globals::isTwoPlayersMode)
            board->makeCPUMove();
    }
}

bool TicTacToe::MainWindow::handleMenuEvents(int x, int y) {
    int playerModeAction = playerModeMenu->actionPerformed(x, y);
    if (playerModeAction > -1) {
        Globals::isTwoPlayersMode = playerModeAction == 1;
        return true;
    }

    int difficultyAction = difficultyMenu->actionPerformed(x, y);
    if (difficultyAction > -1) {
        Globals::difficulty = (Difficulty)difficultyAction;
        return true;
    }

    int playAsAction = playAsMenu->actionPerformed(x, y);
    if (playAsAction > -1) {
        Globals::playAs = (CellSymbol)(playAsAction + 1);
        return true;
    }

    int startAsAction = startAsMenu->actionPerformed(x, y);
    if (startAsAction > -1) {
        Globals::startAs = (CellSymbol)(startAsAction + 1);
        return true;
    }

    return false;
}

void TicTacToe::MainWindow::run() {
    SDL_Event event;
    bool isRunning = true;

    while (isRunning) {
        SDL_Delay(40);
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    int x, y;
                    SDL_GetMouseState(&x, &y);

                    handleEvent(x, y);
                }
            }
        }

        render();
    }
}
