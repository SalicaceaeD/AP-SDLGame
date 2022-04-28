#include "Animation.h"

Animation::Animation(string _path, int _maxFrame){
    path = _path;
    maxFrame = _maxFrame;
}
void Animation::setPos(float _x, float _y){
    rect.x = _x;
    rect.y = _y;
}
void Animation::setSize(float _w, float _h){
    rect.w = _w;
    rect.h = _h;
}
void Animation::showTexture(SDL_Renderer *renderer){
    SDL_Rect clip = {rect.w*(frame/6), 0, rect.w, rect.h};
    ++frame;
    if (frame/6 == maxFrame) frame = 0;
    SDL_RenderCopy(renderer, texture, &clip, &rect);
}
