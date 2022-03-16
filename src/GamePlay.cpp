#include "GamePlay.h"

Entity levelMap;
Ball golfBall;
Hole hole;
Block blocks;
Button xButton('x');
void gamePlay(SDL_Renderer *renderer, SDL_Event &event){
    golfBall.initTexture(renderer);
    hole.initTexture(renderer);

    xButton.initTexture(renderer);
    xButton.setPos(636, 0);

    Button levelButton('l');
    levelButton.initTexture(renderer);
    levelButton.setCenter('w', 300);

    bool playing = true;
    while (playing){
        SDL_RenderClear(renderer);
        while (SDL_PollEvent(&event)){
            switch (event.type){
                case SDL_QUIT:{
                    playing = false;
                    break;
                }
                case SDL_MOUSEBUTTONDOWN:{
                    int mouseX = 0, mouseY = 0;
                    SDL_GetMouseState(&mouseX, &mouseY);
                    Vector2f curMousePos(mouseX, mouseY);
                    if (xButton.checkClick(curMousePos)){
                        playing = false;
                    }
                    if (levelButton.checkClick(curMousePos)){
                        runGame(renderer, event, 1);
                    }
                    break;
                }
            }
        }
        xButton.showTexture(renderer);
        levelButton.showTexture(renderer);
        SDL_RenderPresent(renderer);
    }

    xButton.destroyTexture();
    golfBall.destroyTexture();
    hole.destroyTexture();
}

bool gamerunning = true;
void runGame(SDL_Renderer *renderer, SDL_Event &event, int level){
    loadLevel(renderer, level);
    gamerunning = true;
    while (gamerunning){
        play(renderer, event);
    }
    levelMap.destroyTexture();
}

bool mouseDown = false;
void play(SDL_Renderer *renderer, SDL_Event &event){
    bool mousePressed = false;
    while (SDL_PollEvent(&event)){
        switch (event.type){
            case SDL_QUIT:{
                gamerunning = false;
                break;
            }
            case SDL_MOUSEBUTTONDOWN:{
                Vector2f curMousePos = getMouse();
                if (xButton.checkClick(curMousePos)){
                    gamerunning = false;
                } else {
                    mouseDown = true;
                    mousePressed = true;
                }

                break;
            }
            case SDL_MOUSEBUTTONUP:{
                mouseDown = false;
                break;
            }
        }
    }
    bool win = golfBall.update(mousePressed, mouseDown, hole, blocks);
    SDL_RenderClear(renderer);
    levelMap.showTexture(renderer);
    //blocks.showBlock(renderer);
    hole.showTexture(renderer);
    xButton.showTexture(renderer);
    if (!win) golfBall.showTexture(renderer);
    SDL_RenderPresent(renderer);
    if (win){
        SDL_Delay(1000);
        gamerunning = false;
    }
}

void loadLevel(SDL_Renderer *renderer, int level){
    int x = 0, y = 0;
    string path = "data/"+to_string(level)+"/data.txt";
    FILE* F = fopen(path.c_str(), "r");

    fscanf(F, "%d%d", &x, &y);
    golfBall.init({x, y});

    fscanf(F, "%d%d", &x, &y);
    hole.setPos(x, y);

    int x2 = 0, y2 = 0;
    blocks.reset();
    while (fscanf(F, "%d", &x) != EOF){
        fscanf(F, "%d%d%d", &y, &x2, &y2);
        blocks.add({{x, y}, {x2, y2}});
    }

    levelMap.path = "data/"+to_string(level)+"/map.png";
    levelMap.initTexture(renderer);
    levelMap.setPos(0, 0);
    fclose(F);
}
