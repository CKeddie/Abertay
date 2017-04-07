#include "MenuScreen.h"

#include <scene_app.h>

MenuScreen::MenuScreen(SceneApp& scene, gef::Font* font)
	: GameState::GameState(scene, font)
	, space_background_(NULL)
{

}

MenuScreen::~MenuScreen()
{
}

void MenuScreen::Initialize()
{
	space_background_ = scene_.GetImage("space_background");
	
	gef::Sprite sprite_0 = *scene_.GetImage("glass_button");
	sprite_0.set_width(144);	
	sprite_0.set_height(96);
	start_game_ = new Button(scene_, &SceneApp::PushState, control_manager_->GetFont(), sprite_0);
	
	start_game_->Position(gef::Vector4((scene_.platform().width() / 3), (scene_.platform().height() / 4) * 2, 0));
	start_game_->Text("Start Game");
	start_game_->SetFocus(true);
	control_manager_->AddControl(start_game_);


	gef::Sprite sprite_1 = *scene_.GetImage("glass_button");
	sprite_1.set_width(128);
	sprite_1.set_height(96);
	quit_ = new Button(scene_, &SceneApp::Quit, control_manager_->GetFont(),sprite_1);
	quit_->Position(gef::Vector4((scene_.platform().width() / 3), (scene_.platform().height() / 4) * 3, 0));
	quit_->Text("Quit");	
	quit_->SetFocus(false);
	control_manager_->AddControl(quit_);
}

void MenuScreen::Update(float gameTime)
{
	space_background_->set_uv_position(space_background_->uv_position() - scroll_speed_);
	control_manager_->Update(gameTime, scene_.GetInputManager());
}

void MenuScreen::Draw()
{

	//Draw UI	
	scene_.GetRenderer()->Begin();
	scene_.GetRenderer()->End();

	scene_.GetSpriteRenderer()->Begin(false);
	
 	scene_.GetSpriteRenderer()->DrawSprite(*space_background_);
	if (control_manager_)
		control_manager_->Draw(scene_.GetSpriteRenderer());

	scene_.GetSpriteRenderer()->End();
}

void MenuScreen::CleanUp()
{
	delete control_manager_;
	control_manager_ = NULL;

	delete start_game_;
	start_game_ = NULL;

	delete quit_;
	quit_ = NULL;

	//delete space_background_;
	//space_background_ = NULL;
}
