#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include "Text.h"
#include "Tool.h"

using namespace std;

namespace Block{

    void add(const pair<Vector2f,Vector2f> &Pos);
    void reset();
    bool checkCollision(Vector2f ballPos);
}

namespace Water{
    void add(const pair<Vector2f,Vector2f> &Pos);
    void reset();
    bool checkWater(Vector2f prevPos, Vector2f &ballPos);
}

namespace Pyramid{
    void add(Vector2f Pos);
    void reset();
    void init(SDL_Renderer *renderer);
    void destroy();
    void display(SDL_Renderer *renderer, Vector2f ballPos);
    bool checkPyr(Vector2f &ballPos, Vector2f &ballDir, bool inPyr);
}

namespace Lock{
    void add(Vector2f pos);
    void add(const pair<Vector2f,Vector2f> &Pos);
    void add(vector<pair<Vector2f,Vector2f>> keyPos);
    void reset();
    void init(SDL_Renderer *renderer);
    void destroy();
    bool display(SDL_Renderer *renderer);
    bool checkKey(Vector2f ballPos);
    bool checkCollision(Vector2f ballPos);
}

namespace Teleport{
    void add(pair<Vector2f, Vector2f> _port);
    void reset();
    bool checkBallInPort(Vector2f &ballPos);
}

void blockReset();

#endif // BLOCK_H
