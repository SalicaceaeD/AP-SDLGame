#ifndef ANIMATION_H
#define ANIMATION_H

#include <Entity.h>


class Animation : public Entity {
public:
    Animation();
    Animation(string _path, int _maxFrame);

    void setPos(float _x, float _y);
    void setSize(float _w, float _h);
    //void initTexture(SDL_Renderer *renderer);
    void showTexture(SDL_Renderer *renderer);
protected:
    int maxFrame = 0;
    int frame = 0;
};

#endif // ANIMATION_H
