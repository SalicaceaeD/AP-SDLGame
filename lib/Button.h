#ifndef BUTTON_H
#define BUTTON_H

#include <Entity.h>


class Button : public Entity{
public:
    Button(){};
    Button(char type) {setType(type);}

    void setType(char type);
    bool checkClick(Vector2f mousePos);
protected:
private:
};

#endif // BUTTON_H
