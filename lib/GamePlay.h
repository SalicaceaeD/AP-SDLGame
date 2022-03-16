#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "Ball.h"
#include "Hole.h"
#include "Block.h"
#include "Button.h"

using namespace std;

void gamePlay(SDL_Renderer *renderer, SDL_Event &event);
void loadLevel(SDL_Renderer *renderer, int level);
void play(SDL_Renderer *renderer, SDL_Event &event);
void runGame(SDL_Renderer *renderer, SDL_Event &event, int level);

#endif // GAMEPLAY_H
