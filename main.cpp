#include "SDL_utils.h"
#include "GamePlay.h"
#include "Display.h"

using namespace std;

const int SCREEN_WIDTH = 700;
const int SCREEN_HEIGHT = 600;
const char* WINDOW_TITLE = "Mini-Golf game";

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event event;

int main(int argc, char* argv[])
{
    initLib();
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, (Uint8)0, (Uint8)0, (Uint8)0, (Uint8)128);

    initSound();
    HomeScreen::init(renderer);
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&event)){
            switch (event.type){
            case SDL_QUIT:{
                running = false;
                break;
            }
            case SDL_MOUSEBUTTONDOWN:{
                char pressed = HomeScreen::handle();
                if (pressed == 'p'){
                    HomeScreen::destroy();
                    gamePlay(renderer, event);
                    HomeScreen::build(renderer);
                }
                if (pressed == 'q'){
                    running = false;
                }
                break;
            }
            }
        }
        HomeScreen::display(renderer);
    }

    quitSound();
    HomeScreen::destroy();
    quitSDL(window, renderer);
    return 0;
}
