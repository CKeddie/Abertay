#pragma once

#include "GameState.h"
#include "maths\vector4.h"

#include "GameObject.h"
#include "MeshRenderer.h"
#include "box2d\Box2D.h"

#include <Player.h>
#include<Enemy.h>
#include <Asteroid.h>
#include <Projectile.h>

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
	void BuildEnemies(int count);
	void BuildTorpedo();
	void BuildPlayer();
	void BuildAsteroid();
	void BuildEnemy();
	void BuildEnvironment();
	void BuildEdge(b2World * world, b2Vec2 v0, b2Vec2 v1);
	void DrawPlayerLives();
	void SpawnPlayer();

	gef::Vector2 scroll_speed_ = gef::Vector2(0, 0.5f);
	gef::Sprite* space_background_;
	gef::Sprite* gameover_sprite_;

	Player* player_object;
	Enemy* enemy_object;
	Asteroid* asteroid_object;
	Projectile* torpedo_object;

	std::vector<gef::Vector4> asteroid_spawns_;
	std::vector<gef::Vector4> enemy_spawns_;
	std::vector<Enemy*> enemies_;

	gef::Vector4 player_start_ = gef::Vector4(0, -1, 0);
	gef::Vector4 player_spawn_ = gef::Vector4(0, 0, 0);
	gef::Vector4 player_transfer = gef::Vector4();
	float asteroid_spawn_timer_ = 0, asteroid_spawn_time = 3;
	float enemy_spawn_timer_ = 0, enemy_spawn_time = 3;
	float distance_ = 1.0f;
	int score_ = 0;
	float bounds_x = 8, bounds_y = 5;
	bool tally_score = false;
	bool game_over = false;
	b2World* world_;
};

