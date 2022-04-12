#ifndef DISPLAY_H
#define DISPLAY_H

#include "Entity.h"
#include "Text.h"
//#include "Animation.h"
#include "Sound.h"
#include "SDL_utils.h"

void initSound();
void quitSound();

namespace Background{
    void init(SDL_Renderer *renderer);
    void display(SDL_Renderer *renderer);
    void destroy();
}

namespace HomeScreen{
    void init();
    char handle();
    void display(SDL_Renderer *renderer);
    void destroy();
}

namespace OptionScreen{
    void init();
    char handle();
    void resetPage(SDL_Window* window, SDL_Renderer *renderer, SDL_Event &event);
    void display(SDL_Renderer *renderer);
    void destroy();
}

namespace PauseScreen{
    void init(SDL_Renderer *renderer);
    char handle();
    void display(SDL_Renderer *renderer);
    void destroy();
}

namespace WinningScreen{
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

namespace PlayingScreen{
    void init(SDL_Renderer *renderer);
    char handle();
    void display(SDL_Renderer *renderer, int level, int stroke);
    void destroy();
    int getTime();
    void setStartTime();
}
#endif // DISPLAY_H
