#ifndef __BUTTON_HPP__
#define __BUTTON_HPP__

struct SDL_Rect;
struct SDL_Texture;
struct SDL_Renderer;

namespace TicTacToe {

class Button {

public:
    Button(SDL_Renderer *renderer, int x, int y, const char *text);
    ~Button();

    void render();
    
    bool actionPerformed(int x, int y);

private:
    void initTexture(const char *text);

private:
    SDL_Renderer *renderer;

    SDL_Rect *rect;
    SDL_Rect *rect2;
    SDL_Texture *texture;
};

} // namespace TicTacToe

#endif