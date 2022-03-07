#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>

#include "SDL_utils.h"
#include "Tool.h"
#include "Ball.h"
#include "Entity.h"
#include "Hole.h"

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const char* WINDOW_TITLE = "Mini-Golf game";

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event event;

Ball golfBall;
Entity background;
Hole hole;

bool gamerunning = true;
bool mouseDown = false;

void game(){
    bool mousePressed = false;
    while (SDL_PollEvent(&event)){
        switch (event.type){
            case SDL_QUIT:{
                gamerunning = false;
                break;
            }
            case SDL_MOUSEBUTTONDOWN:{
                mouseDown = true;
                mousePressed = true;
                break;
            }
            case SDL_MOUSEBUTTONUP:{
                mouseDown = false;
                break;
            }
        }
    }
    bool win = golfBall.update(mousePressed, mouseDown, hole);
    SDL_RenderClear(renderer);
    background.showTexture(renderer);
    hole.showTexture(renderer);
    if (!win) golfBall.showTexture(renderer);
    SDL_RenderPresent(renderer);
    if (win){
        SDL_Delay(1000);
        gamerunning = false;
    }
}
void loadLevel(){
    float x = 0, y = 0;
    FILE* F = fopen("data.inp", "r");
    fscanf(F, "%f %f", &x, &y);
    golfBall.init({x, y});
    fscanf(F, "%f %f", &x, &y);
    hole.setPos(x, y);
    fclose(F);
}
int main(int argc, char* argv[])
{
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

    ///
    golfBall.initTexture(renderer);

    background.path = "assets/img/background.png";
    background.setPos(0, 0);
    background.initTexture(renderer);

    hole.initTexture(renderer);

    Entity playButton;
    playButton.path = "assets/img/play-button.png";
    playButton.initTexture(renderer);
    playButton.setPos(250,350);
    gamerunning = true;
    while (true) {
        while (SDL_PollEvent(&event)){
            switch (event.type){
            case SDL_QUIT:{
                goto QUIT;
                //return 0;
                break;
            }
            case SDL_MOUSEBUTTONDOWN:{
                int mouseX = 0, mouseY = 0;
                SDL_GetMouseState(&mouseX, &mouseY);
                if (playButton.checkClick({mouseX, mouseY})){
                    gamerunning = true;
                    loadLevel();
                    while (gamerunning){game();}
                }
                break;
            }
            default:
                background.showTexture(renderer);
                playButton.showTexture(renderer);
                SDL_RenderPresent(renderer);
            }
        }
        //game();
    }

    QUIT:
        quitSDL(window, renderer);
    return 0;
}

