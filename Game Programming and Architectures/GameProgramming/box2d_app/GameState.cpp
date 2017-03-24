#include "GameState.h"

#include <scene_app.h>

GameState::GameState(SceneApp& scene, gef::Font* font)
	: scene_(scene)
	, control_manager_(NULL)
{
	control_manager_ = new ControlManager(font);
}

GameState::~GameState()
{

}

void GameState::Initialize()
{

}

void GameState::Update(float gameTime)
{
}

void GameState::Draw()
{

}

void GameState::CleanUp()
{

}
