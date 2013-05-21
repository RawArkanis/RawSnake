#include "SceneManager.h"

SceneManager::SceneManager()
    : _currentSceneName("")
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::AddScene(Scene *scene)
{
    _sceneList[scene->Name()] = scene;
}

void SceneManager::RemoveScene(const std::string &name)
{
    _sceneList.erase(name);
}

bool SceneManager::ChangeCurrentScene(const std::string &name)
{
	if (!SceneExists(name))
		return false;

	_currentSceneName = name;
			
	return true;
}

Scene *SceneManager::CurrentScene()
{
    return _sceneList[_currentSceneName];
}

Scene *SceneManager::GetScene(const std::string &name)
{
	if (!SceneExists(name))
		return nullptr;

    return _sceneList[name];
}

bool SceneManager::SceneExists(const std::string &name)
{
	return _sceneList.find(name) != _sceneList.end();
}

void SceneManager::Update(float delta)
{
	if (!_currentSceneName.empty())
    {
        _sceneList[_currentSceneName]->Update(delta);
    }
}

void SceneManager::Draw()
{
    if (!_currentSceneName.empty())
    {
        _sceneList[_currentSceneName]->Draw();
    }
}
