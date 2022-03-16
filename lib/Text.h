#ifndef TEXT_H
#define TEXT_H

#include <SDL.h>
#include <SDL_ttf.h>

class Text {
public:
    void loadFromRenderedText(SDL_Renderer *renderer, TTF_Font *font, const char *textureText, SDL_Color textColor);
    void showText(SDL_Renderer *renderer);
    void freeText();
protected:
    SDL_Texture *texture;
    SDL_Rect rect;
private:
};

#endif // TEXT_H
