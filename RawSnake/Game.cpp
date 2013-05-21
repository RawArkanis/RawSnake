#include "Game.h"
#include "GameWindow.h"
#include "Scene/GameScene.h"

Game::Game()
    : _exit(false)
{
    GameScene *gameScene = new GameScene(&_sceneManager, "GameScene");
    _sceneManager.AddScene(gameScene);

    _sceneManager.ChangeCurrentScene("GameScene");
}

void Game::setup()
{
    //Define a cor de limpeza da tela
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_POLYGON_SMOOTH);
    glEnable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(FOVY, GAMEWINDOW.getRatio(), ZNEAR, ZFAR);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        0.0f, 25.0f, 10.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f);

    float ambientLight[] = {0.05f, 0.05f, 0.05f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
}

void Game::processEvents(const SDL_Event& event)
{
    switch (event.type)
    {
        case SDL_QUIT:
            _exit = true;
            break;
    }
}

void Game::processLogics(float secs)
{
    _sceneManager.Update(secs);
}

void Game::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _sceneManager.Draw();

}

bool Game::ended()
{
    return _exit;
}

void Game::teardown()
{
}
