#ifndef SDLINIT_H
#define SDLINIT_H
#include <iostream>
#include <SDL.h>

using namespace std;

void logSDLError(std::ostream& os, const std::string &msg, bool fatal = false);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer,
             const string WINDOW_TITLE, const int SCREEN_WIDTH, const int SCREEN_HEIGHT);

void waitUntilKeyPressed();

#endif // SDLINIT_H
