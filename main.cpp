#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "SDL_utils.h"
#include "Ball.h"
#include "Hole.h"
#include "GamePlay.h"
#include "Button.h"

using namespace std;

const int SCREEN_WIDTH = 700;
const int SCREEN_HEIGHT = 600;
const char* WINDOW_TITLE = "Mini-Golf game";

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event event;

TTF_Font *font = TTF_OpenFont("assets/font/font.tff", 32);
SDL_Color white = {255, 255, 255};
void test(){
    string mes = "Hello";
    Entity text;
    text.initTexture(renderer, font, mes.c_str(), white);
    text.showTexture(renderer);
}

int main(int argc, char* argv[])
{
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    test();

    Entity background;
    background.path = "assets/img/background.png";
    background.setPos(0, 0);
    background.initTexture(renderer);

    Button playButton('p');
    playButton.initTexture(renderer);
    playButton.setCenter('w', 280);

    Button soundButton('s');
    soundButton.initTexture(renderer);
    soundButton.setCenter('w', 380);

    Button quitButton('q');
    quitButton.initTexture(renderer);
    quitButton.setCenter('w', 480);

    while (true) {
        while (SDL_PollEvent(&event)){
            switch (event.type){
            case SDL_QUIT:{
                goto QUIT;
                //return 0;
                break;
            }
            case SDL_MOUSEBUTTONDOWN:{
                Vector2f curMousePos = getMouse();
                if (playButton.checkClick(curMousePos)){
                    gamePlay(renderer, event);
                }
                if (quitButton.checkClick(curMousePos)){
                    goto QUIT;
                }
                break;
            }
            }
        }
        background.showTexture(renderer);
        playButton.showTexture(renderer);
        soundButton.showTexture(renderer);
        quitButton.showTexture(renderer);
        SDL_RenderPresent(renderer);
        //game();
    }

    QUIT:
        background.destroyTexture();
        playButton.destroyTexture();
        soundButton.destroyTexture();
        quitButton.destroyTexture();
        quitSDL(window, renderer);
    return 0;
}
