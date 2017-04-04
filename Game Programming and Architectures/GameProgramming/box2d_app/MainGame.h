#pragma once

#include "GameState.h"
#include "maths\vector4.h"

#include "GameObject.h"
#include "MeshRenderer.h"
#include "box2d\Box2D.h"
#include <Player.h>

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
	std::vector<gef::Vector4> enemy_spawns_;
	std::vector<GameObject*> enemies_;
	
	void BuildEnemies(int count);
	void BuildTorpedo();
	void BuildPlayer();
	void BuildAsteroid();
	void BuildEnemy();
	void BuildEnvironment();
	void BuildEdge(b2World * world, b2Vec2 v0, b2Vec2 v1);
	void SpawnPlayer();

	gef::Vector2 scroll_speed_ = Vector2(0, 0.5f);
	Sprite* space_background_;
	Player* player_;

	GameObject* player_object;
	GameObject* enemy_object;
	GameObject* asteroid_object;
	GameObject* torpedo_object;

	gef::Vector4 player_start_ = Vector4(0, -1, 0);
	gef::Vector4 player_spawn_ = Vector4(0, -5, 0);
	gef::Vector4 player_transfer = Vector4();
	float spawn_timer_ = 0, spawn_time = 3;
	float distance_ = 1.0f;
	int score_ = 0;
	float bounds_x = 10, bounds_y = 6;

	b2World* world_;
};

