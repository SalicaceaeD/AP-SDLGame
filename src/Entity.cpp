#include "Entity.h"

#include "Tool.h"

const int SCREEN_WIDTH = 700;
const int SCREEN_HEIGHT = 700;

void Entity::setPos(float _x, float _y){
    pos.x = _x; pos.y = _y;
}

Vector2f Entity::getPos(){
    return pos;
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

void Entity::initTexture(SDL_Renderer *renderer, TTF_Font *font, const char *textureText, SDL_Color textColor){
    texture = nullptr;
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText, textColor);
    if(textSurface == NULL){
        cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << "\n";
    } else {
        //Create texture from surface pixels
        texture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if(texture == NULL){
            cout << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << "\n";
        }
        SDL_FreeSurface(textSurface);
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

void Entity::destroyTexture(){
    SDL_DestroyTexture(texture);
}
