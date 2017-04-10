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
{
}


MainGame::~MainGame()
{
}

void MainGame::Initialize()
{
	//Setup spawn points
	asteroid_spawns_.resize(2);
	asteroid_spawns_[0] = gef::Vector4(bounds_x, bounds_y, 0);
	asteroid_spawns_[1] = gef::Vector4(-bounds_x, bounds_y, 0); 
	
	enemy_spawns_.resize(3);
	enemy_spawns_[0] = gef::Vector4( bounds_x - 4 , bounds_y, 0);
	enemy_spawns_[1] = gef::Vector4( 0, bounds_y + 4, 0);
	enemy_spawns_[2] = gef::Vector4(-bounds_x + 4 , bounds_y, 0);
											       
	BuildEnvironment();
	BuildTorpedo();
	BuildPlayer();
	BuildEnemy();
	BuildAsteroid();
}

void MainGame::Update(float gameTime)
{
	asteroid_spawn_timer_ += gameTime;

	enemy_spawn_timer_ += gameTime;

	if (asteroid_spawn_timer_ >= asteroid_spawn_time)
	{

		asteroid_spawn_timer_ = 0;
		int i = rand() % asteroid_spawns_.size();
		asteroid_object->Reset(asteroid_spawns_[i]);
	}

	if (enemy_spawn_timer_ >= enemy_spawn_time)
	{	
		enemy_spawn_timer_ = 0;
		int j = rand() % enemy_spawns_.size();
		enemy_object->Reset(enemy_spawns_[j]);
	}
	

	world_->Step(1, 1, 1);
	player_object->Update(gameTime);
	asteroid_object->Update(gameTime);

	//for (int i = 0; i < enemies_.size(); i++)
	enemy_object->Update(gameTime);

	if (scene_.GetInputManager()->keyboard()->IsKeyDown(gef::Keyboard::KC_A))
		scroll_speed_.x = gef::Lerp(scroll_speed_.x, scroll_speed_.y, 5 * gameTime);
	else if (scene_.GetInputManager()->keyboard()->IsKeyDown(gef::Keyboard::KC_D))
		scroll_speed_.x = gef::Lerp(scroll_speed_.x, -scroll_speed_.y, 5 * gameTime);
	else 
		scroll_speed_.x = gef::Lerp(scroll_speed_.x, 0, 5 * gameTime);

	space_background_->set_uv_position(space_background_->uv_position() - (scroll_speed_ * gameTime));

	distance_ += 2 * gameTime;
	control_manager_->Update(gameTime, scene_.GetInputManager());

	if (!player_object->IsAlive())
	{
		game_over = true;
		if (!tally_score)
		{
			tally_score = true;
			score_ = score_ + (int)distance_;
		}//scene_.PopState();
	}

	score_ = player_object->GetScore();
}

void MainGame::Draw()
{
	//Draw Background
	scene_.GetSpriteRenderer()->Begin(false);

	scene_.GetSpriteRenderer()->DrawSprite(*space_background_);
		scene_.GetSpriteRenderer()->End();

	if (!game_over)
	{
		//Draw UI	
		scene_.GetRenderer()->Begin(false);

		player_object->Render(scene_.GetRenderer());
		//for (int i = 0; i < enemies_.size(); i++)
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
	else
	{
		scene_.GetSpriteRenderer()->Begin(false);

		scene_.GetSpriteRenderer()->DrawSprite(*gameover_sprite_);
		scene_.GetRenderer()->End();
	}
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
	float maxX = 0.5f;
	float maxY = 0.5f;
	torpedo_object = new Projectile(gef::Vector4(0,0,0));
	torpedo_object->GetTransform()->Initialize(gef::Vector4(0, 0, -10), gef::Vector4(0, 0, 0), gef::Vector4(1, 1, 1));
	torpedo_object->GetMeshRenderer()->Initialize(scene_.GetMesh("torpedo"), gef::Vector4(0, 0, -1), gef::Vector4(0, 0, 0), gef::Vector4(1, 1, 1));
	torpedo_object->GetRigidBody()->Initialize(torpedo_object, world_, b2_dynamicBody, maxX, maxY, PROJECTILE, ENEMY | ASTEROID | BOUNDS);
	torpedo_object->SetHealth(1);
}

void MainGame::BuildPlayer()
{
	float maxX = 1.0f;
	float maxY = 1.0f;
	player_object = new Player(*scene_.GetInputManager());
	player_object->GetTransform()->Initialize(player_spawn_, gef::Vector4(0, 0, 0), gef::Vector4(1, 1, 1));
	player_object->GetMeshRenderer()->Initialize(scene_.GetMesh("space_frigate"), gef::Vector4(0, 0, 0), gef::Vector4(0, 0, -90), gef::Vector4(1, 1, 1));
	player_object->GetRigidBody()->Initialize(player_object, world_, b2_dynamicBody, maxX, maxY, PLAYER, BOUNDS | ASTEROID | ENEMY);
	player_object->SetHealth(3);
	player_object->SetProjectile(torpedo_object);
	torpedo_object->SetSpawnPoint(player_object->GetTransform()->GetPosition());
}

void MainGame::BuildAsteroid()
{
	float maxX = 1;
	float maxY = 1;
	asteroid_object = new Asteroid(gef::Vector4(0, 0, 0));
	asteroid_object->GetTransform()->Initialize(asteroid_spawns_[1], gef::Vector4(0, 0, 0), gef::Vector4(1, 1, 1));
	asteroid_object->GetMeshRenderer()->Initialize(scene_.GetMesh("asteroid"), gef::Vector4(0, 0, 0), gef::Vector4(0, 0, -90), gef::Vector4(1, 1, 1));
	asteroid_object->GetRigidBody()->Initialize(asteroid_object, world_, b2_dynamicBody, maxX, maxY, ASTEROID, PLAYER | ASTEROID | PROJECTILE);
}

void MainGame::BuildEnemy()
{
	float maxX = 0.75f;
	float maxY = 0.75f;
	enemy_object = new Enemy(gef::Vector4(0, 0, 0));
	enemy_object->GetTransform()->Initialize(asteroid_spawns_[1], gef::Vector4(0, 0, 0), gef::Vector4(1, 1, 1));
	enemy_object->GetMeshRenderer()->Initialize(scene_.GetMesh("dark_fighter"), gef::Vector4(0, 0, 0), gef::Vector4(0, 0, 90), gef::Vector4(1, 1, 1));
	enemy_object->GetRigidBody()->Initialize(enemy_object, world_, b2_dynamicBody, maxX, maxY, ENEMY, PLAYER | PROJECTILE);

	//for (int i = 0; i < 3; i++)
	//{
	//	enemies_.push_back(new Enemy(*enemy_object));
	//	enemies_[i]->GetRigidBody()->ToggleMask((uint16)enemies_[i]->GetRigidBody()->GetCollisionMask());
	//}
}

void MainGame::BuildEnvironment()
{
	space_background_ = scene_.GetImage("space_background");
	space_background_->set_position(scene_.platform().width() / 2, scene_.platform().height() / 2, 1);
	gameover_sprite_ = scene_.GetImage("alien_skull");
	gameover_sprite_->set_position(scene_.platform().width() / 2, scene_.platform().height() / 2, 1);
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
	fixture->filter.maskBits     = PLAYER | PROJECTILE;

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
