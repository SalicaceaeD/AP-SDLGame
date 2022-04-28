#ifndef BALL_H
#define BALL_H

#include <vector>
#include "Entity.h"
#include "Tool.h"
#include "Hole.h"
#include "Block.h"

class Ball : public Entity {
public:
    Ball(){path = "assets/img/golf-ball.png";};

    void setInitialMousePos(const Vector2f &curMousePos);
    void setVelocity(const Vector2f &curMousePos);
    void updatePos();
    void init(const Vector2f &initPos);
    char update(SDL_Renderer *renderer, bool mousePressed, bool mouseDown,
                Hole &golfHole);
    bool increaseStroke();

    void addX(int val) {pos.x += val;}
    void addY(int val) {pos.y += val;}
    void resizeRect(int val) {rect.w += val; rect.h += val;}
protected:
    Vector2f initialMousePos;
    Vector2f dir;
    float initVelocity = 1;
    float velocity = 0;
    vector<float> friction = {0.02, 0.01, 0.005};
    float inertia = 0.005;
private:
    bool moving = false;
    char win = '0';
};

#endif // BALL_H
