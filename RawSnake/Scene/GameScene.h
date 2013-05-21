#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include <vector>

#include "Scene.h"
#include "../Map/Map.h"
#include "../Entity/Head.h"
#include "../Entity/Tail.h"
#include "../Entity/Food.h"

enum Direction
{
    D_UP,
    D_DOWN,
    D_LEFT,
    D_RIGHT
};

enum GameState
{
    GS_IDLE,
    GS_PLAY,
    GS_GAME_OVER
};

class GameScene : public Scene
{
public:
    GameScene(SceneManager *manager, const std::string &name);
    ~GameScene();

    void Update(float delta);
    void Draw();

private:
    float _elapsedTime;
    Direction _direction;
    GameState _state;

    bool _blockMove;
    bool _enlarge;

    std::vector<SDL_Rect> _lastFoodPos;

    Map _map;

    Head _head;
    std::vector<Tail *> _tails;

    Food _food;

    std::vector<int> _textures;

    void Reset();
    void SpawnFood();
};

#endif
