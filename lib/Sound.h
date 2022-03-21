#ifndef SOUND_H
#define SOUND_H

#include <iostream>
#include <SDL_mixer.h>

using namespace std;

class Music {
public:
    void loadMusic();
    void freeMusic();
    void play();

    void setPlayingStatus(bool status) {playing = status;}
    bool getPlayingStatus() {return playing;}

    string path;
protected:
    Mix_Music *aud;
    bool playing = true;
};

class SoundEffect {
public:
    void loadSE(const char* path);
    void freeSE();
    void play();

    void setSoundStatus(bool status) {soundOn = status;}
    bool getSoundStatus() {return soundOn;}
protected:
    Mix_Chunk *aud;
    bool soundOn = true;
};

#endif // SOUND_H
