#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "Ball.h"
#include "Hole.h"
#include "Block.h"
#include "Display.h"

using namespace std;

void gamePlay(SDL_Renderer *renderer, SDL_Event &event);
void loadLevel(SDL_Renderer *renderer, int level);
void loadGame(SDL_Renderer *renderer, SDL_Event &event, int level);
void loadPauseScreen(SDL_Renderer *renderer, SDL_Event &event, int level);
char loadWinningScreen(SDL_Renderer *renderer, SDL_Event &event);
char runGame(SDL_Renderer *renderer, SDL_Event &event, int level);

#endif // GAMEPLAY_H
