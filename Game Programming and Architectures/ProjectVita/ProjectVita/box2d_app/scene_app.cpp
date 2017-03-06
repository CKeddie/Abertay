#include "scene_app.h"
#include <system/platform.h>
#include <graphics/sprite_renderer.h>
#include <graphics/font.h>
#include <system/debug_log.h>
#include <graphics/renderer_3d.h>
#include <maths/math_utils.h>
#include <assets/obj_loader.h>
#include <graphics/model.h>

#include <audio\audio_manager.h>

#include <Rigidbody2D.h>

#include <MeshRenderer.h>

#include <graphics\mesh.h>

Camera camera_(gef::Vector4(0,0,10), Vector4(0,0,0));
gef::MeshInstance mInst;

SceneApp::SceneApp(gef::Platform& platform) :
	Application(platform),
	sprite_renderer_(NULL),
	renderer_3d_(NULL),
	primitive_builder_(NULL),
	font_(NULL),
	input_manager(NULL),
	control_manager(NULL),	
	audio_manager_(NULL),
	world_(NULL)
{

}

void SceneApp::Init()
{
	sprite_renderer_ = gef::SpriteRenderer::Create(platform_);
	input_manager = gef::InputManager::Create(platform_);
	// audio_manager_ = gef::AudioManager::Create();
	// create the renderer for draw 3D geometry
	renderer_3d_ = gef::Renderer3D::Create(platform_);

	// initialise primitive builder to make create some 3D geometry easier
	primitive_builder_ = new PrimitiveBuilder(platform_);

	// setup the mesh for the player
	player_.set_mesh(primitive_builder_->GetDefaultCubeMesh());
	

	gef::ImageData data;

	png_loader_->Load("textures/hydra.png", platform_, data);

	sprite_.set_texture(Texture::Create(platform_, data));
	sprite_.set_position(50, 50, 100);
	sprite_.set_width(data.width());
	sprite_.set_height(data.height());
		
	InitFont();
	SetupLights();

	control_manager.SetFont(font_);

	//UI Setup
	button_ = new Button(sprite_, "Button1", Vector4(platform_.width() / 2, platform_.height() / 2, 0), Vector4(0, 0, 0), font_);
	control_manager.AddControl(button_);
	button_ = new Button(sprite_, "Button2", Vector4(platform_.width() / 3, platform_.height() / 2, 0), Vector4(0, 0, 0), font_);
	control_manager.AddControl(button_);
	button_ = new Button(sprite_, "Button3", Vector4((platform_.width() * 2) / 3, platform_.height() / 2, 0), Vector4(0, 0, 0), font_);
	control_manager.AddControl(button_);

	//initialize physics simulation
	b2Vec2 gravity = b2Vec2(0, -0.81f);
	world_ = new b2World(gravity);
	BuildPlayer();
	BuildLevel();
}

void SceneApp::CleanUp()
{
	CleanUpFont();

	delete primitive_builder_;
	primitive_builder_ = NULL;

	delete renderer_3d_;
	renderer_3d_ = NULL;

	delete sprite_renderer_;
	sprite_renderer_ = NULL;
}

bool SceneApp::Update(float frame_time)
{
	fps_ = 1.0f / frame_time;

	if (!input_manager)
		return true;
	
	//update physics simulation
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIter = 6;
	int32 positionIter = 2;

	world_->Step(timeStep, velocityIter, positionIter);
	//

	//Update UI controls
	input_manager->Update();
	control_manager.Update(frame_time, input_manager);
	//

	//Update input
	Keyboard* kb = input_manager->keyboard();

	//if escape pressed exit application
	if (kb->IsKeyPressed(gef::Keyboard::KC_ESCAPE))
		return false;
	
	_player.Yaw(45);
	_player.Update(frame_time);
	_ground.Update(frame_time);


	camera_.Input(kb, frame_time);
	camera_.Update(fps_);
	return true;
}

void SceneApp::Render()
{
	camera_.Render(renderer_3d_, platform_);

	// draw 3d geometry
	renderer_3d_->Begin();

	//Render player components
	renderer_3d_->set_override_material(&primitive_builder_->blue_material());
	_player.Render(renderer_3d_); 
	renderer_3d_->set_override_material(&primitive_builder_->red_material());
	_ground.Render(renderer_3d_);
	renderer_3d_->set_override_material(NULL);
	//-----------------------

	renderer_3d_->End();

	// start drawing sprites, but don't clear the frame buffer
	sprite_renderer_->Begin(false);

	//Draw controls within control manager
	control_manager.Draw(sprite_renderer_);
		
	DrawHUD();
	sprite_renderer_->End();
}

void SceneApp::InitFont()
{
	font_ = new gef::Font(platform_);
	font_->Load("comic_sans");
}

void SceneApp::CleanUpFont()
{
	delete font_;
	font_ = NULL;
	
}

void SceneApp::DrawHUD()
{
	if(font_)
	{
		Vector4 v = _ground.GetPosition();
		//Vector4 v1 = camera_.GetTransformMatrix().GetRow(1);
		Vector4 v2 = _player.GetPosition();
		// display frame rate
		//font_->RenderText(sprite_renderer_, gef::Vector4(850.0f, 510.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_LEFT, "FPS: %.1f", fps_);
		font_->RenderText(sprite_renderer_, gef::Vector4(700.0f, 400.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_LEFT, 
			"ground : %.1f, %.1f, %.1f", v.x(), v.y(), v.z());
		//font_->RenderText(sprite_renderer_, gef::Vector4(700.0f, 420.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_LEFT, 
			//"FPS: %.1f, %.1f, %.1f", v1.x(), v1.y(), v1.z()); 
		font_->RenderText(sprite_renderer_, gef::Vector4(700.0f, 440.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_LEFT, 
			"player : %.1f, %.1f, %.1f", v2.x(), v2.y(), v2.z());
	}
}

void SceneApp::SetupLights()
{
	// grab the data for the default shader used for rendering 3D geometry
	gef::Default3DShaderData& default_shader_data = renderer_3d_->default_shader_data();

	// set the ambient light
	default_shader_data.set_ambient_light_colour(gef::Colour(0.25f, 0.25f, 0.25f, 1.0f));

	// add a point light that is almost white, but with a blue tinge
	// the position of the light is set far away so it acts light a directional light
	gef::PointLight default_point_light;
	default_point_light.set_colour(gef::Colour(0.7f, 0.7f, 1.0f, 1.0f));
	default_point_light.set_position(gef::Vector4(-500.0f, 400.0f, 700.0f));
	default_shader_data.AddPointLight(default_point_light);
}

void SceneApp::BroadPhase()
{

}

void SceneApp::BuildLevel()
{		
	ground_.set_mesh(primitive_builder_->GetDefaultCubeMesh());	
	_ground.AddComponent(new MeshRenderer(_ground, &ground_));
	_ground.AddComponent(new Rigidbody2D(_ground, world_, b2_staticBody, 0.5f, 0.5f));
}

void SceneApp::BuildPlayer()
{ 	
		
	player_.set_mesh(primitive_builder_->GetDefaultCubeMesh());
	_player.AddComponent(new MeshRenderer(_player, &player_));
	_player.AddComponent(new Rigidbody2D(_player, world_, b2_dynamicBody, 0.5f, 0.5f));
}
