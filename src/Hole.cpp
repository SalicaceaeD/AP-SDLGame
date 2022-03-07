#include "Hole.h"

bool Hole::checkWin(Vector2f golfBallPos){
    golfBallPos = golfBallPos + Vector2f(8, 8);
    Vector2f holePos = pos + Vector2f(radius, radius);
    if (holePos.getDistance(golfBallPos) < radius)
        return true;
    return false;
}
