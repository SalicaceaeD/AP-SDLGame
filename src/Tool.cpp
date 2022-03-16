#include "Tool.h"

Vector2f getMouse(){
    int mouseX = 0, mouseY = 0;
    SDL_GetMouseState(&mouseX, &mouseY);
    return Vector2f(mouseX, mouseY);
}

int ccw(Vector2f u, Vector2f v, Vector2f t){
    float val = u.x * (v.y - t.y) + v.x * (t.y - u.y) + t.x * (u.y - v.y);
    if (val < 0) return -1;
    if (val > 0) return 1;
    return 0;
}
