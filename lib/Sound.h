#ifndef SOUND_H
#define SOUND_H

#include <iostream>
#include <SDL_mixer.h>

using namespace std;

class Music {
public:
    void loadMusic(const char* path);
    void freeMusic();
    void play();

    void setPlayingStatus(bool status) {playing = status;}
    void switchSoundStatus();
    bool getPlayingStatus() {return playing;}
protected:
    Mix_Music *aud;
    bool playing = true;
};

class SoundEffect {
public:
    void loadSE(const char* path);
    void freeSE();
    void play();

    void setSoundStatus(bool status) {soundStatus = status;}
    void switchSoundStatus();
    bool getSoundStatus() {return soundStatus;}
protected:
    Mix_Chunk *aud;
    bool soundStatus = true;
};

#endif // SOUND_H
