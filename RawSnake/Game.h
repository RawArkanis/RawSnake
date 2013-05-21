#ifndef ROTATINGTRIANGLE_H_INCLUDED
#define ROTATINGTRIANGLE_H_INCLUDED

#include "GameSteps.h"
#include "Scene/SceneManager.h"

class Game : public GameSteps
{
public:
	Game();

    virtual void setup();

    virtual void processEvents(const SDL_Event& event);
    virtual void processLogics(float secs);
    virtual void draw();

	bool ended();

    virtual void teardown();

private:
    bool _exit;

    SceneManager _sceneManager;

};

#endif // ROTATINGTRIANGLE_H_INCLUDED
