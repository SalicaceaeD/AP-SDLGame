#include "Text.h"
#include <iostream>

using namespace std;

void Text::loadFromRenderedText(SDL_Renderer *renderer, TTF_Font *font, const char *textureText, SDL_Color textColor){
    texture = nullptr;
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText, textColor);
    if(textSurface == NULL){
        cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << "\n";
    } else {
        //Create texture from surface pixels
        texture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if(texture == NULL){
            cout << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << "\n";
        }
        SDL_FreeSurface(textSurface);
    }
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
}

/*void showText(SDL_Renderer *renderer){
    rect.x = pos.x;
    rect.y = pos.y;
    //rect.w = rect.w / 2.0;
    //rect.h = rect.h / 2.0;
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}*/

void Text::freeText(){
    SDL_free(texture);
}
