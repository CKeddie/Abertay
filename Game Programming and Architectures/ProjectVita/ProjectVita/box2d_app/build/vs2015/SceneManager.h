#pragma once

#include <vector>
#include "scene_app.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

protected:
	std::vector<SceneApp> _scenes;
};

