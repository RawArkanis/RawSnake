#ifndef __RGL_SCENE_MANAGER_H__
#define __RGL_SCENE_MANAGER_H__

#include <map>

#include "Scene.h"

class SceneManager
{
public:
    SceneManager();
    ~SceneManager();

    void AddScene(Scene *scene);
    void RemoveScene(const std::string &name);

    bool ChangeCurrentScene(const std::string &name);
    Scene *CurrentScene();
    Scene *GetScene(const std::string &name);

	bool SceneExists(const std::string &name);

    void Update(float delta);
    void Draw();

private:
    std::map<std::string, Scene *> _sceneList;

    std::string _currentSceneName;
};

#endif
