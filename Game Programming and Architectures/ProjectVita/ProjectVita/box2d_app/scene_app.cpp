#include "scene_app.h"
#include <system/platform.h>
#include <graphics/sprite_renderer.h>
#include <graphics/font.h>
#include <system/debug_log.h>
#include <graphics/renderer_3d.h>
#include <maths/math_utils.h>
#include <assets/obj_loader.h>
#include <graphics/model.h>

Camera camera_(gef::Vector4(0,0,5));
gef::MeshInstance mInst;

SceneApp::SceneApp(gef::Platform& platform) :
	Application(platform),
	sprite_renderer_(NULL),
	renderer_3d_(NULL),
	primitive_builder_(NULL),
	font_(NULL),
	input_manager(NULL)
{
}

void SceneApp::Init()
{
	sprite_renderer_ = gef::SpriteRenderer::Create(platform_);
	input_manager = gef::InputManager::Create(platform_);
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

	
	//if (obj_loader_->Load("models/wolf/wolf.obj", platform_, starship_))
	//{
	//	if (starship_.mesh())
	//	{			
	//		player_.set_mesh(starship_.mesh());
	//	}
	//}
	InitFont();
	SetupLights();
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

	input_manager->Update();
	Keyboard* kb = input_manager->keyboard();
	if (kb->IsKeyPressed(gef::Keyboard::KC_ESCAPE))
		return false;

	gef::Matrix44 player_transform;
	player_transform.SetIdentity();
	player_transform.Scale(Vector4(1, 1, 1));
	player_.set_transform(player_transform);	

	camera_.Input(kb, frame_time);
	camera_.Update(fps_);
	return true;
}

void SceneApp::Render()
{
	camera_.Render(renderer_3d_, platform_);

	// draw 3d geometry
	renderer_3d_->Begin();
	
	renderer_3d_->set_override_material(&primitive_builder_->red_material());
	renderer_3d_->DrawMesh(player_);
	renderer_3d_->set_override_material(NULL);

	renderer_3d_->End();

	// start drawing sprites, but don't clear the frame buffer
	sprite_renderer_->Begin(false);
	sprite_renderer_->DrawSprite(sprite_);
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
		// display frame rate
		font_->RenderText(sprite_renderer_, gef::Vector4(850.0f, 510.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_LEFT, "FPS: %.1f", fps_);
		//font_->RenderText(sprite_renderer_, gef::Vector4(850.0f, 510.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_LEFT, "Camera Position: %",);
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
