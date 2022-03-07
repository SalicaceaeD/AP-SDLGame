#ifndef ENTITY_H
#define ENTITY_H
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "Tool.h"

using namespace std;

class Entity{
public:
    Entity() {};
    void setPos(float _x, float _y);
    Vector2f getPos();
    bool checkClick(Vector2f mousePos);
    void initTexture(SDL_Renderer *renderer);
    void showTexture(SDL_Renderer *renderer);

    string path = "";
protected:
    Vector2f pos;
    SDL_Texture *texture;
    SDL_Rect rect;
};

#endif // ENTITY_H
