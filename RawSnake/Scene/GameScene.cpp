#include "GameScene.h"

GameScene::GameScene(SceneManager *manager, const std::string &name)
    : Scene(manager, name),
    _elapsedTime(0.0f),
    _direction(D_DOWN),
    _state(GS_IDLE),
    _enlarge(false)
{
    srand(SDL_GetTicks());

    _textures.push_back(LoadTexture("Resource/floor.png"));
    _textures.push_back(LoadTexture("Resource/wall.png"));
    _textures.push_back(LoadTexture("Resource/head.png"));
    _textures.push_back(LoadTexture("Resource/tail.png"));
    _textures.push_back(LoadTexture("Resource/food.png"));
    _textures.push_back(LoadTexture("Resource/intro.png"));
    _textures.push_back(LoadTexture("Resource/gameover.png"));

    for (int i = 0; i < (int)_textures.size(); i++)
    {
        if (_textures[i] == -1)
            throw std::runtime_error(std::string("Unable to load textures."));
    }

    _map.SetTextures(_textures[0], _textures[1]);
    _head.SetTexture(_textures[2]);
    _food.SetTexture(_textures[4]);

    Reset();
}

GameScene::~GameScene()
{
}

void GameScene::Update(float delta)
{
    Uint8* keys = SDL_GetKeyState(NULL);

    if (_state == GS_IDLE)
    {
        if (keys[SDLK_SPACE])
            _state = GS_PLAY;
    }
    else if (_state == GS_PLAY)
    {
        if (keys[SDLK_r])
            Reset();
        else if (keys[SDLK_UP])
        {
            if ((_moveQueue.size() == 0 && _direction != D_DOWN && _direction != D_UP) || 
                (_moveQueue.size() == 1 && _moveQueue.front() != D_UP && _moveQueue.front() != D_DOWN))
                _moveQueue.push(D_UP);
        }
        else if (keys[SDLK_DOWN])
        {
            if ((_moveQueue.size() == 0 && _direction != D_DOWN && _direction != D_UP) ||
                (_moveQueue.size() == 1 && _moveQueue.front() != D_UP && _moveQueue.front() != D_DOWN))
                _moveQueue.push(D_DOWN);
        }
        else if (keys[SDLK_LEFT])
        {
            if ((_moveQueue.size() == 0 && _direction != D_LEFT && _direction != D_RIGHT) ||
                (_moveQueue.size() == 1 && _moveQueue.front() != D_LEFT && _moveQueue.front() != D_RIGHT))
                _moveQueue.push(D_LEFT);
        }
        else if (keys[SDLK_RIGHT])
        {
            if ((_moveQueue.size() == 0 && _direction != D_LEFT && _direction != D_RIGHT) ||
                (_moveQueue.size() == 1 && _moveQueue.front() != D_LEFT && _moveQueue.front() != D_RIGHT))
                _moveQueue.push(D_RIGHT);
        }

        _elapsedTime += delta;
        if (_elapsedTime >= 0.250f)
        {
            _elapsedTime = 0.0f;

            if (_moveQueue.size() != 0)
            {
                _direction = _moveQueue.front();
                _moveQueue.pop();
            }

            SDL_Rect rect = _head.Rect();
            SDL_Rect old = rect;

            switch (_direction)
            {
            case D_UP:
                rect.y--;
                break;

            case D_DOWN:
                rect.y++;
                break;

            case D_LEFT:
                rect.x--;
                break;

            case D_RIGHT:
                rect.x++;
                break;

            default:
                break;
            }

            if (rect.x < -10.0f || rect.x > 9.0f || rect.y < -10.0f || rect.y > 9.0f)
                _state = GS_GAME_OVER;
            else
            {
                bool collided = false;

                for (int i = 0; i < _tails.size(); i++)
                {
                    SDL_Rect tail = _tails[i]->Rect();

                    if (rect.x == tail.x && rect.y == tail.y)
                    {
                        collided = true;
                        break;
                    }
                }

                if (collided)
                    _state = GS_GAME_OVER;
                else
                {
                    SDL_Rect food = _food.Rect();
                    if (food.x == rect.x && food.y == rect.y)
                    {
                        _lastFoodPos.push_back(food);
                        SpawnFood();

                        _enlarge = true;
                    }

                    _head.Rect(rect);

                    rect = old;
                    for (int i = 0; i < _tails.size(); i++)
                    {
                        old = _tails[i]->Rect();
                        _tails[i]->Rect(rect);
                        rect = old;
                    }

                    if (_enlarge)
                    {
                        SDL_Rect pos = _lastFoodPos[0];

                        if (rect.x == pos.x && rect.y == pos.y)
                        {
                            _lastFoodPos.erase(_lastFoodPos.begin());

                            Tail *tail = new Tail(rect);
                            tail->SetTexture(_textures[3]);
                            _tails.push_back(tail);

                            if (_lastFoodPos.size() == 0)
                                _enlarge = false;
                        }
                    }
                }
            }
        }
    }
    else if (_state == GS_GAME_OVER)
    {
        if (keys[SDLK_SPACE])
        {
            Reset();
            _state = GS_PLAY;
        }
    }
}

void GameScene::Draw()
{
    if (_state == GS_IDLE)
    {
        glEnable(GL_TEXTURE_2D);

        glDisable(GL_DEPTH_TEST);

        ViewOrtho();

        glPushMatrix();

        float branco[] = {1.0f, 1.0f, 1.0f, 1.0f};
        float specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, branco);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
        glMateriali(GL_FRONT, GL_SHININESS, 10);

        glBindTexture(GL_TEXTURE_2D, _textures[5]);

        glBegin(GL_QUADS);
        glColor3f(1.0f, 0.1f, 0.1f);
        glTexCoord2f(0, 0);
        glVertex3f(0, 0, 0);
        glTexCoord2f(0, 1);
        glVertex3f(0, GAME_HEIGHT, 0); 
        glTexCoord2f(1, 1);
        glVertex3f(GAME_WIDTH, GAME_HEIGHT, 0);
        glTexCoord2f(1, 0);
        glVertex3f(GAME_WIDTH, 0, 0);
        glEnd();

        glPopMatrix();

        ViewPerspective();

        glEnable(GL_DEPTH_TEST);

        glDisable(GL_TEXTURE_2D);
    }
    else if (_state == GS_PLAY)
    {
        float ambient[] = {0.3f, 0.3f, 0.3f, 1.0f};
        float diffuse[] = {0.7f, 0.7f, 0.7f, 1.0f};
        float specular[] = {1.0f, 1.0f, 1.0f, 1.0f};

        glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

        float posicao[] = {0.0f, 10.0f, 0.0f, 1.0f};
        glLightfv(GL_LIGHT0, GL_POSITION, posicao);

        glEnable(GL_LIGHT0);

        _map.Draw();

        _head.Draw();

        for (int i = 0; i < _tails.size(); i++)
            _tails[i]->Draw();

        _food.Draw();
    }
    else if (_state == GS_GAME_OVER)
    {
        glEnable(GL_TEXTURE_2D);

        glDisable(GL_DEPTH_TEST);

        ViewOrtho();

        glPushMatrix();

        float branco[] = {1.0f, 1.0f, 1.0f, 1.0f};
        float specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, branco);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
        glMateriali(GL_FRONT, GL_SHININESS, 10);

        glBindTexture(GL_TEXTURE_2D, _textures[6]);

        glBegin(GL_QUADS);
        glColor3f(1.0f, 0.1f, 0.1f);
        glTexCoord2f(0, 0);
        glVertex3f(0, 0, 0);
        glTexCoord2f(0, 1);
        glVertex3f(0, GAME_HEIGHT, 0); 
        glTexCoord2f(1, 1);
        glVertex3f(GAME_WIDTH, GAME_HEIGHT, 0);
        glTexCoord2f(1, 0);
        glVertex3f(GAME_WIDTH, 0, 0);
        glEnd();

        glPopMatrix();

        ViewPerspective();

        glEnable(GL_DEPTH_TEST);

        glDisable(GL_TEXTURE_2D);
    }
}

void GameScene::Reset()
{
    SDL_Rect rect = { 0, 0, 0, 0 };

    int size = _moveQueue.size();
    for (int i = 0; i < size; i++)
        _moveQueue.pop();

    _head.Rect(rect);

    _elapsedTime = 0.0f;
    _direction = D_DOWN;
    _state = GS_IDLE;

    _tails.clear();

    for (int i = 0; i < 3; i++)
    {
        rect.y--;

        Tail *tail = new Tail(rect);
        tail->SetTexture(_textures[3]);

        _tails.push_back(tail);
    }

    SpawnFood();
}

void GameScene::SpawnFood()
{
    std::vector<SDL_Rect> freeSpaces;

    for (int i = -10; i < 10; i++)
    {
        for (int j = -10; j < 10; j++)
        {
            SDL_Rect rect = _head.Rect();

            if (rect.x != i && rect.y != j)
            {
                bool mustAdd = true;

                for (int k = 0; k < _tails.size(); k++)
                {
                    rect = _tails[k]->Rect();

                    if (rect.x == i && rect.y == j)
                    {
                        mustAdd = false;
                        break;
                    }
                }

                if (mustAdd)
                {
                    rect.x = i;
                    rect.y = j;

                    freeSpaces.push_back(rect);
                }
            }
        }
    }

    if (freeSpaces.size() > 0)
    {
        int i = rand() % freeSpaces.size();

        _food.Rect(freeSpaces[i]);
    }
}
