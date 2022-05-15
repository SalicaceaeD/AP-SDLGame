#ifndef TEXT_H
#define TEXT_H

#include "Entity.h"
#include <SDL_ttf.h>

class Text : public Entity {
public:
    Text(){};
    Text(string _mes, int _sz, bool _isButton);
    bool mouseHovering = 0;
    SDL_Color textColor = {58, 34, 79};

    void setText(string _mes, int _sz, bool _isButton);
    void setMes(string _mes) {mes = _mes;}
    void setColor(int color);
    void setIsButton(bool _isButton) {isButton = _isButton;}
    //void initTexture(SDL_Renderer *renderer);
    void showTexture(SDL_Renderer *renderer);
protected:
    string mes = "";
    int sz = 0;
    bool isButton = 0;
private:
};

#endif // TEXT_H
