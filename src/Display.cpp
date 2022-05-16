#include "Display.h"

SoundEffect buttonPressed;
Music bgm;

void initSound(){
    buttonPressed.loadSE("assets/sfx/button.mp3");
    bgm.loadMusic("assets/sfx/bgm.mp3");
    bgm.play();
}
void quitSound(){
    buttonPressed.freeSE();
    bgm.freeMusic();
}

namespace Background {
    static Entity background[2];
    float bgPos[2];
    static Entity homeScreen("assets/img/homescreen.png");
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
            if (bgPos[i] < -2100) bgPos[i] = 0;
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
        playButton.setPos(288, 333);
        quitButton.setPos(288, 493);
        optionButton.setPos(241, 413);
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
    static Text bgmButton[2];
    static Text resetButton("RESET", 40, 1);
    static Text backButton("BACK", 40, 1);
    bool soundStatus = true;
    bool playing = true;

    void init(){
        soundButton[0].setText("SOUND: OFF", 40, 1);
        soundButton[1].setText("SOUND: ON", 40, 1);
        soundButton[0].setPos(208, 328);
        soundButton[1].setPos(223, 328);

        bgmButton[0].setText("MUSIC: OFF", 40, 1);
        bgmButton[1].setText("MUSIC: ON", 40, 1);
        bgmButton[0].setPos(208, 396);
        bgmButton[1].setPos(223, 396);

        resetButton.setPos(272, 464);
        backButton.setPos(288, 532);

        FILE *F = fopen("assets/sfx/data.txt", "r");
        int tmp;
        fscanf(F, "%d", &tmp);
        fclose(F);
        soundStatus = tmp;

        F = fopen("assets/sfx/bgm.txt", "r");
        fscanf(F, "%d", &tmp);
        fclose(F);
        playing = tmp;
    }
    char handle(){
        char pressed = 'n';
        if (soundButton[soundStatus].checkMouseHovering()){
            soundStatus ^= 1;
            buttonPressed.switchSoundStatus();
            pressed = 's';
        }
        if (bgmButton[playing].checkMouseHovering()){
            playing ^= 1;
            bgm.switchSoundStatus();
            bgm.play();
            pressed = 'm';
        }
        if (resetButton.checkMouseHovering())pressed = 'r';
        if (backButton.checkMouseHovering()) pressed = 'b';
        if (pressed != 'n') buttonPressed.play();
        return pressed;
    }
        void display(SDL_Renderer *renderer){
        SDL_RenderClear(renderer);

        Background::display(renderer);
        soundButton[soundStatus].showTexture(renderer);
        bgmButton[playing].showTexture(renderer);
        resetButton.showTexture(renderer);
        backButton.showTexture(renderer);

        SDL_RenderPresent(renderer);
    }
    void destroy(){
        soundButton[0].destroyTexture();
        soundButton[1].destroyTexture();
        bgmButton[0].destroyTexture();
        bgmButton[1].destroyTexture();
        resetButton.destroyTexture();
        backButton.destroyTexture();
}
    static Entity resetBg("assets/img/option-reset-bg.png");
    void resetPage(SDL_Window* window, SDL_Renderer *renderer, SDL_Event &event){
        resetBg.initTexture(renderer);
        resetBg.showTexture(renderer);

        Text mes("ALL YOUR PLAYING DATA WILL BE DELETED", 20, 0);
        mes.setPos(87, 215);
        mes.showTexture(renderer);

        mes.setMes("ARE YOU SURE YOU WANT TO RESET GAME?");
        mes.setPos(95, 258);
        mes.showTexture(renderer);
        mes.~Entity();

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

                            playing = 1;
                            bgm.setPlayingStatus(1);
                            bgm.play();
                            F = fopen("assets/sfx/bgm.txt", "w");
                            fprintf(F, "%d", 1);
                            fclose(F);

                            for (int i=1;; ++i){
                                string path = "data/"+to_string(i)+"/score.txt";
                                F = fopen(path.c_str(), "w");
                                if (F == nullptr) break;
                                fprintf(F, "%d %d", 0, 0);
                                fclose(F);
                            }
                            LevelScreen::resetData();
                        }
                        if (!displaying) buttonPressed.play();
                        break;
                    }
                }
            }
            if (!rs) {
                yesButton.showTexture(renderer);
                noButton.showTexture(renderer);
            }
            else {
                SDL_RenderClear(renderer);
                resetBg.showTexture(renderer);

                Text mes("RESET COMPLETED !", 40, 0);
                mes.setPos(103, 281);
                mes.showTexture(renderer);
                mes.~Entity();
            }
            SDL_RenderPresent(renderer);
            if (rs) SDL_Delay(1000);

        }
        resetBg.destroyTexture();
        yesButton.~Entity();
        noButton.~Entity();
    }
}

namespace PauseScreen{
    static Entity menu("assets/img/pause-screen.png");
    static Text returnButtonText("RETURN", 25, 0);
    static Text resumeButtonText("RESUME", 25, 0);
    Button returnButton(130, 293, 155, 48);
    Button resumeButton(415, 293, 155, 48);

    void init(SDL_Renderer *renderer){
        SDL_Rect background = {0, 0, 700, 600};
        SDL_RenderFillRect(renderer, &background);

        menu.initTexture(renderer);
        menu.showTexture(renderer);
        menu.destroyTexture();

        Text ques("DO YOU WANT TO RETURN TO MENU?", 20, 0);
        ques.setPos(140, 254);
        ques.showTexture(renderer);
        ques.~Entity();

        returnButtonText.setPos(150, 305);
        resumeButtonText.setPos(435, 305);
    }
    char handle(){
        char pressed = 'n';
        if (resumeButton.checkClick()) pressed = 'r';
        if (returnButton.checkClick()) pressed = 'b';
        if (pressed != 'n') buttonPressed.play();
        return pressed;
    }
    void display(SDL_Renderer *renderer){
        returnButtonText.mouseHovering = returnButton.checkClick();
        resumeButtonText.mouseHovering = resumeButton.checkClick();

        returnButtonText.showTexture(renderer);
        resumeButtonText.showTexture(renderer);

        SDL_RenderPresent(renderer);
    }
    void destroy(){
        returnButtonText.destroyTexture();
        resumeButtonText.destroyTexture();
    }
}

namespace WinningScreen{
    static Entity winningScreen("assets/img/winning-screen.png");
    static Entity hio("assets/img/winning-screen-hio.png");
    static Entity nhs("assets/img/winning-screen-nhs.png");
    static Text nextButtonText("NEXT LEVEL", 15, 0);
    static Text backButtonText("BACK TO MENU", 15, 0);
    static Text repButtonText("TRY AGAIN", 15, 0);
    Button nextButton(251, 371, 196, 34);
    Button backButton(252, 409, 196, 34);
    Button repButton(252, 447, 196, 34);
    int level = 0;

    void init(SDL_Renderer *renderer, int stroke, int time, int bestStroke, int bestTime, int _level){
        level = _level;

        nextButtonText.setPos(298, 381);
        backButtonText.setPos(286, 419);
        repButtonText.setPos(301, 457);

        SDL_Rect background = {0, 0, 700, 600};
        SDL_RenderFillRect(renderer, &background);
        winningScreen.initTexture(renderer);
        winningScreen.showTexture(renderer);
        winningScreen.destroyTexture();
        if (stroke == 1) { ///hole in one
            hio.initTexture(renderer);
            hio.showTexture(renderer);
            hio.destroyTexture();
        }
        if ((!bestStroke || !bestTime) || (stroke < bestStroke) || (stroke == bestStroke && time < bestTime)){ ///new high score
            nhs.initTexture(renderer);
            nhs.showTexture(renderer);
            nhs.destroyTexture();
        }

        string Sec = to_string(time%60);
        string Min = to_string(time/60);
        Text Time((Min.size()<2?"0"+Min:Min) + ":" + (Sec.size()<2?"0"+Sec:Sec), 15, 0);
        Time.setPos(301, 326);
        Time.showTexture(renderer);

        Sec = to_string(bestTime%60);
        Min = to_string(bestTime/60);
        Time.setMes((Min.size()<2?"0"+Min:Min) + ":" + (Sec.size()<2?"0"+Sec:Sec));
        Time.setPos(433, 326);
        Time.showTexture(renderer);
        Time.~Entity();

        Text Stroke(to_string(stroke), 15, 0);
        Stroke.setPos(301, 293);
        Stroke.showTexture(renderer);

        Stroke.setMes(to_string(bestStroke));
        Stroke.setPos(433, 293);
        Stroke.showTexture(renderer);
        Stroke.~Entity();
    }
    char handle(){
        char pressed = 'n';
        if (LevelScreen::haveNext(level))
            if (nextButton.checkClick()) pressed = 'N';
        if (backButton.checkClick()) pressed = 'b';
        if (repButton.checkClick())  pressed = 'a';
        if (pressed != 'n') buttonPressed.play();
        return pressed;
    }
    void display(SDL_Renderer *renderer){
        if (LevelScreen::haveNext(level))
            nextButtonText.mouseHovering = nextButton.checkClick();
        backButtonText.mouseHovering = backButton.checkClick();
        repButtonText.mouseHovering  = repButton.checkClick();

        nextButtonText.showTexture(renderer);
        backButtonText.showTexture(renderer);
        repButtonText.showTexture(renderer);

        SDL_RenderPresent(renderer);
    }
    void destroy(){
        nextButtonText.destroyTexture();
        backButtonText.destroyTexture();
        repButtonText.destroyTexture();
    }
}

namespace GameOverScreen{
    static Entity GOScreen("assets/img/game-over-screen.png");
    static Text backButtonText("BACK TO MENU", 15, 0);
    static Text repButtonText("TRY AGAIN", 15, 0);
    Button backButton(252, 269, 196, 34);
    Button repButton(252, 307, 196, 34);

    void init(SDL_Renderer *renderer){
        backButtonText.setPos(286, 280);
        repButtonText.setPos(301, 318);

        SDL_Rect background = {0, 0, 700, 600};
        SDL_RenderFillRect(renderer, &background);
        GOScreen.initTexture(renderer);
        GOScreen.showTexture(renderer);
        GOScreen.destroyTexture();
    }
    char handle(){
        char pressed = 'n';
        if (repButton.checkClick())  pressed = 'a';
        if (backButton.checkClick()) pressed = 'b';
        if (pressed != 'n') buttonPressed.play();
        return pressed;
    }
    void display(SDL_Renderer *renderer){
        backButtonText.mouseHovering = backButton.checkClick();
        repButtonText.mouseHovering  = repButton.checkClick();

        backButtonText.showTexture(renderer);
        repButtonText.showTexture(renderer);

        SDL_RenderPresent(renderer);
    }
    void destroy(){
        backButtonText.destroyTexture();
        repButtonText.destroyTexture();
    }
}

namespace LevelScreen{
    const vector<Vector2f> lpos =  {{113,95}, {239,95}, {365,95}, {491,95},
                                    {113,221},{239,221},{365,221},{491,221},
                                    {113,347},{239,347},{365,347},{491,347},
                                    {113,473},{239,473},{365,473},{491,473}};
    static Text levelFrame("f", 96, 1);
    static Entity goBackButton("assets/img/go-back-button.png");
    static Entity goNextButton("assets/img/go-next-button.png");
    static Entity xButton("assets/img/x-button.png");
    static Entity background("assets/img/background.png");
    static Text htpButton("HOW TO PLAY", 20, 1);
    int page = 0;
    const int maxPage = 1;

    void init(SDL_Renderer *renderer){
        goBackButton.initTexture(renderer);
        goNextButton.initTexture(renderer);
        xButton.initTexture(renderer);
        background.initTexture(renderer);

        goBackButton.setPos(19, 300);
        goNextButton.setPos(617,300);
        xButton.setPos(636, 0);

        htpButton.setPos(16, 22);

        loadData();
    }
    //Entity levelButton[2];
    vector<int> won(16);
    int nextLevel = 1;
    void loadData(){
        fill(won.begin(), won.end(), -1);
        FILE* F;
        for (int i=0; i<16; ++i){
            string path = "data/"+to_string(page*16+i+1)+"/score.txt";
            F = fopen(path.c_str(), "r");
            if (F == nullptr) break;
            fscanf(F, "%d", &won[i]);
            fclose(F);
            if (won[i] > 0) nextLevel = page*16+i+1+1;
        }
        delete F;
    }
    void transition(SDL_Renderer *renderer, int sign){
        buttonPressed.play();
        /*
        levelButton[0].path = "assets/img/level-button-faint.png";
        levelButton[1].path = "assets/img/level-button-dark.png";
        levelButton[0].initTexture(renderer);
        levelButton[1].initTexture(renderer);

        vector<int> won(lpos.size()*2, 0);
        FILE* F;
        for (int id=0; id<=1; ++id) for (int i=0; i<lpos.size(); ++i) {
            string path = "data/"+to_string((page+sign*id)*16+i+1)+"/score.txt";
            F = fopen(path.c_str(), "r");
            if (F != nullptr) fscanf(F, "%d", &won[id*lpos.size()+i]);
            fclose(F);
        }
        delete F;
        for (auto &x : won) x = (x ? 1 : 0);

        vector<Vector2f> Pos[2];
        Pos[0] = Pos[1] = lpos;
        int SCREEN_WIDTH = 700;
        for (auto &p : Pos[1]) p.x += sign*SCREEN_WIDTH;
        for (int delta = 25; SCREEN_WIDTH > 0; SCREEN_WIDTH -= delta){
            SDL_RenderClear(renderer);
            background.showTexture(renderer);
            for (int id=0; id<=1; ++id)
                for (int i=0; i<lpos.size(); ++i){
                    auto p = &Pos[id][i];
                    p->x = p->x - sign*delta;
                    int j = won[id*lpos.size()+i];
                    levelButton[j].setPos(p->x, p->y);
                    levelButton[j].showTexture(renderer);
                }
            SDL_RenderPresent(renderer);
        }

        levelButton[0].destroyTexture();
        levelButton[1].destroyTexture();
        */
        page += sign;
        loadData();
    }
    int handle(SDL_Renderer *renderer){
        Vector2f curMousePos = getMouse();
        if (xButton.checkMouseHovering()){
            buttonPressed.play();
            return -1;
        }
        if (htpButton.checkMouseHovering()){
            buttonPressed.play();
            return -2;
        }
        for (int i=0; i<16; ++i)
            if (lpos[i].x <= curMousePos.x && curMousePos.x < lpos[i].x+96 &&
                lpos[i].y <= curMousePos.y && curMousePos.y < lpos[i].y+96){
                    if (won[i] < 0 || page*16+i+1 > nextLevel) return 0;
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
        htpButton.showTexture(renderer);

        Text Level("0", 40, 0);
        for (int i=0; i<16; ++i){
            if (won[i] < 0) break;
            levelFrame.setPos(lpos[i].x, lpos[i].y);
            levelFrame.setColor(won[i]!=0 ? 2 : 0);
            if (page*16+i+1 == nextLevel) levelFrame.setColor(4);
            levelFrame.showTexture(renderer);

            string level = to_string(page*16+i+1);
            float x = lpos[i].x + (96-level.size()*32+6)/2;
            float y = lpos[i].y + (96-40)/2;
            Level.textColor = levelFrame.textColor;
            Level.mouseHovering = levelFrame.mouseHovering;
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
        goBackButton.destroyTexture();
        goNextButton.destroyTexture();
        background.destroyTexture();

        levelFrame.destroyTexture();
        htpButton.destroyTexture();
    }

    bool haveNext(int level){
        string path = "data/"+to_string(level+1)+"/score.txt";
        FILE* F = fopen(path.c_str(), "r");
        if (F == nullptr) return 0;
        fclose(F);
        delete F;
        return true;
    }
    void resetData(){
        page = 0;
        nextLevel = 1;
    }
}

namespace PlayingScreen{
    static Entity pauseButton("assets/img/pause-button.png"); //(636, 0, 64);
    static Entity playAgainButton("assets/img/play-again-button.png"); //(572, 0, 64);
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

namespace Instruction{
    static Animation ins("assets/img/ins.png", 15);
    static Text gi("GOT IT!", 20, 1);
    static Text htp("DRAG AND DROP YOUR MOUSE CURSOR TO", 20, 0);
    static Text htp2("INITIALIZE GOLF BALL'S VELOCITY AND DIRECTION", 20, 0);

    void init(SDL_Renderer *renderer){
        ins.reset();
        ins.initTexture(renderer);
        ins.setSize(300, 300);
        ins.setPos(200, 200);

        gi.setColor(0);
        gi.setPos(300, 525);
        htp.setColor(0);
        htp.setPos(100, 100);
        htp2.setColor(0);
        htp2.setPos(30, 140);
    }
    char handle(){
        if (gi.checkMouseHovering()){
            buttonPressed.play();
            return 'b';
        }
        return 'n';
    }
    void display(SDL_Renderer *renderer){
        SDL_RenderClear(renderer);

        ins.showTexture(renderer);
        gi.showTexture(renderer);
        htp.showTexture(renderer);
        htp2.showTexture(renderer);

        SDL_RenderPresent(renderer);
    }
    void destroy(){
        ins.destroyTexture();
        gi.destroyTexture();
        htp.destroyTexture();
        htp2.destroyTexture();
    }
}
