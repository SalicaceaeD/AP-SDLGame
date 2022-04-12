#include "Entity.h"

#include "Tool.h"

const int SCREEN_WIDTH = 700;
const int SCREEN_HEIGHT = 600;

Entity::~Entity(){
    destroyTexture();
}

void Entity::setPos(float _x, float _y){
    pos.x = _x; pos.y = _y;
}
void Entity::setCenter(char type, float val){
    if (type == 'a'){
        pos.x = (SCREEN_WIDTH - rect.w) / 2;
        pos.y = (SCREEN_HEIGHT- rect.h) / 2;
    }
    if (type == 'w'){
        pos.x = (SCREEN_WIDTH - rect.w) / 2;
        pos.y = val;
    }
    if (type == 'h'){
        pos.x = val;
        pos.y = (SCREEN_HEIGHT- rect.h) / 2;
    }
}
Vector2f Entity::getPos(){
    return pos;
}
Vector2f Entity::getSize(){
    return {rect.w, rect.h};
}
bool Entity::checkMouseHovering(){
    Vector2f mousePos = getMouse();
    float x1 = pos.x;
    float y1 = pos.y;
    float x2 = x1+rect.w;
    float y2 = y1+rect.h;
    return (x1<=mousePos.x && mousePos.x<x2 &&
            y1<=mousePos.y && mousePos.y<y2);
}

void Entity::initTexture(SDL_Renderer* renderer){
    if (texture) return;
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
    //SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    rect.x = pos.x;
    rect.y = pos.y;
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}
void Entity::destroyTexture(){
    if (texture) SDL_DestroyTexture(texture);
    texture = nullptr;
}
