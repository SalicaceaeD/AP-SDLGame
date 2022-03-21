#ifndef SDL_UTILS_H
#define SDL_UTILS_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal);

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer,
	const int screenWidth, const int screenHeight, const char* windowTitle) ;

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void waitUntilKeyPressed();

void initLib();

#endif // SDL_UTILS_H
