#include "Display.h"

bool soundStatus = true;
SoundEffect buttonPressed;

void initSound(){
    buttonPressed.loadSE("assets/sfx/button.mp3");
    int tmp;
    FILE* F = fopen("assets/sfx/data.txt", "r");
    fscanf(F, "%d", &tmp);
    fclose(F);
    soundStatus = tmp;
    buttonPressed.setSoundStatus(soundStatus);
}
void quitSound(){
    buttonPressed.freeSE();
    FILE* F = fopen("assets/sfx/data.txt", "w");
    fprintf(F, "%d", soundStatus);
    fclose(F);
}

namespace HomeScreen {
    Entity background;
    Button playButton('p');
    Button quitButton('q');
    Button soundButton[2];

    char handle(){
        Vector2f curMousePos = getMouse();
        if (playButton.checkClick(curMousePos)){
            buttonPressed.play();
            return 'p';
        }
        if (quitButton.checkClick(curMousePos)){
            return 'q';
        }
        if (soundButton[soundStatus].checkClick(curMousePos)){
            soundStatus ^= 1;
            buttonPressed.setSoundStatus(soundStatus);
            buttonPressed.play();
            return 's';
        }
        return 'n';
    }
    void build(SDL_Renderer *renderer){
        background.initTexture(renderer);
        playButton.initTexture(renderer);
        quitButton.initTexture(renderer);
        soundButton[0].initTexture(renderer);
        soundButton[1].initTexture(renderer);
    }
    void init(SDL_Renderer *renderer){
        background.path = "assets/img/background.png";
        background.setPos(0, 0);

        soundButton[0].setType('o');
        soundButton[1].setType('s');
        build(renderer);
        soundButton[0].setCenter('w', 380);
        soundButton[1].setCenter('w', 380);
        playButton.setCenter('w', 280);
        quitButton.setCenter('w', 480);
    }
    void display(SDL_Renderer *renderer){
        SDL_RenderClear(renderer);

        background.showTexture(renderer);
        playButton.showTexture(renderer);
        soundButton[soundStatus].showTexture(renderer);
        quitButton.showTexture(renderer);

        SDL_RenderPresent(renderer);
    }
    void destroy(){
        background.destroyTexture();
        playButton.destroyTexture();
        quitButton.destroyTexture();
        soundButton[0].destroyTexture();
        soundButton[1].destroyTexture();
    }
}

namespace PauseScreen{
    Entity menu;
    pv2f resumeButton = {{254, 194}, {446, 258}};
    pv2f returnButton = {{254, 268}, {446, 332}};
    pv2f resetButton  = {{254, 342}, {446, 406}};

    void init(SDL_Renderer *renderer){
        menu.path = "assets/img/menu.png";
        menu.initTexture(renderer);
        menu.setCenter('a', -1);
    }
    inline bool checkClick(pv2f button, Vector2f curMousePos){
        return  (button.first.x <= curMousePos.x && curMousePos.x <= button.second.x) &&
                (button.first.y <= curMousePos.y && curMousePos.y <= button.second.y);
    }
    char handle(){
        Vector2f curMousePos = getMouse();
        char pressed = 'n';
        if (checkClick(resumeButton, curMousePos)) pressed = 'r';
        if (checkClick(returnButton, curMousePos)) pressed = 'b';
        if (checkClick(resetButton,  curMousePos)) pressed = 'a';
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

namespace LevelScreen{
    const vector<Vector2f> lpos =  {{113,95}, {239,95}, {365,95}, {491,95},
                                    {113,221},{239,221},{365,221},{491,221},
                                    {113,347},{239,347},{365,347},{491,347},
                                    {113,473},{239,473},{365,473},{491,473}};
    Button levelButton('l');
    Button goBackButton('b');
    Button goNextButton('n');
    Button xButton('x');
    Entity background;
    int page = 0;
    const int maxPage = 3;
    void init(SDL_Renderer *renderer){
        page = 0;
        background.path = "assets/img/background.png";

        levelButton.initTexture(renderer);
        goBackButton.initTexture(renderer);
        goNextButton.initTexture(renderer);
        xButton.initTexture(renderer);
        background.initTexture(renderer);

        goBackButton.setPos(19, 300);
        goNextButton.setPos(617,300);
        xButton.setPos(636, 0);
        background.setPos(0, 0);
    }
    void transition(SDL_Renderer *renderer, int sign){
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
        if (xButton.checkClick(curMousePos)) return -1;
        for (int i=0; i<lpos.size(); ++i){
            if (lpos[i].x <= curMousePos.x && curMousePos.x < lpos[i].x+96 &&
                lpos[i].y <= curMousePos.y && curMousePos.y < lpos[i].y+96)
                    return page*16+i+1;
        }
        if (goBackButton.checkClick(curMousePos) && page > 0) transition(renderer, -1);
        if (goNextButton.checkClick(curMousePos) && page < maxPage) transition(renderer, 1);
        return 0;
    }
    void display(SDL_Renderer *renderer){
        SDL_RenderClear(renderer);

        background.showTexture(renderer);
        xButton.showTexture(renderer);
        for (auto p : lpos){
            levelButton.setPos(p.x, p.y);
            levelButton.showTexture(renderer);
        }
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
    }
}

namespace WinningScreen{
    Button playAgainButton('a');
    Button goBackButton('b');
    Button nextButton('N');

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
        if (playAgainButton.checkClick(curMousePos)) return 'a';
        if (goBackButton.checkClick(curMousePos))    return 'b';
        if (nextButton.checkClick(curMousePos))      return 'N';
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
