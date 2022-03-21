#ifndef ENTITY_H
#define ENTITY_H
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
//#include <SDL_ttf.h>

#include "Tool.h"

using namespace std;

class Entity{
public:
    Entity() {};
    ~Entity() {};
    void setPos(float _x, float _y);
    void setCenter(char type, float val);
    Vector2f getPos();
    bool checkClick(Vector2f mousePos);

    void initTexture(SDL_Renderer *renderer);
    //void initTexture(SDL_Renderer *renderer, TTF_Font *font, const char *textureText, SDL_Color textColor);
    void showTexture(SDL_Renderer *renderer);
    void destroyTexture();

    string path = "";
protected:
    Vector2f pos;
    SDL_Texture *texture;
    SDL_Rect rect;
};

#endif // ENTITY_H
