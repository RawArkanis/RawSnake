#ifndef __RGL_SCENE_H__
#define __RGL_SCENE_H__

#include "../Common.h"

class SceneManager;

class Scene
{
public:
    Scene(SceneManager *manager, const std::string &name);
    ~Scene();

    std::string Name() const;

    virtual void Update(float delta) = 0;
    virtual void Draw() = 0;

protected:
    SceneManager *_manager;

    std::string _name;
};

#endif
