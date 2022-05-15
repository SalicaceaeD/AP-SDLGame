#include "Ball.h"

Entity charge("assets/img/charge.png");
Entity initMousePos("assets/img/init-mouse-pos.png");
void Ball::setInitialMousePos(const Vector2f &curMousePos){
    initialMousePos = curMousePos;
    initMousePos.setPos(initialMousePos.x-12, initialMousePos.y-12);
}

void Ball::setVelocity(const Vector2f &curMousePos){
    initVelocity = initialMousePos.getDistance(curMousePos);
    velocity = initVelocity/20;
    velocity = min((int) velocity, 10);
    dir = initialMousePos - curMousePos;
}

bool inPyr = 0;
Vector2f prevPos;
void Ball::updatePos(){
    //cout << velocity << "\n";
    if (velocity <= 0){
        moving = false;
        return;
    }
    moving = true;
    float deltaX = (velocity/initVelocity)*dir.x;
    float deltaY = (velocity/initVelocity)*dir.y;

    if (Block::checkCollision({pos.x+deltaX, pos.y}) ||
        Lock::checkCollision({pos.x+deltaX, pos.y})) dir.x *= -1, deltaX *= -1;
    if (Block::checkCollision({pos.x, pos.y+deltaY}) ||
        Lock::checkCollision({pos.x, pos.y+deltaY})) dir.y *= -1, deltaY *= -1;
    prevPos = pos;
    pos.x += deltaX;
    pos.y += deltaY;

    inPyr = Pyramid::checkPyr(pos, dir, inPyr);

    for (auto a : friction) if (velocity > a*10){
        velocity -= a;
        break;
    }
    velocity -= inertia;
}

char Ball::update(SDL_Renderer *renderer, bool mousePressed, bool mouseDown,
                  Hole &golfHole){
    if (win != '0'){
        return win;
    }
    if (golfHole.checkWin(pos)){
        win = 'w';
    }
    if (Water::checkWater(prevPos, pos)){
        win = 'l';
    }
    if (Teleport::checkBallInPort(pos)){
        pos.x += (8.0/initVelocity)*dir.x;
        pos.y += (8.0/initVelocity)*dir.y;
    }
    Lock::checkKey(pos);

    Vector2f curMousePos = getMouse();
    if (mousePressed && !moving){
        setInitialMousePos(curMousePos);
    }
    if (mouseDown && !moving){
        initMousePos.initTexture(renderer);
        initMousePos.showTexture(renderer);
        initMousePos.destroyTexture();

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
        updatePos();
    }
    return '0';
}

void Ball::init(const Vector2f &initPos){
    setPos(initPos.x, initPos.y);
    velocity = 0;
    initVelocity = 1;
    dir = Vector2f(0,0);
    prevPos = Vector2f(0,0);
    moving = false;
    win = '0';
}

bool Ball::increaseStroke(){
    return (velocity > 0 && !moving);
}
