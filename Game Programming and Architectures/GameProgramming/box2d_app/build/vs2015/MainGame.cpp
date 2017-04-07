#include "MainGame.h"

#include <graphics\sprite.h>
#include <scene_app.h>
#include <MeshRenderer.h>
#include <Enemy.h>
#include <float.h>
#include <sstream>
#include <Entity.h>
#include <Asteroid.h>
#include <Projectile.h>
using namespace std;

MainGame::MainGame(SceneApp& scene, gef::Font* font)
	: GameState(scene, font)
	, player_(NULL)
{
}


MainGame::~MainGame()
{
}

void MainGame::Initialize()
{
	//Setup spawn points
	enemy_spawns_.resize(5);
	enemy_spawns_[0] = gef::Vector4(bounds_x, bounds_y, 0);
	enemy_spawns_[1] = gef::Vector4(bounds_x / 2, bounds_y, 0);
	enemy_spawns_[2] = gef::Vector4(-bounds_x, bounds_y, 0);
	enemy_spawns_[3] = gef::Vector4(-bounds_x, bounds_y / 2, 0);
	enemy_spawns_[4] = gef::Vector4(bounds_x, bounds_y / 2, 0);

	BuildEnvironment();
	BuildTorpedo();
	BuildPlayer();
	BuildEnemy();
	BuildAsteroid();
}

void MainGame::Update(float gameTime)
{
	spawn_timer_ += gameTime;
	if (spawn_timer_ >= spawn_time)
	{
		spawn_timer_ = 0;
		int i = rand() % enemy_spawns_.size();
		asteroid_object->Reset(enemy_spawns_[i]);
	}

	world_->Step(1, 1, 1);
	player_object->Update(gameTime);
	enemy_object->Update(gameTime);
	asteroid_object->Update(gameTime);
	//torpedo_object->Update(gameTime);

	if (scene_.GetInputManager()->keyboard()->IsKeyDown(gef::Keyboard::KC_A))
		scroll_speed_.x = gef::Lerp(scroll_speed_.x, scroll_speed_.y, 5 * gameTime);
	else if (scene_.GetInputManager()->keyboard()->IsKeyDown(gef::Keyboard::KC_D))
		scroll_speed_.x = gef::Lerp(scroll_speed_.x, -scroll_speed_.y, 5 * gameTime);
	else 
		scroll_speed_.x = gef::Lerp(scroll_speed_.x, 0, 5 * gameTime);

	space_background_->set_uv_position(space_background_->uv_position() - (scroll_speed_ * gameTime));

	distance_ += 2 * gameTime;
	control_manager_->Update(gameTime, scene_.GetInputManager());

	/*if (!player_object->IsAlive())
	{
		scene_.PopState();
	}*/
}

void MainGame::Draw()
{
	//Draw Background
	scene_.GetSpriteRenderer()->Begin(false);

	scene_.GetSpriteRenderer()->DrawSprite(*space_background_);

	scene_.GetSpriteRenderer()->End();

	//Draw UI	
	scene_.GetRenderer()->Begin(true);

	player_object->Render(scene_.GetRenderer());
	enemy_object->Render(scene_.GetRenderer());
	asteroid_object->Render(scene_.GetRenderer());
	//torpedo_object->Render(scene_.GetRenderer());

	scene_.GetRenderer()->End();

	scene_.GetSpriteRenderer()->Begin(false);

	if (control_manager_->GetFont())
	{
		control_manager_->GetFont()->RenderText(scene_.GetSpriteRenderer(), gef::Vector4(0.0f, 510.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_LEFT, "Dist: %.1f ly", distance_);
		control_manager_->GetFont()->RenderText(scene_.GetSpriteRenderer(), gef::Vector4(960.0f, 510.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_RIGHT, "Score: %08d", score_);
	}

	DrawPlayerLives();

	scene_.GetSpriteRenderer()->End();
}

void MainGame::CleanUp()
{
	delete player_object;
	player_object = NULL;

	//delete space_background_;
	//space_background_ = NULL;
}

void MainGame::BuildEnemies(int count)
{

}

void MainGame::BuildTorpedo()
{
	torpedo_object = new Projectile();
	torpedo_object->GetTransform()->Initialize(gef::Vector4(0,0,-10), gef::Vector4(0, 0, 0), gef::Vector4(1, 1, 1));
	torpedo_object->GetMeshRenderer()->Initialize(scene_.GetMesh("torpedo"), gef::Vector4(0, 0, -1), gef::Vector4(0, 0, 0), gef::Vector4(1, 1, 1));
	torpedo_object->GetRigidBody()->Initialize(torpedo_object, world_, b2_dynamicBody, 0.5f, 0.5f, PROJECTILE, ENEMY | ASTEROID | BOUNDS);
	torpedo_object->SetHealth(1);
}

void MainGame::BuildPlayer()
{
	player_object = new Player(*scene_.GetInputManager());
	player_object->GetTransform()->Initialize(player_spawn_, gef::Vector4(0, 0, 0), gef::Vector4(1, 1, 1));
	player_object->GetMeshRenderer()->Initialize(scene_.GetMesh("space_frigate"), gef::Vector4(0, 0, 0), gef::Vector4(0, 0, -90), gef::Vector4(1, 1, 1));
	player_object->GetRigidBody()->Initialize(player_object, world_, b2_dynamicBody, 0.5f, 0.5f, PLAYER, ENEMY | BOUNDS | ASTEROID);
	player_object->SetHealth(3);
	player_object->SetProjectile(torpedo_object);
}

void MainGame::BuildAsteroid()
{	
	asteroid_object = new Asteroid();
	asteroid_object->GetTransform()->Initialize(enemy_spawns_[1], gef::Vector4(0, 0, 0), gef::Vector4(1, 1, 1));
	asteroid_object->GetMeshRenderer()->Initialize(scene_.GetMesh("asteroid"), gef::Vector4(0, 0, 0), gef::Vector4(0, 0, -90), gef::Vector4(1, 1, 1));
	asteroid_object->GetRigidBody()->Initialize(asteroid_object, world_, b2_dynamicBody, 1, 1, ASTEROID, PLAYER | ENEMY | ASTEROID);
}

void MainGame::BuildEnemy()
{
	enemy_object = new Enemy();
	enemy_object->GetTransform()->Initialize(enemy_spawns_[0], gef::Vector4(0, 0, 0), gef::Vector4(1, 1, 1));
	enemy_object->GetMeshRenderer()->Initialize(scene_.GetMesh("dark_fighter"), gef::Vector4(0, 0, 0), gef::Vector4(0, 0, 90), gef::Vector4(1, 1, 1));
	enemy_object->GetRigidBody()->Initialize(enemy_object, world_, b2_dynamicBody, 0.5f, 0.5f, ENEMY, PLAYER | ASTEROID);\
}

void MainGame::BuildEnvironment()
{
	space_background_ = scene_.GetImage("space_background");
	world_ = new b2World(b2Vec2(0, 0));

	BuildEdge(world_, b2Vec2( bounds_x,  bounds_y), b2Vec2( bounds_x, -bounds_y));
	BuildEdge(world_, b2Vec2(-bounds_x,  bounds_y), b2Vec2(-bounds_x, -bounds_y));
	BuildEdge(world_, b2Vec2(-bounds_x,  bounds_y), b2Vec2( bounds_x,  bounds_y));
	BuildEdge(world_, b2Vec2(-bounds_x, -bounds_y), b2Vec2( bounds_x, -bounds_y));
}

void MainGame::BuildEdge(b2World* world, b2Vec2 v0, b2Vec2 v1)
{
	b2BodyDef* bDef = new b2BodyDef();
	bDef->type = b2_staticBody;
	//bDef->position = b2Vec2(7, 0);

	b2EdgeShape* edge = new b2EdgeShape();
	edge->Set(v0, v1);

	b2FixtureDef* fixture = new b2FixtureDef();
	fixture->density = 1.0f;
	fixture->shape = edge;
	fixture->filter.categoryBits = BOUNDS;
	fixture->filter.maskBits     = PLAYER;

	b2Body* wall = world_->CreateBody(bDef);
	wall->CreateFixture(fixture);
}

void MainGame::DrawPlayerLives()
{
	if (!player_object)
		return;

	gef::Sprite* sprite = scene_.GetImage("player_lives");
	
	int width = scene_.platform().width() / 7;
	int player_health = player_object->GetHealth();
	for (int i = 0; i < (player_health); i++)
	{
		sprite->set_position((i + 2)*width+64, scene_.platform().height() - 32, 0);
		scene_.GetSpriteRenderer()->DrawSprite(*sprite);
	}
}

void MainGame::SpawnPlayer()
{
	
	//initialize cooldown timer
	//player_->Reset();
}
