#pragma once

#include "GameState.h"
#include "maths\vector4.h"
#include "GameObject.h"

class MainGame :
	public GameState
{
public:
	MainGame(SceneApp & scene, gef::Font * font);
	~MainGame();

	void Initialize();
	void Update(float gameTime);
	void Draw();
	void CleanUp();
protected:
	gef::Vector4 player_spawn_;
	GameObject* player_;

	std::vector<gef::Vector4> enemy_spawns_;
	std::vector<GameObject*> enemies_;
	
	void BuildEnemies(int count);
	void BuildPlayer();
	void BuildEnvironment();
};

