#include "Scene.h"

Scene::Scene(SceneManager *manager, const std::string &name)
    : _manager(manager), 
	_name(name)
{
}

Scene::~Scene()
{
}

std::string Scene::Name() const
{
    return _name;
}
