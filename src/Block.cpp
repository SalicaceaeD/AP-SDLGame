#include "Block.h"

bool checkIntersect(Vector2f u, Vector2f v, Vector2f t, Vector2f w){
    return ccw(u, v, t)*ccw(u, v, w) < 0;
}

vector<Vector2f> dir = {{0, 8}, {0, -8}, {8, 0}, {-8, 0}};
bool Block::checkCollision(Vector2f ballPos){
    ballPos = ballPos + Vector2f(8,8);
    for (auto &p : blockPos){
        for (int i=0; i<4; ++i){
            if (checkIntersect(p.first, p.second, ballPos, ballPos+dir[i]))
                return true;
        }
    }
    return false;
}

void Block::add(const pair<Vector2f,Vector2f> &Pos){
    blockPos.push_back(Pos);
}

void Block::reset(){
    blockPos.clear();
}
