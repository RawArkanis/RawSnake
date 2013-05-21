#include "Head.h"

Head::Head(SDL_Rect rect)
    : Entity(rect)
{
}

Head::~Head()
{
}

void Head::Draw()
{
    float x0 = _rect.x + 0.1f;
    float y0 = 0.1f;
    float z0 = _rect.y + 0.1f;

    float xf = _rect.x + 0.9f;
    float yf = 0.9f;
    float zf = _rect.y + 0.9f;

    glEnable(GL_TEXTURE_2D);

    glPushMatrix();

    float verde[] = {0.0f, 0.75f, 0.0f, 1.0f};
    float specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, verde);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMateriali(GL_FRONT, GL_SHININESS, 10);

    glBindTexture(GL_TEXTURE_2D, _texture);

    DrawBox(x0, y0, z0, xf, yf, zf);

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}
