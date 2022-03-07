#ifndef BALL_H
#define BALL_H

#include <vector>
#include "Entity.h"
#include "Tool.h"
#include "Hole.h"

class Ball : public Entity {
public:
    Ball(){path = "assets/img/golf-ball.png";};

    void setInitialMousePos(Vector2f curMousePos);
    void setVelocity(Vector2f curMousePos);
    void updatePos();
    void init(Vector2f initPos);
    bool update(bool mousePressed, bool mouseDown, Hole &golfHole);
protected:
    Vector2f initialMousePos;
    Vector2f initV;
    float initVelocity = 1;
    float velocity = 0;
    vector<float> friction = {0.05, 0.01, 0.005};
    float inertia = 0.001;
private:
    bool moving = false;
    bool win = false;
};

#endif // BALL_H
