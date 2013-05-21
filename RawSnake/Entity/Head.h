#ifndef __HEAD_H__
#define __HEAD_H__

#include "Entity.h"

class Head : public Entity
{
public:
    Head(SDL_Rect rect = SDL_Rect());
    ~Head();

    void Draw();
};

#endif
