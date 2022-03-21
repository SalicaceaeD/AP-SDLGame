#ifndef DISPLAY_H
#define DISPLAY_H

#include "Button.h"
#include "Sound.h"

void initSound();
void quitSound();

namespace HomeScreen{
    void build(SDL_Renderer *renderer);
    void init(SDL_Renderer *renderer);
    char handle();
    void display(SDL_Renderer *renderer);
    void destroy();
}

namespace PauseScreen{
    void init(SDL_Renderer *renderer);
    char handle();
    void display(SDL_Renderer *renderer);
    void destroy();
}

namespace LevelScreen{
    void init(SDL_Renderer *renderer);
    int handle(SDL_Renderer *renderer);
    void display(SDL_Renderer *renderer);
    void destroy();
}

namespace WinningScreen{
    void init(SDL_Renderer *renderer);
    char handle();
    void display(SDL_Renderer *renderer);
    void destroy();
}
#endif // DISPLAY_H
