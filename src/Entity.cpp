#include "Entity.h"
#include <iostream>

#include "Tool.h"

using namespace std;

void Entity::setPos(float _x, float _y){
    pos.x = _x; pos.y = _y;
}

Vector2f Entity::getPos(){
    return pos;
}

bool Entity::checkClick(Vector2f mousePos){
    float x1 = rect.x;
    float y1 = rect.y;
    float x2 = x1+rect.w;
    float y2 = y1+rect.h;
    return (x1<=mousePos.x && mousePos.x<x2 &&
            y1<=mousePos.y && mousePos.y<y2);
}

void Entity::initTexture(SDL_Renderer* renderer){
    texture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr)
        cout << "Unable to load image " << path << " SDL_image Error: "
            << IMG_GetError() << "\n";
    else {
        texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (texture == nullptr)
            cout << "Unable to create texture from " << path << " SDL Error: "
                << SDL_GetError() << "\n";
        SDL_FreeSurface(loadedSurface);
    }
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
}

void Entity::showTexture(SDL_Renderer *renderer){
    rect.x = pos.x;
    rect.y = pos.y;
    //rect.w = rect.w / 2.0;
    //rect.h = rect.h / 2.0;
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}
