#include "Display.h"

SoundEffect buttonPressed;

void initSound(){
    buttonPressed.loadSE("assets/sfx/button.mp3");
}
void quitSound(){
    buttonPressed.freeSE();
}

namespace Background {
    Entity background[2];
    float bgPos[2];
    Entity homeScreen("assets/img/homescreen.png");
    //Animation flag(8, 26, 52, 600, 248);
    void init(SDL_Renderer *renderer){
        background[0].path = "assets/img/background-slow.png";
        background[1].path = "assets/img/background-fast.png";
        background[0].initTexture(renderer);
        background[1].initTexture(renderer);
        bgPos[0] = bgPos[1] = 0;

        homeScreen.initTexture(renderer);
        //flag.path = "assets/img/flag.png";
        //flag.initTexture(renderer);
    }
    void display(SDL_Renderer *renderer){
        homeScreen.showTexture(renderer);
        vector<float> spd = {0.4, 0.5};
        for (int i=0; i<=1; ++i){
            bgPos[i] -= spd[i];
            if (bgPos[i] < -1050) bgPos[i] = 0;
            background[i].setPos(bgPos[i], 0);
            background[i].showTexture(renderer);
        }
        //flag.showTexture(renderer);
    }
    void destroy(){
        background[0].destroyTexture();
        background[1].destroyTexture();
        homeScreen.destroyTexture();
        //flag.destroyTexture();
    }
}

namespace HomeScreen {
    static Text playButton("PLAY", 40, 1);
    static Text quitButton("QUIT", 40, 1);
    static Text optionButton("OPTIONS", 40, 1);

    void init(){
        playButton.setPos(50, 333);
        quitButton.setPos(50, 493);
        optionButton.setPos(50, 413);
    }
    char handle(){
        char pressed = 'n';
        if (playButton.checkMouseHovering())   pressed = 'p';
        if (quitButton.checkMouseHovering())   pressed = 'q';
        if (optionButton.checkMouseHovering()) pressed = 'o';
        if (pressed != 'n') buttonPressed.play();
        return pressed;
    }
    void display(SDL_Renderer *renderer){
        SDL_RenderClear(renderer);

        Background::display(renderer);
        playButton.showTexture(renderer);
        quitButton.showTexture(renderer);
        optionButton.showTexture(renderer);

        SDL_RenderPresent(renderer);
    }
    void destroy(){
        playButton.destroyTexture();
        quitButton.destroyTexture();
        optionButton.destroyTexture();
    }
}

namespace OptionScreen{
    static Text soundButton[2];
    static Text resetButton("RESET", 40, 1);
    static Text backButton("BACK", 40, 1);
    bool soundStatus = true;

    void init(){
        soundButton[0].setText("SOUND: OFF", 40, 1);
        soundButton[1].setText("SOUND: ON", 40, 1);
        soundButton[0].setPos(50, 333);
        soundButton[1].setPos(50, 333);
        resetButton.setPos(50, 413);
        backButton.setPos(50, 493);

        FILE *F = fopen("assets/sfx/data.txt", "r");
        int tmp;
        fscanf(F, "%d", &tmp);
        fclose(F);
        soundStatus = tmp;
    }
    char handle(){
        char pressed = 'n';
        if (soundButton[soundStatus].checkMouseHovering()){
            soundStatus ^= 1;
            buttonPressed.switchSoundStatus();
            pressed = 's';
        }
        if (resetButton.checkMouseHovering())pressed = 'r';
        if (backButton.checkMouseHovering()) pressed = 'b';
        if (pressed != 'n') buttonPressed.play();
        return pressed;
    }
    static Entity resetBg("assets/img/option-reset.png");
    static Entity rsCpl("assets/img/option-reset-completed.png");
    void resetPage(SDL_Window* window, SDL_Renderer *renderer, SDL_Event &event){
        resetBg.initTexture(renderer);
        Text yesButton("YES", 40, 1); //(147, 323, 170, 96);
        Text noButton("NO", 40, 1); //(386, 323, 170, 96);
        yesButton.setPos(160, 323);
        noButton.setPos(450, 323);

        bool displaying = true;
        while (displaying) {
            bool rs = false;
            while (SDL_PollEvent(&event)){
                switch (event.type){
                    case SDL_QUIT:{
                        quitSDL(window, renderer);
                        exit(0);
                        break;
                    }
                    case SDL_MOUSEBUTTONDOWN:{
                        if (noButton.checkMouseHovering()) displaying = false;
                        if (yesButton.checkMouseHovering()){
                            displaying = false;
                            rs = true;

                            soundStatus = 1;
                            buttonPressed.setSoundStatus(1);
                            FILE *F = fopen("assets/sfx/data.txt", "w");
                            fprintf(F, "%d", 1);
                            fclose(F);

                            for (int i=1;; ++i){
                                string path = "data/"+to_string(i)+"/score.txt";
                                F = fopen(path.c_str(), "w");
                                if (F == nullptr) break;
                                fprintf(F, "%d %d", 0, 0);
                                fclose(F);
                            }

                        }
                        if (!displaying) buttonPressed.play();
                        break;
                    }
                }
            }
            SDL_RenderClear(renderer);
            if (!rs) {
                resetBg.showTexture(renderer);
                yesButton.showTexture(renderer);
                noButton.showTexture(renderer);
            }
            else {
                rsCpl.initTexture(renderer);
                rsCpl.showTexture(renderer);
            }
            SDL_RenderPresent(renderer);
            if (rs){
                SDL_Delay(1000);
                rsCpl.destroyTexture();
            }

        }
        resetBg.destroyTexture();
        yesButton.~Entity();
        noButton.~Entity();
    }
    void display(SDL_Renderer *renderer){
        SDL_RenderClear(renderer);

        Background::display(renderer);
        soundButton[soundStatus].showTexture(renderer);
        resetButton.showTexture(renderer);
        backButton.showTexture(renderer);

        SDL_RenderPresent(renderer);
    }
    void destroy(){
        soundButton[0].destroyTexture();
        soundButton[1].destroyTexture();
        resetButton.destroyTexture();
        backButton.destroyTexture();
    }
}

namespace PauseScreen{
    Entity menu("assets/img/menu.png");
    Button resumeButton(254, 194, 192, 64);
    Button returnButton(254, 268, 192, 64);
    Button resetButton(254, 342, 192, 64);

    void init(SDL_Renderer *renderer){
        menu.initTexture(renderer);
        menu.setCenter('a', -1);
    }
    char handle(){
        Vector2f curMousePos = getMouse();
        char pressed = 'n';
        if (resumeButton.checkClick(curMousePos)) pressed = 'r';
        if (returnButton.checkClick(curMousePos)) pressed = 'b';
        if (resetButton.checkClick(curMousePos))  pressed = 'a';
        if (pressed != 'n') buttonPressed.play();
        return pressed;
    }
    void display(SDL_Renderer *renderer){
        SDL_Rect background = {0, 0, 700, 600};
        SDL_RenderFillRect(renderer, &background);

        menu.showTexture(renderer);
        SDL_RenderPresent(renderer);
    }
    void destroy(){
        menu.destroyTexture();
    }
}

namespace WinningScreen{
    Entity playAgainButton("assets/img/play-again-button.png");
    Entity goBackButton("assets/img/go-back-button.png");
    Entity nextButton("assets/img/next-button.png");

    void init(SDL_Renderer *renderer){
        playAgainButton.initTexture(renderer);
        goBackButton.initTexture(renderer);
        nextButton.initTexture(renderer);

        playAgainButton.setCenter('a', -1);
        goBackButton.setCenter('h', playAgainButton.getPos().x-74);
        nextButton.setCenter('h', playAgainButton.getPos().x+74);
    }
    char handle(){
        Vector2f curMousePos = getMouse();
        if (playAgainButton.checkMouseHovering()) return 'a';
        if (goBackButton.checkMouseHovering())    return 'b';
        if (nextButton.checkMouseHovering())      return 'N';
        return 'n';
    }
    void display(SDL_Renderer *renderer){
        SDL_Rect background = {0, 0, 700, 600};
        SDL_RenderFillRect(renderer, &background);

        playAgainButton.showTexture(renderer);
        goBackButton.showTexture(renderer);
        nextButton.showTexture(renderer);

        SDL_RenderPresent(renderer);
    }
    void destroy(){
        playAgainButton.destroyTexture();
        goBackButton.destroyTexture();
        nextButton.destroyTexture();
    }
}

namespace LevelScreen{
    const vector<Vector2f> lpos =  {{113,95}, {239,95}, {365,95}, {491,95},
                                    {113,221},{239,221},{365,221},{491,221},
                                    {113,347},{239,347},{365,347},{491,347},
                                    {113,473},{239,473},{365,473},{491,473}};
    Text levelFrame("f", 96, 1);
    Entity levelButton("assets/img/level-frame.png");
    Entity goBackButton("assets/img/go-back-button.png");
    Entity goNextButton("assets/img/go-next-button.png");
    Entity xButton("assets/img/x-button.png");
    Entity background("assets/img/background.png");
    int bgPos = 0;
    int page = 0;
    const int maxPage = 3;
    void init(SDL_Renderer *renderer){
        levelButton.initTexture(renderer);
        goBackButton.initTexture(renderer);
        goNextButton.initTexture(renderer);
        xButton.initTexture(renderer);
        background.initTexture(renderer);

        goBackButton.setPos(19, 300);
        goNextButton.setPos(617,300);
        xButton.setPos(636, 0);
    }
    void transition(SDL_Renderer *renderer, int sign){
        buttonPressed.play();
        auto Cur = lpos;
        auto New = lpos;
        int SCREEN_WIDTH = 700;
        for (auto &p : New) p.x += sign*SCREEN_WIDTH;
        for (int delta = 25; SCREEN_WIDTH > 0; SCREEN_WIDTH -= delta) {
            SDL_RenderClear(renderer);
            background.showTexture(renderer);
            for (auto &p : Cur){
                p.x = p.x - sign*delta;
                levelButton.setPos(p.x, p.y);
                levelButton.showTexture(renderer);
            }
            for (auto &p : New) {
                p.x = p.x - sign*delta;
                levelButton.setPos(p.x, p.y);
                levelButton.showTexture(renderer);
            }
            SDL_RenderPresent(renderer);
        }
        page += sign;
    }
    int handle(SDL_Renderer *renderer){
        Vector2f curMousePos = getMouse();
        if (xButton.checkMouseHovering()){
            buttonPressed.play();
            return -1;
        }
        for (int i=0; i<lpos.size(); ++i)
            if (lpos[i].x <= curMousePos.x && curMousePos.x < lpos[i].x+96 &&
                lpos[i].y <= curMousePos.y && curMousePos.y < lpos[i].y+96){
                    buttonPressed.play();
                    return page*16+i+1;
                }

        if (goBackButton.checkMouseHovering() && page > 0) transition(renderer, -1);
        if (goNextButton.checkMouseHovering() && page < maxPage) transition(renderer, 1);
        return 0;
    }
    void display(SDL_Renderer *renderer){
        SDL_RenderClear(renderer);

        background.showTexture(renderer);
        xButton.showTexture(renderer);

        Text Level("0", 40, 0);
        for (int i=0; i<lpos.size(); ++i){
            levelFrame.setPos(lpos[i].x, lpos[i].y);
            levelFrame.showTexture(renderer);

            string level = to_string(page*16+i+1);
            float x = lpos[i].x + (96-level.size()*32+6)/2;
            float y = lpos[i].y + (96-40)/2;
            Level.mouseHovering = levelFrame.checkMouseHovering();
            Level.setMes(level);
            Level.setPos(x, y);
            Level.showTexture(renderer);
        }
        Level.~Entity();
        if (page > 0) goBackButton.showTexture(renderer);
        if (page < maxPage) goNextButton.showTexture(renderer);

        SDL_RenderPresent(renderer);
    }
    void destroy(){
        xButton.destroyTexture();
        levelButton.destroyTexture();
        goBackButton.destroyTexture();
        goNextButton.destroyTexture();
        background.destroyTexture();

        levelFrame.destroyTexture();
    }
}

namespace PlayingScreen{
    Entity pauseButton("assets/img/pause-button.png"); //(636, 0, 64);
    Entity playAgainButton("assets/img/play-again-button.png"); //(572, 0, 64);
    Uint32 startTime = 0;
    int time = 0;
    //Entity background("assets/img/playscreen.png");

    void init(SDL_Renderer *renderer){
        //background.initTexture(renderer);
        pauseButton.initTexture(renderer);
        pauseButton.setPos(636, 0);
        playAgainButton.initTexture(renderer);
        playAgainButton.setPos(572, 0);

        time = 0;
        setStartTime();
    }
    char handle(){
        char pressed = 'n';
        if (pauseButton.checkMouseHovering()){ ///pause
            time += getTime();
            pressed = 'p';
        }
        if (playAgainButton.checkMouseHovering()){ ///reset level
            time = 0;
            setStartTime();
            pressed = 'a';
        }
        if (pressed != 'n') buttonPressed.play();
        return pressed;
    }
    void display(SDL_Renderer *renderer, int level, int stroke){
        //background.showTexture(renderer);
        pauseButton.showTexture(renderer);
        playAgainButton.showTexture(renderer);

        int now = time + getTime();
        string Sec = to_string(now%60);
        string Min = to_string(now/60);
        Text Time("o " + (Min.size()<2?"0"+Min:Min) + ":" + (Sec.size()<2?"0"+Sec:Sec), 25, 0);
        Time.setPos(315, 19);
        Time.showTexture(renderer);
        Time.~Entity();

        Text Level("l " + to_string(level), 25, 0);
        Level.setPos(32, 19);
        Level.showTexture(renderer);
        Level.~Entity();

        Text Stroke("s " + to_string(stroke), 25, 0);
        Stroke.setPos(128, 19);
        Stroke.showTexture(renderer);
        Stroke.~Entity();
    }
    void destroy(){
        //background.destroyTexture();
        pauseButton.destroyTexture();
        playAgainButton.destroyTexture();
    }
    int getTime(){
        return (SDL_GetTicks() - startTime)/1000;
    }
    void setStartTime(){
        startTime = SDL_GetTicks();
    }
}
