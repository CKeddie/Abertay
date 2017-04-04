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
	space_background_ = scene_.image_repository["space_background"];
	
	start_game_ = new Button(scene_, &SceneApp::PushState, control_manager_->GetFont(), *scene_.image_repository["glass_button"]);
	start_game_->Position(Vector4((scene_.platform().width() / 3), (scene_.platform().height() / 4) * 2, 0));
	start_game_->Text("Start Game");
	start_game_->SetFocus(true);
	control_manager_->AddControl(start_game_);

	quit_ = new Button(scene_, &SceneApp::Quit, control_manager_->GetFont(), *scene_.image_repository["glass_button"]);
	quit_->Position(Vector4((scene_.platform().width() / 3), (scene_.platform().height() / 4) * 3, 0));
	quit_->Text("Quit");	
	quit_->SetFocus(false);
	control_manager_->AddControl(quit_);
}

void MenuScreen::Update(float gameTime)
{
	space_background_->set_uv_position(space_background_->uv_position() - scroll_speed_);
	control_manager_->Update(gameTime, scene_.input_manager);
}

void MenuScreen::Draw()
{

	//Draw UI	
	scene_.renderer_3d_->Begin();
	scene_.renderer_3d_->End();

	scene_.sprite_renderer_->Begin(false);
	
 	scene_.sprite_renderer_->DrawSprite(*space_background_);
	if (control_manager_)
		control_manager_->Draw(scene_.sprite_renderer_);

	scene_.sprite_renderer_->End();
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
