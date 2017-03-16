#include "MainGame.h"

#include <graphics\sprite.h>
#include <scene_app.h>

MainGame::MainGame(SceneApp& scene, gef::Font* font) 
	: GameState(scene, font)
{
}


MainGame::~MainGame()
{
}

void MainGame::Initialize()
{
}

void MainGame::Update(float gameTime)
{
	//update player
	//update enemies
	
	//--game condition--//

	//if enemy hit lose 1 life
	//if enemy health <= 0 then destroy and increment score

	//if player hit then remove 1 life
	//if player health < 0 then display high score and return to main menu (pop state)

	if (true)
	{

	}
}

void MainGame::Draw()
{
	gef::Sprite* sprite = scene_.image_Repository["space_background"];
	sprite->set_uv_position(sprite->uv_position() - gef::Vector2(0.0f, 0.005f));
	//Draw UI	
	scene_.renderer_3d_->Begin();

	scene_.renderer_3d_->End();

	scene_.sprite_renderer_->Begin(false);

	scene_.sprite_renderer_->DrawSprite(*sprite);
	if (control_manager_)
		control_manager_->Draw(scene_.sprite_renderer_);

	scene_.sprite_renderer_->End();
}

void MainGame::CleanUp()
{
}

void MainGame::BuildEnemies(int count)
{
}

void MainGame::BuildPlayer()
{
}

void MainGame::BuildEnvironment()
{
}
