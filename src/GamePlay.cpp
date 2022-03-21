#include "GamePlay.h"

Entity levelMap;
Ball golfBall;
Hole hole;
Block blocks;
Button menuButton('m');
void gamePlay(SDL_Renderer *renderer, SDL_Event &event){
    golfBall.initTexture(renderer);
    hole.initTexture(renderer);
    menuButton.initTexture(renderer);
    menuButton.setPos(0, 0);

    LevelScreen::init(renderer);
    int opt = 0;
    bool playing = true;
    while (playing){
        if (opt < 0) playing = false;
        if (opt > 0){
            char pressed = runGame(renderer, event, opt);
            if (pressed == 'N') ++opt;
            else if (pressed != 'a') opt = 0;
        }
        if (opt == 0){
            while (SDL_PollEvent(&event)){
                switch (event.type){
                    case SDL_QUIT:{
                        playing = false;
                        break;
                    }
                    case SDL_MOUSEBUTTONDOWN:{
                        opt = LevelScreen::handle(renderer);
                        break;
                    }
                }
            }
            LevelScreen::display(renderer);
        }
    }

    LevelScreen::destroy();
    golfBall.destroyTexture();
    hole.destroyTexture();
    menuButton.destroyTexture();
}

bool gamerunning = true;
char runGame(SDL_Renderer *renderer, SDL_Event &event, int level){
    loadLevel(renderer, level);
    gamerunning = true;
    while (gamerunning){
        loadGame(renderer, event, level);
    }
    levelMap.destroyTexture();
    return loadWinningScreen(renderer, event);

}

bool mouseDown = false;
void loadGame(SDL_Renderer *renderer, SDL_Event &event, int level){
    bool mousePressed = false;
    while (SDL_PollEvent(&event)){
        switch (event.type){
            case SDL_QUIT:{
                gamerunning = false;
                break;
            }
            case SDL_MOUSEBUTTONDOWN:{
                Vector2f curMousePos = getMouse();
                if (menuButton.checkClick(curMousePos)){
                    loadPauseScreen(renderer, event, level);
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
    menuButton.showTexture(renderer);
    hole.showTexture(renderer);

    if (!win) golfBall.showTexture(renderer);
    SDL_RenderPresent(renderer);
    if (win){
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

void loadPauseScreen(SDL_Renderer *renderer, SDL_Event &event, int level){
    PauseScreen::init(renderer);
    PauseScreen::display(renderer);

    bool pausing = true;
    while (pausing){
        while (SDL_PollEvent(&event)){
            switch (event.type){
                case SDL_QUIT:{
                    pausing = false;
                    break;
                }
                case SDL_MOUSEBUTTONDOWN:{
                    char pressed = PauseScreen::handle();
                    if (pressed != 'n') pausing = false; ///none
                    if (pressed == 'a') loadLevel(renderer, level); ///again
                    if (pressed == 'b') gamerunning = false; ///back
                    break;
                }
            }
        }
    }
    PauseScreen::destroy();
}

char loadWinningScreen(SDL_Renderer *renderer, SDL_Event &event){
    WinningScreen::init(renderer);
    WinningScreen::display(renderer);

    char pressed;
    bool displaying = true;
    while (displaying){
        while (SDL_PollEvent(&event)){
            switch (event.type){
                case SDL_QUIT:{
                    displaying = false;
                    break;
                }
                case SDL_MOUSEBUTTONDOWN:{
                    pressed = WinningScreen::handle();
                    if (pressed != 'n') displaying = false; ///none
                    break;
                }
            }
        }
    }
    WinningScreen::destroy();
    return pressed;
}
