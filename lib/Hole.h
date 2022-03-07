#ifndef HOLE_H
#define HOLE_H

#include "Entity.h"
#include "Tool.h"

class Hole : public Entity {
public:
    Hole() {path = "assets/img/hole.png";};

    bool checkWin(Vector2f golfBallPos);
protected:
    float radius = 8;
private:
};

#endif // HOLE_H
