#ifndef __MENU_HPP__
#define __MENU_HPP__

struct SDL_Renderer;
struct SDL_Rect;
struct SDL_Texture;

namespace TicTacToe {

class Menu {

public:
    Menu(SDL_Renderer *renderer, const char **items, int itemCount, int x, int y);
    ~Menu();

    void render();
    void setActiveItem(int activeItem);
    void setVisible(bool isVisible);
    void toggleVisible();

    int actionPerformed(int x, int y);

private:
    void initRects(int x, int y);
    void initTextures(const char **items);

private:
    SDL_Renderer *renderer;

    SDL_Rect **rects;
    SDL_Rect **rects2;

    int itemCount;
    int activeItem;

    SDL_Texture **textures;

    bool isVisible;
};

} // namespace TicTacToe

#endif