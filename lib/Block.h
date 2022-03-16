#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include "Tool.h"

using namespace std;

class Block{
public:
    Block(){};

    bool checkCollision(Vector2f ballPos);
    void add(const pair<Vector2f,Vector2f> &Pos);
    void reset();

    vector<pair<Vector2f,Vector2f>> blockPos;
private:
};

#endif // BLOCK_H
