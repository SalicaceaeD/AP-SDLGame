#include "Sound.h"

void SoundEffect::loadSE(const char* path){
    aud = Mix_LoadWAV(path);
    if (aud == NULL)
        cout << "Fail to load sound effect! SDL_mixer error: " << Mix_GetError() << "\n";
}
void SoundEffect::freeSE(){
    Mix_FreeChunk(aud);
}
void SoundEffect::play(){
    if (soundOn)
        Mix_PlayChannel(-1, aud, 0);
}

void Music::loadMusic(){
    aud = Mix_LoadMUS(path.c_str());
    if (aud == NULL)
        cout << "Fail to load music! SDL_mixer error: " << Mix_GetError() << "\n";
}
void Music::freeMusic(){
    Mix_FreeMusic(aud);
}
void Music::play(){
    Mix_PlayMusic(aud, -1);
}

