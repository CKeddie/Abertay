#include "MainGame.h"

#include <graphics\sprite.h>
#include <scene_app.h>
#include <MeshRenderer.h>
#include <Enemy.h>
#include <float.h>
#include <sstream>
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
	BuildEnvironment();
	BuildPlayer();
	BuildEnemy();

	player_object->SetRotation(Vector4(0, 0, 0));
	player_transfer = player_spawn_;
}

void MainGame::Update(float gameTime)
{
	if (spawn_timer_ < spawn_time)
	{
		/*spawn_timer_+=gameTime;
		player_transfer.Lerp(player_spawn_, player_start_, 0.25F);
		player_object->GetComponent<Rigidbody2D>()->SetPosition(player_transfer);*/
	}

	world_->Step(1, 1, 1);
	player_object->Update(gameTime);
	enemy_object->Update(gameTime);

	if (scene_.input_manager->keyboard()->IsKeyDown(gef::Keyboard::KC_A))
		scroll_speed_.x = Lerp(scroll_speed_.x, scroll_speed_.y, 5 * gameTime);
	else if (scene_.input_manager->keyboard()->IsKeyDown(gef::Keyboard::KC_D))
		scroll_speed_.x = Lerp(scroll_speed_.x, -scroll_speed_.y, 5 * gameTime);
	else 
		scroll_speed_.x = Lerp(scroll_speed_.x, 0, 5 * gameTime);

	space_background_->set_uv_position(space_background_->uv_position() - (scroll_speed_ * gameTime));

	distance_ += 2 * gameTime;
	control_manager_->Update(gameTime, scene_.input_manager);
}

void MainGame::Draw()
{
	//Draw Background
	scene_.sprite_renderer_->Begin(true);

	scene_.sprite_renderer_->DrawSprite(*space_background_);

	scene_.sprite_renderer_->End();

	//Draw UI	
	scene_.renderer_3d_->Begin(false);

	player_object->Render(scene_.renderer_3d_);
	enemy_object->Render(scene_.renderer_3d_);
	
	scene_.renderer_3d_->End();

	scene_.sprite_renderer_->Begin(false);

	if (control_manager_->GetFont())
	{
		control_manager_->GetFont()->RenderText(scene_.sprite_renderer_, gef::Vector4(0.0f, 510.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_LEFT, "Dist: %.1f ly", distance_);	
		control_manager_->GetFont()->RenderText(scene_.sprite_renderer_, gef::Vector4(960.0f, 510.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_RIGHT, "Score: %08d", score_);
	}
	scene_.sprite_renderer_->End();
}

void MainGame::CleanUp()
{
	delete player_object;
	player_object = NULL;

	delete space_background_;
	space_background_ = NULL;
}

void MainGame::BuildEnemies(int count)
{
}

void MainGame::BuildPlayer()
{
	player_object = new GameObject("Player", player_spawn_, gef::Vector4(0,0,0));
	player_object->AddComponent(new MeshRenderer(*player_object,
		scene_.mesh_repository["space_frigate"], 
		scene_.material_repository["space_frigate_color"], 
		gef::Vector4(0, 0, -90)));

	player_object->AddComponent(new Rigidbody2D(*player_object, world_, b2_dynamicBody, 1, 1, PLAYER, ENEMY | BOUNDS));
	player_object->AddComponent(new Player(*player_object, *scene_.input_manager));

	player_ = (player_object->GetComponent<Player>());
}

void MainGame::BuildEnemy()
{
	enemy_object = new GameObject("Enemy", Vector4(0, 4, 0), gef::Vector4(0, 0, 0));
	enemy_object->AddComponent(new MeshRenderer(*enemy_object,
		scene_.mesh_repository["dark_fighter"],
		scene_.material_repository["dark_fighter_color"],
		gef::Vector4(0, 0, 0)));

	enemy_object->AddComponent(new Rigidbody2D(*enemy_object, world_, b2_dynamicBody, 1, 1, ENEMY, PLAYER | ASTEROID));
	enemy_object->AddComponent(new Enemy(*enemy_object));
	enemy_object->GetComponent<Enemy>()->SetDirection(player_object->GetPosition());
}

void MainGame::BuildEnvironment()
{
	space_background_ = scene_.image_repository["space_background"];
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
	fixture->filter.maskBits = PLAYER;

	b2Body* wall = world_->CreateBody(bDef);
	wall->CreateFixture(fixture);
}

void MainGame::SpawnPlayer()
{
	
	//initialize cooldown timer
	//player_->Reset();
}
