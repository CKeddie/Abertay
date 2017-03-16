#include "TitleScreen.h"

#include "scene_app.h"
#include <graphics\sprite.h>

TitleScreen::TitleScreen(SceneApp& scene, gef::Font* font)
	: GameState::GameState(scene, font)
{

}


TitleScreen::~TitleScreen()
{
}

void TitleScreen::Initialize()
{
	Sprite sprite = *scene_.image_Repository["glass_button"];
	button_start_ = new Button(scene_, &SceneApp::PushState, control_manager_->GetFont(), sprite);
	button_start_->Position(Vector4(scene_.platform().width() / 2, scene_.platform().height() / 2, 1));
	button_start_->Text("Start");
	control_manager_->AddControl(button_start_);
}

void TitleScreen::Update(float gameTime)
{
	control_manager_->Update(gameTime, scene_.input_manager);
}

void TitleScreen::Draw()
{
	Sprite* space_background = scene_.image_Repository["space_background"];

	Sprite* warp_background = scene_.image_Repository["title_background"];
	warp_background->set_colour(0xff41180f);
	Sprite* sprite = scene_.image_Repository["title"];
	sprite->set_colour(0xfff2916f);
	//sprite->set_uv_position(sprite->uv_position() - gef::Vector2(0.0f, 0.005f));
	//Draw UI	
	scene_.renderer_3d_->Begin();

	

	scene_.renderer_3d_->End();

	scene_.sprite_renderer_->Begin(false);

	scene_.sprite_renderer_->DrawSprite(*space_background);
	scene_.sprite_renderer_->DrawSprite(*warp_background);
	scene_.sprite_renderer_->DrawSprite(*sprite);

	if(control_manager_)
		control_manager_->Draw(scene_.sprite_renderer_);

	scene_.sprite_renderer_->End();

}

void TitleScreen::CleanUp()
{
	delete control_manager_;
	control_manager_ = NULL;

	delete button_start_;
	button_start_ = NULL;
}
