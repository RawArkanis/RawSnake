#include "Entity.h"

Entity::Entity(SDL_Rect rect)
    : _rect(rect)
{
}

Entity::~Entity()
{
}

void Entity::SetTexture(int texture)
{
    _texture = texture;
}

void Entity::Rect(SDL_Rect rect)
{
    _rect = rect;
}

SDL_Rect Entity::Rect()
{
    return _rect;
}
