#include "Ball.h"

void Ball::setInitialMousePos(const Vector2f &curMousePos){
    initialMousePos = curMousePos;
}

void Ball::setVelocity(const Vector2f &curMousePos){
    initVelocity = initialMousePos.getDistance(curMousePos);
    velocity = initVelocity/20;
    velocity = min((int) velocity, 10);
    dir = initialMousePos - curMousePos;
}

void Ball::updatePos(Block &blocks){
    //cout << velocity << "\n";
    if (velocity <= 0){
        moving = false;
        return;
    }
    moving = true;
    float deltaX = (velocity/initVelocity)*dir.x;
    float deltaY = (velocity/initVelocity)*dir.y;

    if (blocks.checkCollision({pos.x+deltaX, pos.y})) dir.x *= -1, deltaX *= -1;
    if (blocks.checkCollision({pos.x, pos.y+deltaY})) dir.y *= -1, deltaY *= -1;
    pos.x += deltaX;
    pos.y += deltaY;

    for (auto a : friction) if (velocity > a*10){
        velocity -= a;
        break;
    }
    velocity -= inertia;
}

Entity charge("assets/img/charge.png");
bool Ball::update(SDL_Renderer *renderer, bool mousePressed, bool mouseDown,
                  Hole &golfHole, Block &blocks){
    if (win){
        return true;
    }
    if (golfHole.checkWin(pos)){
        win = true;
    }
    Vector2f curMousePos = getMouse();

    if (mousePressed && !moving){
        setInitialMousePos(curMousePos);
    }
    if (mouseDown && !moving){
        setVelocity(curMousePos);
        if (velocity > 0){
            //SDL_RenderDrawLine(renderer, pos.x+8, pos.y+8, pos.x+8+initV.x, pos.y+8+initV.y);
            charge.initTexture(renderer);
            float x=pos.x+5, y=pos.y+5;
            for (int i=1; i<=velocity; ++i){
                x += 15.0/initVelocity*dir.x;
                y += 15.0/initVelocity*dir.y;
                charge.setPos(x, y);
                charge.showTexture(renderer);
            }
            charge.destroyTexture();
        }
    } else {
        updatePos(blocks);
    }
    return false;
}

void Ball::init(const Vector2f &initPos){
    setPos(initPos.x, initPos.y);
    velocity = 0;
    initVelocity = 1;
    dir = Vector2f(0, 0);
    moving = false;
    win = false;
}

bool Ball::increaseStroke(){
    return (velocity > 0 && !moving);
}
