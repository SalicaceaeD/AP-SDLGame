#include "Text.h"

//TTF_Font* font = TTF_OpenFont("assets/font/font.ttf", 32);
SDL_Color dark = {58, 34, 79};
SDL_Color red = {232, 80, 42};

Text::Text(string _mes, int _sz, bool _isButton){
    setText(_mes, _sz, _isButton);
}
void Text::setText(string _mes, int _sz, bool _isButton){
    mes = _mes; sz = _sz; isButton = _isButton;
}
void Text::showTexture(SDL_Renderer *renderer){
    texture = nullptr;

    if (isButton) mouseHovering = checkMouseHovering();
    SDL_Color textColor = (mouseHovering ? red : dark);
    TTF_Font* font = TTF_OpenFont("assets/font/font.ttf", sz);
    if (font == NULL)  printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, mes.c_str(), textColor);
    if(textSurface == NULL)
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    else{
        texture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if(texture == NULL)
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        SDL_FreeSurface(textSurface);
    }
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    rect.x = pos.x;
    rect.y = pos.y;
    SDL_RenderCopy(renderer, texture, NULL, &rect);

    TTF_CloseFont(font);
    //mouseHovering = false;
}
