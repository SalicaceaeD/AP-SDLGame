#include "Button.h"

void Button::setType(char type){
    path = "assets/img/";
    if (type == 'p') path += "play-button.png";
    if (type == 'q') path += "quit-button.png";
    if (type == 's') path += "sound-on-button.png";
    if (type == 'o') path += "sound-off-button.png";
    if (type == 'x') path += "x-button.png";
    if (type == 'l') path += "level-frame.png";
    if (type == 'm') path += "menu-button.png";
    if (type == 'a') path += "play-again-button.png";
    if (type == 'b') path += "go-back-button.png";
    if (type == 'n') path += "go-next-button.png";
    if (type == 'N') path += "next-button.png";
}

bool Button::checkClick(Vector2f mousePos){
    float x1 = rect.x;
    float y1 = rect.y;
    float x2 = x1+rect.w;
    float y2 = y1+rect.h;
    return (x1<=mousePos.x && mousePos.x<x2 &&
            y1<=mousePos.y && mousePos.y<y2);
}
