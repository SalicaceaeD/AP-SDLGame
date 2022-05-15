#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "Ball.h"
#include "Hole.h"
#include "Block.h"
#include "Display.h"
#include "Animation.h"

using namespace std;

void gamePlay(SDL_Window *window, SDL_Renderer *renderer, SDL_Event &event);
char runGame(SDL_Window *window, SDL_Renderer *renderer, SDL_Event &event, int level);

void loadLevel(SDL_Renderer *renderer, int level);
char loadGame(SDL_Window *window, SDL_Renderer *renderer, SDL_Event &event, int level);
void loadPauseScreen(SDL_Window *window, SDL_Renderer *renderer, SDL_Event &event, int level);
char loadWinningScreen(SDL_Window *window, SDL_Renderer *renderer, SDL_Event &event, int level);
char loadGameOverScreen(SDL_Window *window, SDL_Renderer *renderer, SDL_Event &event);
void loadInstruction(SDL_Window *window, SDL_Renderer *renderer, SDL_Event &event);


#endif // GAMEPLAY_H
