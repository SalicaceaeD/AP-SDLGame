#ifndef ENTITY_H
#define ENTITY_H
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Tool.h"

using namespace std;

class Entity{
public:
    Entity() {};
    void setPos(float _x, float _y);
    void setCenter(char type, float val);
    Vector2f getPos();
    bool checkClick(Vector2f mousePos){
    float x1 = rect.x;
    float y1 = rect.y;
    float x2 = x1+rect.w;
    float y2 = y1+rect.h;
    return (x1<=mousePos.x && mousePos.x<x2 &&
            y1<=mousePos.y && mousePos.y<y2);
}
    void initTexture(SDL_Renderer *renderer);
    void initTexture(SDL_Renderer *renderer, TTF_Font *font, const char *textureText, SDL_Color textColor);
    void showTexture(SDL_Renderer *renderer);
    void destroyTexture();

    string path = "";
protected:
    Vector2f pos;
    SDL_Texture *texture;
    SDL_Rect rect;
};

#endif // ENTITY_H
