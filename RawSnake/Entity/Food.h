#ifndef __FOOD_H__
#define __FOOD_H__

#include "Entity.h"

class Food : public Entity
{
public:
    Food(SDL_Rect rect = SDL_Rect());
    ~Food();

    void Draw();
};

#endif
