#include "Button.h"

bool Button::checkClick(Vector2f mousePos){
    float x1 = rect.x;
    float y1 = rect.y;
    float x2 = x1+rect.w;
    float y2 = y1+rect.h;
    return (x1<=mousePos.x && mousePos.x<x2 &&
            y1<=mousePos.y && mousePos.y<y2);
}
