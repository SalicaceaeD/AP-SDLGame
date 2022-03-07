#include "Ball.h"

void Ball::setInitialMousePos(Vector2f curMousePos){
    initialMousePos = curMousePos;
}

void Ball::setVelocity(Vector2f curMousePos){
    initVelocity = initialMousePos.getDistance(curMousePos);
    velocity = initVelocity/30;
    initV = initialMousePos - curMousePos;
}

bool checkCollision(float _x, float _y){
    if (_x < 0 || _x > 800 || _y < 0 || _y > 600) return 1;
    return 0;
}

void Ball::updatePos(){
    if (velocity <= 0){
        moving = false;
        return;
    }
    moving = true;
    float deltaX = (velocity/initVelocity)*initV.x;
    float deltaY = (velocity/initVelocity)*initV.y;

    if (checkCollision(pos.x+deltaX, pos.y)) initV.x *= -1, deltaX *= -1;
    if (checkCollision(pos.x, pos.y+deltaY)) initV.y *= -1, deltaY *= -1;
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

bool Ball::update(bool mousePressed, bool mouseDown, Hole &golfHole){
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
        updatePos();
    }
    return false;
}

void Ball::init(Vector2f initPos){
    setPos(initPos.x, initPos.y);
    velocity = 0;
    initVelocity = 1;
    initV = Vector2f(0, 0);
    moving = false;
    win = false;
}
