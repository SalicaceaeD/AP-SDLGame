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
    void updatePos(Block &blocks);
    void init(const Vector2f &initPos);
    bool update(bool mousePressed, bool mouseDown,
                Hole &golfHole, Block &blocks);
protected:
    Vector2f initialMousePos;
    Vector2f initV;
    float initVelocity = 1;
    float velocity = 0;
    vector<float> friction = {0.02, 0.01, 0.005};
    float inertia = 0.001;
private:
    bool moving = false;
    bool win = false;
};

#endif // BALL_H
