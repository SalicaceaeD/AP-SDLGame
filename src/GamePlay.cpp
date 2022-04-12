#include "GamePlay.h"

Entity levelMap;
Ball golfBall;
Hole hole;
Block blocks;

SoundEffect swing;

void gamePlay(SDL_Window *window, SDL_Renderer *renderer, SDL_Event &event){
    golfBall.initTexture(renderer);
    hole.initTexture(renderer);

    int opt = 0;
    bool playing = true;
    while (playing){
        if (opt < 0) playing = false;
        if (opt > 0){
            LevelScreen::destroy();
            char pressed = runGame(window, renderer, event, opt);
            if (pressed == 'N') ++opt;
            else if (pressed != 'a') opt = 0;
        }
        if (opt == 0){
            LevelScreen::init(renderer);
            while (SDL_PollEvent(&event)){
                switch (event.type){
                    case SDL_QUIT:{
                        quitSDL(window, renderer);
                        exit(0);
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
}

bool gamerunning = true;
int stroke = 0;
char runGame(SDL_Window *window, SDL_Renderer *renderer, SDL_Event &event, int level){
    swing.loadSE("assets/sfx/swing.mp3");
    loadLevel(renderer, level);
    PlayingScreen::init(renderer);

    gamerunning = true;
    bool win = false;
    while (gamerunning){
        win = loadGame(window, renderer, event, level);
    }

    levelMap.destroyTexture();
    PlayingScreen::destroy();
    swing.freeSE();
    if (win) return loadWinningScreen(window, renderer, event, level);
    return 'b';
}

bool mouseDown = false;
bool loadGame(SDL_Window *window, SDL_Renderer *renderer, SDL_Event &event, int level){
    bool mousePressed = false;
    while (SDL_PollEvent(&event)){
        switch (event.type){
            case SDL_QUIT:{
                quitSDL(window, renderer);
                exit(0);
                break;
            }
            case SDL_MOUSEBUTTONDOWN:{
                char pressed = PlayingScreen::handle();
                if (pressed != 'n'){
                    if (pressed == 'p') loadPauseScreen(window, renderer, event, level);
                    if (pressed == 'a') loadLevel(renderer, level);
                } else {
                    mouseDown = true;
                    mousePressed = true;
                }
                break;
            }
            case SDL_MOUSEBUTTONUP:{
                if (golfBall.increaseStroke()){
                    ++stroke;
                    swing.play();
                }
                mouseDown = false;
                break;
            }
        }
    }

    SDL_RenderClear(renderer);
    levelMap.showTexture(renderer);
    hole.showTexture(renderer);
    PlayingScreen::display(renderer, level, stroke);

    bool win = golfBall.update(renderer, mousePressed, mouseDown, hole, blocks);
    if (!win) golfBall.showTexture(renderer);
    SDL_RenderPresent(renderer);
    if (win){
        gamerunning = false;
    }
    return win;
}

void loadLevel(SDL_Renderer *renderer, int level){
    stroke = 0;
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

void loadPauseScreen(SDL_Window *window, SDL_Renderer *renderer, SDL_Event &event, int level){
    PauseScreen::init(renderer);
    PauseScreen::display(renderer);

    bool pausing = true;
    while (pausing){
        while (SDL_PollEvent(&event)){
            switch (event.type){
                case SDL_QUIT:{
                    quitSDL(window, renderer);
                    exit(0);
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
    PlayingScreen::setStartTime();
}

char loadWinningScreen(SDL_Window *window, SDL_Renderer *renderer, SDL_Event &event, int level){
    if (stroke == 1){
        Text hio("HOLE IN ONE !", 40, 0);
        hio.setPos(200, 280);
        hio.showTexture(renderer);
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
        hio.~Entity();
    }

    int _time = PlayingScreen::getTime();
    WinningScreen::init(renderer);
    WinningScreen::display(renderer);

    char pressed;
    bool displaying = true;
    while (displaying){
        while (SDL_PollEvent(&event)){
            switch (event.type){
                case SDL_QUIT:{
                    quitSDL(window, renderer);
                    exit(0);
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

    string path = "data/"+to_string(level)+"/score.txt";
    FILE *F = fopen(path.c_str(), "r");
    int bestStroke = 0, bestTime = 0;
    fscanf(F, "%d %d", &bestStroke, &bestTime);
    fclose(F);

    F = fopen(path.c_str(), "w");
    if ((!bestStroke || !bestTime) || stroke < bestStroke || (stroke == bestStroke && _time < bestTime))
        fprintf(F, "%d %d", stroke, _time);
    fclose(F);
    return pressed;
}
