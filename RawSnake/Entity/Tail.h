#ifndef __TAIL_H__
#define __TAIL_H__

#include "Entity.h"

class Tail : public Entity
{
public:
    Tail(SDL_Rect rect = SDL_Rect());
    ~Tail();

    void Draw();
};

#endif
