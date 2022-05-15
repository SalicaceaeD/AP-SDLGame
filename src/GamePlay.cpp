#include "GamePlay.h"

Entity levelMap;
Ball golfBall;
Hole hole;
Animation flag("assets/img/flag.png", 8);

void gamePlay(SDL_Window *window, SDL_Renderer *renderer, SDL_Event &event){
    hole.initTexture(renderer);
    flag.initTexture(renderer);
    flag.setSize(23, 46);

    int opt = 0;
    bool playing = true;
    while (playing){
        if (opt == -1) playing = false;
        if (opt == -2) {
            loadInstruction(window, renderer, event);
            opt = 0;
        }
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
    hole.destroyTexture();
    flag.destroyTexture();
}

bool gamerunning = true;
int stroke = 0;
int _time = 0;
SoundEffect swing;
SoundEffect inHole;
SoundEffect inWater;
char runGame(SDL_Window *window, SDL_Renderer *renderer, SDL_Event &event, int level){
    swing.loadSE("assets/sfx/swing.mp3");
    inHole.loadSE("assets/sfx/hole.mp3");
    inWater.loadSE("assets/sfx/water.mp3");

    loadLevel(renderer, level);
    PlayingScreen::init(renderer);
    Pyramid::init(renderer);
    Lock::init(renderer);

    gamerunning = true;
    char win = '0';
    while (gamerunning){
        win = loadGame(window, renderer, event, level);
    }
    _time = PlayingScreen::getTime();

    if (win == 'w') inHole.play();
    if (win == 'l') inWater.play();
    if (win != '0') for (int t=8; t; --t){
        golfBall.resizeRect(-1);
        levelMap.showTexture(renderer);
        hole.showTexture(renderer);
        if (win == 'w'){
            Vector2f ballPos = golfBall.getPos();
            Vector2f holePos = hole.getPos();
            holePos = holePos + Vector2f(6, 6);
            if (ballPos.x > holePos.x) golfBall.addX(-2);
            if (ballPos.x < holePos.x) golfBall.addX(2);
            if (ballPos.y > holePos.y) golfBall.addY(-2);
            if (ballPos.y < holePos.y) golfBall.addY(2);
        }
        golfBall.showTexture(renderer);
        SDL_RenderPresent(renderer);
        SDL_Delay(50);
    }
    levelMap.showTexture(renderer);
    hole.showTexture(renderer);
    SDL_RenderPresent(renderer);
    SDL_Delay(100);

    golfBall.destroyTexture();
    levelMap.destroyTexture();
    PlayingScreen::destroy();
    Pyramid::destroy();
    Lock::destroy();

    swing.freeSE();
    inHole.freeSE();
    inWater.freeSE();

    if (win == 'w') return loadWinningScreen(window, renderer, event, level);
    if (win == 'l') return loadGameOverScreen(window, renderer, event);
    return 'b';
}

bool mouseDown = false;
char loadGame(SDL_Window *window, SDL_Renderer *renderer, SDL_Event &event, int level){
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
    if (!Lock::display(renderer)) flag.showTexture(renderer);
    PlayingScreen::display(renderer, level, stroke);

    char win = golfBall.update(renderer, mousePressed, mouseDown, hole);
    if (win == '0') golfBall.showTexture(renderer);
    Pyramid::display(renderer, golfBall.getPos());
    SDL_RenderPresent(renderer);
    if (win != '0'){
        gamerunning = false;
    }
    return win;
}

void loadLevel(SDL_Renderer *renderer, int level){
    stroke = 0;
    int x = 0, y = 0;
    string path = "data/"+to_string(level)+"/data.txt";
    FILE* F = fopen(path.c_str(), "r");

    golfBall.initTexture(renderer);
    fscanf(F, "%d%d", &x, &y);
    golfBall.init({x, y});

    fscanf(F, "%d%d", &x, &y);
    hole.setPos(x, y);
    flag.setPos(x+8, y-flag.getSize().y+8);

    int x2 = 0, y2 = 0;
    char type;
    blockReset();
    while (fscanf(F, "%c", &type) != EOF){
        if (type == 'p'){
            fscanf(F, "%d%d", &x, &y);
            Pyramid::add({x, y});
        }
        if (type == 'w'){
            fscanf(F, "%d%d%d%d", &x, &y, &x2, &y2);
            Water::add({{x, y}, {x2, y2}});
        }
        if (type == 'b'){
            fscanf(F, "%d%d%d%d", &x, &y, &x2, &y2);
            Block::add({{x, y}, {x2, y2}});
        }
        if (type == 'l'){
            fscanf(F, "%d%d", &x, &y);
            Lock::add({x, y});
            for (int i=0; i<4; ++i){
                fscanf(F, "%d%d%d%d", &x, &y, &x2, &y2);
                Lock::add({{x, y}, {x2, y2}});
            }
        }
        if (type == 'k'){
            int cnt = 0;
            fscanf(F, "%d", &cnt);
            vector<pair<Vector2f,Vector2f>> tmp;
            while (cnt--){
                fscanf(F, "%d%d%d%d", &x, &y, &x2, &y2);
                tmp.push_back({{x, y}, {x2, y2}});
            }
            Lock::add(tmp);
        }
        if (type == 't'){
            fscanf(F, "%d%d%d%d", &x, &y, &x2, &y2);
            Teleport::add({{x, y},{x2, y2}});
        }
    }

    levelMap.path = "data/"+to_string(level)+"/map.png";
    levelMap.initTexture(renderer);
    levelMap.setPos(0, 0);
    fclose(F);
}

void loadPauseScreen(SDL_Window *window, SDL_Renderer *renderer, SDL_Event &event, int level){
    PauseScreen::init(renderer);

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
                    if (pressed == 'b') gamerunning = false; ///back
                    break;
                }
            }
        }
        PauseScreen::display(renderer);
    }
    PauseScreen::destroy();
    PlayingScreen::setStartTime();
}

char loadWinningScreen(SDL_Window *window, SDL_Renderer *renderer, SDL_Event &event, int level){
    string path = "data/"+to_string(level)+"/score.txt";
    FILE *F = fopen(path.c_str(), "r");
    int bestStroke = 0, bestTime = 0;
    fscanf(F, "%d %d", &bestStroke, &bestTime);
    fclose(F);

    if ((!bestStroke || !bestTime) || (stroke < bestStroke) || (stroke == bestStroke && _time < bestTime)){
        F = fopen(path.c_str(), "w");
        fprintf(F, "%d %d", stroke, _time);
        fclose(F);
    }

    WinningScreen::init(renderer, stroke, _time, bestStroke, bestTime, level);

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
        WinningScreen::display(renderer);
    }
    WinningScreen::destroy();
    return pressed;
}

char loadGameOverScreen(SDL_Window *window, SDL_Renderer *renderer, SDL_Event &event){
    GameOverScreen::init(renderer);

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
                    pressed = GameOverScreen::handle();
                    if (pressed != 'n') displaying = false; ///none
                    break;
                }
            }
        }
        GameOverScreen::display(renderer);
    }
    GameOverScreen::destroy();
    return pressed;
}

void loadInstruction(SDL_Window *window, SDL_Renderer *renderer, SDL_Event &event){
    Instruction::init(renderer);

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
                    char pressed = Instruction::handle();
                    if (pressed == 'b') displaying = false; ///none
                    break;
                }
            }
        }
        Instruction::display(renderer);
    }
    Instruction::destroy();
}
