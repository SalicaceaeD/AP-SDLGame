#ifndef TOOL_H
#define TOOL_H

#include <bits/stdc++.h>
#include <math.h>
#include <SDL.h>

class Vector2f{
public:
    Vector2f() : x(0.0f), y(0.0f) {};
    Vector2f(float _x, float _y){
        x = _x; y = _y;
    }
    float getDistance(const Vector2f &v){
        return hypot(x-v.x, y-v.y);
    }
    Vector2f operator + (const Vector2f &u){
        return {x+u.x, y+u.y};
    }
    Vector2f operator - (const Vector2f &u){
        return {x-u.x, y-u.y};
    }

    float x, y;
};

#define pv2f pair<Vector2f,Vector2f>
Vector2f getMouse();
int ccw(Vector2f u, Vector2f v, Vector2f t);

#endif // TOOL_H
