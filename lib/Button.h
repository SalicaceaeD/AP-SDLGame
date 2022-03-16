#ifndef BUTTON_H
#define BUTTON_H

#include <Entity.h>


class Button : public Entity{
public:
    Button(){};
    Button(char type){
        if (type == 'p') path = "assets/img/play-button.png";
        if (type == 'q') path = "assets/img/quit-button.png";
        if (type == 's') path = "assets/img/sound-on-button.png";
        if (type == 'm') path = "assets/img/sound-off-button.png";
        if (type == 'x') path = "assets/img/x-button.png";
        if (type == 'l') path = "assets/img/level-frame.png";
    }

    bool checkClick(Vector2f mousePos);
protected:
private:
};

#endif // BUTTON_H
