#include "TitleScreen.h"

#include "scene_app.h"
#include <graphics\sprite.h>
#include <maths\math_utils.h>

TitleScreen::TitleScreen(SceneApp& scene, gef::Font* font)
	: GameState::GameState(scene, font)
{

}


TitleScreen::~TitleScreen()
{
}

void TitleScreen::Initialize()
{
	gef::Sprite sprite = *scene_.GetImage("glass_button");
	sprite.set_height(64);
	sprite.set_width(96);
	sprite.set_position(gef::Vector4(scene_.platform().width() / 2, scene_.platform().height() / 2, 0));
	button_start_ = new Button(scene_, &SceneApp::PushState, control_manager_->GetFont(), sprite);
	button_start_->Position(gef::Vector4(scene_.platform().width() / 2, scene_.platform().height() / 2, 0));
	button_start_->Text("Start");
	control_manager_->AddControl(button_start_);

	space_background_ = scene_.GetImage("space_background");
	space_background_->set_position(scene_.platform().width() / 2, scene_.platform().height() / 2, 0);
	warp_background_ = scene_.GetImage("title_background");
	warp_background_->set_position(scene_.platform().width() / 2, scene_.platform().height() / 2, 0);
	title_sprite_ = scene_.GetImage("title");
	title_sprite_->set_position(scene_.platform().width() / 2, scene_.platform().height() / 2, 0);

	warp_background_->set_colour(0xff41180f);
	title_sprite_->set_colour(0xfff2916f);
}

void TitleScreen::Update(float gameTime)
{
	deg += 1;
	
	if (deg >= 360)
		deg = 0;

	float x = sinf(gef::DegToRad(deg));
	float y = cosf(gef::DegToRad(deg));
	space_background_->set_uv_position(space_background_->uv_position() + gef::Vector2(x, y) * (gameTime*0.05f));
	control_manager_->Update(gameTime, scene_.GetInputManager());
}

void TitleScreen::Draw()
{
	//Draw UI	
	scene_.GetRenderer()->Begin();

	scene_.GetRenderer()->End();

	scene_.GetSpriteRenderer()->Begin(false);

	
	scene_.GetSpriteRenderer()->DrawSprite(*space_background_);
	scene_.GetSpriteRenderer()->DrawSprite(*warp_background_);
	scene_.GetSpriteRenderer()->DrawSprite(*title_sprite_);
	if(control_manager_)
		control_manager_->Draw(scene_.GetSpriteRenderer());


	scene_.GetSpriteRenderer()->End();
}

void TitleScreen::CleanUp()
{
	delete control_manager_;
	control_manager_ = NULL;

	delete button_start_;
	button_start_ = NULL; 

	delete space_background_;
	space_background_ = NULL;

	delete warp_background_;
	warp_background_ = NULL;

	delete title_sprite_;
	title_sprite_ = NULL;
}
