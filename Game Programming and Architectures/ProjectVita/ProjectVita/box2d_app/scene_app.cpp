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

Camera camera_(gef::Vector4(0,0,10), Vector4(0,0,0), Vector4(1,1,1));
gef::MeshInstance mInst;

SceneApp::SceneApp(gef::Platform& platform) :
	Application(platform),
	sprite_renderer_(NULL),
	renderer_3d_(NULL),
	primitive_builder_(NULL),
	font_(NULL),
	input_manager(NULL),
	audio_manager_(NULL)
{

}

void SceneApp::Init()
{
	// 
	sprite_renderer_ = gef::SpriteRenderer::Create(platform_);
	// input manager for user input
	input_manager = gef::InputManager::Create(platform_);
	// create the renderer for draw 3D geometry
	renderer_3d_ = gef::Renderer3D::Create(platform_);

	// audio_manager_ = gef::AudioManager::Create();

	// initialise primitive builder to make create some 3D geometry easier
	primitive_builder_ = new PrimitiveBuilder(platform_);

	

	InitFont();
	SetupLights();

	//LoadStuff
	LoadImages();
	LoadModels();

	//Initialize
	PushState();

	//sprite_.set_texture(Texture::Create(platform_, data));
	//sprite_.set_position(50, 50, 100);
	//sprite_.set_width(data.width());
	//sprite_.set_height(data.height());
	//	
	////UI Setup	
	//Button* button_ = new Button(*this, &SceneApp::PushState, font_, sprite);
	//button_->Position(Vector4(platform_.width() / 2, platform_.height() / 2, 0));
	//button_->Name("Start Game");

	////initialize physics simulation
	//b2Vec2 gravity = b2Vec2(0, 0);
	//world_ = new b2World(gravity);

	//BuildPlayer();
	//BuildLevel();

	//Entity& e = *_player.GetComponent<Player>();
	//SpriteGrid* player_health_gfx_ = new SpriteGrid(*this, NULL, &sprite_, e);
	

}

void SceneApp::LoadModels()
{

}

void SceneApp::PushState()
{
	switch (index_)
	{
		case -1: // no state, push title screen
		{
			TitleScreen* title = new TitleScreen(*this, font_);
			game_states_.push_back(title);
			index_++;
			break;
		}
		case 0: // title screen, push main menu
		{
			MenuScreen* menu = new MenuScreen(*this, font_);
			game_states_.push_back(menu); 
			index_++;
			break;
		}
		case 1: // start game, push gameplay
		{
			MainGame* game = new MainGame(*this, font_);
			game_states_.push_back(game);
			index_++;
			break;
		}
		case 2: // gameplay, do nothing
		{
			break; 
		}
	}
	
	if (index_ >= 0)
		game_states_[index_]->Initialize();
}

void SceneApp::PopState()
{
	if (index_ >= 0)
		game_states_[index_]->CleanUp();
	game_states_.pop_back();
	index_--;
}

void SceneApp::Quit()
{
	is_Running_ = false;
}

void SceneApp::LoadImages()
{
	gef::ImageData data;
	gef::Sprite* sprite = new Sprite();

	//Load Hydra PNG
	png_loader_->Load("textures/glassPanel.png", platform_, data);
	sprite->set_texture(gef::Texture::Create(platform_, data));
	sprite->set_width(128);//data.width());
	sprite->set_height(128);////data.height());
	sprite->set_position(Vector4(platform_.width() / 2, platform_.height() / 2, 0));

	//Store sprite for later use
	image_Repository.insert(std::pair<string, Sprite*>("glass_button", sprite));

	//Load Space Texture PNG
	gef::ImageData space_data;
	gef::Sprite* space_sprite = new Sprite();

	png_loader_->Load("textures/seamless space_0.png", platform_, space_data);
	space_sprite->set_texture(gef::Texture::Create(platform_, space_data));
	space_sprite->set_width(space_data.width() - 64);
	space_sprite->set_height(space_data.height());
	space_sprite->set_position(Vector4(platform_.width() / 2, platform_.height() / 2, 1));
	image_Repository.insert(std::pair<string, Sprite*>("space_background", space_sprite));

	gef::ImageData galaxy_rush_data;
	gef::Sprite* galaxy_sprite = new Sprite();

	png_loader_->Load("textures/GalaxyRush.png", platform_, galaxy_rush_data);
	galaxy_sprite->set_texture(gef::Texture::Create(platform_, galaxy_rush_data));
	galaxy_sprite->set_width(galaxy_rush_data.width());
	galaxy_sprite->set_height(galaxy_rush_data.height());
	galaxy_sprite->set_position(Vector4(platform_.width() / 2, platform_.height() / 2, 1));
	image_Repository.insert(std::pair<string, Sprite*>("title", galaxy_sprite));

	gef::ImageData lightSpeed_data;
	gef::Sprite* lightSpeed_sprite = new Sprite();

	png_loader_->Load("textures/LightSpeed.png", platform_, lightSpeed_data);
	lightSpeed_sprite->set_texture(gef::Texture::Create(platform_, lightSpeed_data));
	lightSpeed_sprite->set_width(lightSpeed_data.width());
	lightSpeed_sprite->set_height(lightSpeed_data.height());
	lightSpeed_sprite->set_position(Vector4(platform_.width() / 2, platform_.height() / 2, 1));
	image_Repository.insert(std::pair<string, Sprite*>("title_background", lightSpeed_sprite));
}

void SceneApp::LoadMaterials()
{
	Material* space_material = new Material();
	//space_material->set_texture(image_Repository["space_background"]->texture());
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


	//Update input
	Keyboard* kb = input_manager->keyboard();
	input_manager->Update();
	camera_.Update(fps_);
	
	game_states_[index_]->Update(frame_time);

	if (kb->IsKeyPressed(gef::Keyboard::KC_TAB))
		PopState();
	//if escape pressed exit application
	if (kb->IsKeyPressed(gef::Keyboard::KC_ESCAPE))
		return is_Running_;
	else
		return is_Running_;
}

void SceneApp::Render()
{
	camera_.Render(renderer_3d_, platform_);		
	
	game_states_[index_]->Draw();
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

//void SceneApp::BuildLevel()
//{		
//	ground_.set_mesh(primitive_builder_->GetDefaultCubeMesh());	
//	_ground.AddComponent(new MeshRenderer(_ground, &ground_));
//	_ground.AddComponent(new Rigidbody2D(_ground, world_, b2_staticBody, 0.5f, 0.5f));
//}
//
//void SceneApp::BuildPlayer()
//{ 	
//	player_.set_mesh(model_Repository["space_frigate_6"]->mesh());
//	_player.AddComponent(new MeshRenderer(_player, &player_));
//	_player.AddComponent(new Rigidbody2D(_player, world_, b2_dynamicBody, 0.5f, 0.5f));
//	_player.AddComponent(new Player(_player, *input_manager));
//}
