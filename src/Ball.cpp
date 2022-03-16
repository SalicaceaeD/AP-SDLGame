#include "Ball.h"

void Ball::setInitialMousePos(const Vector2f &curMousePos){
    initialMousePos = curMousePos;
}

void Ball::setVelocity(const Vector2f &curMousePos){
    initVelocity = initialMousePos.getDistance(curMousePos);
    velocity = initVelocity/20;
    initV = initialMousePos - curMousePos;
}

void Ball::updatePos(Block &blocks){
    if (velocity <= 0){
        moving = false;
        return;
    }
    moving = true;
    float deltaX = (velocity/initVelocity)*initV.x;
    float deltaY = (velocity/initVelocity)*initV.y;

    if (blocks.checkCollision({pos.x+deltaX, pos.y})) initV.x *= -1, deltaX *= -1;
    if (blocks.checkCollision({pos.x, pos.y+deltaY})) initV.y *= -1, deltaY *= -1;
    pos.x += deltaX;
    pos.y += deltaY;

    /*if (velocity < friction*10){
        velocity -= inertia;
    } else {
        velocity -= friction;
    }*/
    for (auto a : friction) if (velocity > a*10){
        velocity -= a;
        break;
    }
    velocity -= inertia;
}

bool Ball::update(bool mousePressed, bool mouseDown,
                  Hole &golfHole, Block &blocks){
    if (win){
        //cout << "Win!";
        return true;
    }
    if (golfHole.checkWin(pos)){
        win = true;
    }
    int mouseX = 0, mouseY = 0;
    SDL_GetMouseState(&mouseX, &mouseY);
    Vector2f curMousePos = {mouseX, mouseY};

    if (mousePressed && !moving){
        setInitialMousePos(curMousePos);
    }
    if (mouseDown && !moving){
        setVelocity(curMousePos);
    } else {
        updatePos(blocks);
    }
    return false;
}

void Ball::init(const Vector2f &initPos){
    setPos(initPos.x, initPos.y);
    velocity = 0;
    initVelocity = 1;
    initV = Vector2f(0, 0);
    moving = false;
    win = false;
}
