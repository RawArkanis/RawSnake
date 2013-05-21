#ifndef __MAP_H__
#define __MAP_H__

#include <vector>

#include "../Common.h"

const int MAP_WIDTH = 20;
const int MAP_HEIGHT = 20;

class Map
{
public:
	Map(int width = MAP_WIDTH, int height = MAP_HEIGHT);
	~Map();

    void SetTextures(int floor, int wall);

	SDL_Rect GetTile(int x, int y);

    void Draw();

private:
	int _width;
	int _height;

    int _floor;
    int _wall;
};

#endif
