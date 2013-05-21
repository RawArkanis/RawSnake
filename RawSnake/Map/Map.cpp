#include "Map.h"

Map::Map(int width, int height)
	: _width(width),
	_height(height)
{
}

Map::~Map()
{
}

void Map::SetTextures(int floor, int wall)
{
    _floor = floor;
    _wall = wall;
}

SDL_Rect Map::GetTile(int x, int y)
{
    SDL_Rect rect;
        
    rect.x = x - _width / 2;
    rect.y = y - _height / 2;
    rect.w = 1;
    rect.h = 1;

	return rect;
}

void Map::Draw()
{
    float x = _width / 2.0f;
    float y = 0.0f;
    float z = _height / 2.0f;

    glEnable(GL_TEXTURE_2D);

    glPushMatrix();

    float cinza[] = {0.3f, 0.3f, 0.3f, 1.0f};
    float specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cinza);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMateriali(GL_FRONT, GL_SHININESS, 10);

    glBindTexture(GL_TEXTURE_2D, _floor);

    // Chão
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.3f, 0.3f, 0.3f);
    glTexCoord2d(20.0f, 0.0f);
    glVertex3f(x, y, -z);
    glTexCoord2d(0.0f, 0.0f);
    glVertex3f(-x, y, -z);
    glTexCoord2d(0.0f, 20.0f);
    glVertex3f(-x, y, z);
    glTexCoord2d(20.0f, 20.0f);
    glVertex3f(x, y, z);
    glEnd();

    float vermelho[] = {0.75f, 0.0f, 0.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, vermelho);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMateriali(GL_FRONT, GL_SHININESS, 10);

    glBindTexture(GL_TEXTURE_2D, _wall);

    // Parede TOP
    DrawBox(-x - 1, y, -z - 1, x + 1, y + 1, -z);

    // Parede BOTTOM
    DrawBox(-x - 1, y, z, x + 1, y + 1, z + 1);

    // Parede LEFT
    DrawBox(-x - 1, y, -z, -x, y + 1, z);

    // Parede RIGHT
    DrawBox(x, y, -z, x + 1, y + 1, z);

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}
