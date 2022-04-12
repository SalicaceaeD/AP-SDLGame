#include "Sound.h"

void SoundEffect::loadSE(const char* path){
    aud = Mix_LoadWAV(path);
    if (aud == NULL)
        cout << "Fail to load sound effect! SDL_mixer error: " << Mix_GetError() << "\n";

    int tmp;
    FILE* F = fopen("assets/sfx/data.txt", "r");
    fscanf(F, "%d", &tmp);
    fclose(F);
    soundStatus = tmp;
}
void SoundEffect::freeSE(){
    FILE* F = fopen("assets/sfx/data.txt", "w");
    fprintf(F, "%d", soundStatus);
    fclose(F);
    Mix_FreeChunk(aud);
}
void SoundEffect::play(){
    if (soundStatus)
        Mix_PlayChannel(-1, aud, 0);
}
void SoundEffect::switchSoundStatus(){
    soundStatus ^= 1;
    FILE* F = fopen("assets/sfx/data.txt", "w");
    fprintf(F, "%d", soundStatus);
    fclose(F);
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

