#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "../Common.h"

class Entity
{
public:
    Entity(SDL_Rect rect = SDL_Rect());
    ~Entity();

    void SetTexture(int textute);

    void Rect(SDL_Rect rect);
    SDL_Rect Rect();

    virtual void Draw() = 0;

protected:
    SDL_Rect _rect;

    int _texture;
};

#endif
