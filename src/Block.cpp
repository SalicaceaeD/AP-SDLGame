#include "Block.h"

void blockReset(){
    Block::reset();
    Water::reset();
    Pyramid::reset();
    Lock::reset();
    Teleport::reset();
}

bool checkIntersect(Vector2f u, Vector2f v, Vector2f t, Vector2f w){
    if ((u.x-t.x)*(v.x-t.x) <= 0 || (u.y-t.y)*(v.y-t.y) <= 0)
        return ccw(u, v, t)*ccw(u, v, w) < 0;
    return false;
}
namespace Block{
    vector<pair<Vector2f,Vector2f>> blockPos;

    void add(const pair<Vector2f,Vector2f> &Pos){
        blockPos.push_back(Pos);
    }
    void reset(){
        blockPos.clear();
    }
    bool checkCollision(Vector2f ballPos){
        vector<Vector2f> Dir = {{0, 8}, {0, -8}, {8, 0}, {-8, 0}};
        ballPos = ballPos + Vector2f(8,8);
        for (auto &p : blockPos){
            for (int i=0; i<4; ++i){
                if (checkIntersect(p.first, p.second, ballPos, ballPos+Dir[i]))
                    return true;
            }
        }
        return false;
    }
}

namespace Water{
    vector<pair<Vector2f,Vector2f>> water;

    void add(const pair<Vector2f,Vector2f> &Pos){
        water.push_back(Pos);
    }
    void reset(){
        water.clear();
    }
    bool checkWater(Vector2f prevPos, Vector2f &ballPos){
        Vector2f curPos = Vector2f(8,8) + ballPos;
        prevPos = prevPos + Vector2f(8,8);
        for (auto &p : water){
            if (checkIntersect(p.first, p.second, prevPos, curPos))
                return true;
        }
        return false;
    }
}

namespace Pyramid{
    vector<Vector2f> pyr;
    static Entity pyd("assets/img/pyd.png");
    static Entity pyl("assets/img/pyl.png");

    void add(Vector2f Pos){
        pyr.push_back(Pos);
    }
    void reset(){
        pyr.clear();
    }
    bool checkBallInPyr(Vector2f pos, Vector2f ballPos){
        if (ballPos.x+16 < pos.x || pos.x+48 < ballPos.x) return false;
        if (ballPos.y+16 < pos.y || pos.y+48 < ballPos.y) return false;
        if (pos.x+48 - ballPos.x < 7 || ballPos.x+16 - pos.x < 7) return false;
        if (pos.y+48 - ballPos.y < 7 || ballPos.y+16 - pos.y < 7) return false;
        return true;
    }
    void init(SDL_Renderer *renderer){
        if (pyr.empty()) return;
        pyd.initTexture(renderer);
        pyl.initTexture(renderer);
    }
    void destroy(){
        if (pyr.empty()) return;
        pyd.destroyTexture();
        pyl.destroyTexture();
    }
    void display(SDL_Renderer *renderer, Vector2f ballPos){
        for (auto &p : pyr)
            if (checkBallInPyr(p, ballPos)){
                pyl.setPos(p.x, p.y);
                pyl.showTexture(renderer);
            } else {
                pyd.setPos(p.x, p.y);
                pyd.showTexture(renderer);
            }
    }
    bool checkPyr(Vector2f &ballPos, Vector2f &ballDir, bool inPyr){
        for (auto &p : pyr) if (checkBallInPyr(p, ballPos)){
            if (inPyr) return true;
            ballPos = p + Vector2f(16, 16);
            float val = ballDir.getDistance({0, 0});
            vector<Vector2f> Dir = {{val, 0}, {-val, 0}, {0, val}, {0, -val}};
            ballDir = Dir[rand()%4];
            return true;
        }
        return false;
    }

}

namespace Lock{
    vector<vector<pair<Vector2f,Vector2f>>> key;
    Entity lock("assets/img/lock.png");
    vector<pair<Vector2f,Vector2f>> lockPos;

    void add(Vector2f pos){
        lock.setPos(pos.x, pos.y);
    }
    void add(const pair<Vector2f,Vector2f> &Pos){
        lockPos.push_back(Pos);
    }
    void add(vector<pair<Vector2f,Vector2f>> keyPos){
        key.push_back(keyPos);
    }
    void reset(){
        key.clear();
        lockPos.clear();
    }
    void init(SDL_Renderer *renderer){
        if (key.empty()) return;
        lock.initTexture(renderer);
    }
    void destroy(){
        if (key.empty()) return;
        lock.destroyTexture();
    }
    bool display(SDL_Renderer *renderer){
        if (key.empty()) return false;
        SDL_Rect background = {lock.getPos().x, lock.getPos().y, 64, 64};
        SDL_RenderFillRect(renderer, &background);

        Text keyNum(to_string(key.size()), 25, 0);
        keyNum.setColor(3);
        keyNum.setPos(lock.getPos().x+12, lock.getPos().y+19);
        keyNum.showTexture(renderer);

        lock.showTexture(renderer);
        return true;
    }
    bool checkKey(Vector2f ballPos){
        vector<Vector2f> Dir = {{0, 8}, {0, -8}, {8, 0}, {-8, 0}};
        ballPos = ballPos + Vector2f(8,8);
        for (int id=0; id<key.size(); ++id){
            bool check = 0;
            for (auto &p : key[id]) for (int i=0; i<4; ++i)
                check |= checkIntersect(p.first, p.second, ballPos, ballPos+Dir[i]);
            if (check){
                key.erase(key.begin()+id);
                break;
            }
        }
    }
    bool checkCollision(Vector2f ballPos){
        if (key.empty()) return false;
        vector<Vector2f> Dir = {{0, 8}, {0, -8}, {8, 0}, {-8, 0}};
        ballPos = ballPos + Vector2f(8,8);
        for (auto &p : lockPos){
            for (int i=0; i<4; ++i){
                if (checkIntersect(p.first, p.second, ballPos, ballPos+Dir[i]))
                    return true;
            }
        }
        return false;
    }
}

namespace Teleport{
    vector<pair<Vector2f, Vector2f>> port;
    void add(pair<Vector2f, Vector2f> _port){
        port.push_back(_port);
    }
    void reset(){
        port.clear();
    }
    bool checkBallInPort(Vector2f &ballPos){
        Vector2f curPos = Vector2f(8,8) + ballPos;
        for (auto &p : port){
            if (p.first.getDistance(curPos) <= 8){
                ballPos = Vector2f(-8,-8) + p.second;
                return true;
            }
            if (p.second.getDistance(curPos) <= 8){
                ballPos = Vector2f(-8,-8) + p.first;
                return true;
            }
        }
        return false;
    }
}
