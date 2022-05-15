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
    Entity(string _path) {path = _path;}
    ~Entity();
    virtual void setPos(float _x, float _y);
    void setCenter(char type, float val);
    Vector2f getPos();
    Vector2f getSize();
    bool checkMouseHovering();

    virtual void initTexture(SDL_Renderer *renderer);
    virtual void showTexture(SDL_Renderer *renderer);
    void destroyTexture();

    string path = "";
protected:
    Vector2f pos = {0, 0};
    SDL_Texture *texture;
    SDL_Rect rect;
};

class Button{
public:
    Button(){};
    Button(int _x, int _y, int _sz)         { x = _x; y = _y; w = h = _sz; }
    Button(int _x, int _y, int _w, int _h)  { x = _x; y = _y; w = _w; h = _h; }
    bool checkClick(){
        Vector2f mousePos = getMouse();
        return  (x <= mousePos.x && mousePos.x < x+w) &&
                (y <= mousePos.y && mousePos.y < y+h);
    }
protected:
    int x, y, w, h;
private:
};

#endif // ENTITY_H
