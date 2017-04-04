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

#include <sstream>

Camera camera_(gef::Vector4(0,0,10), Vector4(0,0,0), Vector4(1,1,1));

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
	
	////initialize physics simulation
	//b2Vec2 gravity = b2Vec2(0, 0);
	//world_ = new b2World(gravity);
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
	{
		game_states_[index_]->CleanUp();
		game_states_.pop_back();
		index_--;
	}
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
	image_repository.insert(std::pair<string, Sprite*>("glass_button", sprite));

	//Load Space Texture PNG
	gef::ImageData space_data;
	gef::Sprite* space_sprite = new Sprite();

	png_loader_->Load("textures/seamless space_0.png", platform_, space_data);
	space_sprite->set_texture(gef::Texture::Create(platform_, space_data));
	space_sprite->set_width(space_data.width() - 64);
	space_sprite->set_height(space_data.height());
	space_sprite->set_position(Vector4(platform_.width() / 2, platform_.height() / 2, 1));
	image_repository.insert(std::pair<string, Sprite*>("space_background", space_sprite));

	gef::ImageData galaxy_rush_data;
	gef::Sprite* galaxy_sprite = new Sprite();

	png_loader_->Load("textures/GalaxyRush.png", platform_, galaxy_rush_data);
	galaxy_sprite->set_texture(gef::Texture::Create(platform_, galaxy_rush_data));
	galaxy_sprite->set_width(galaxy_rush_data.width());
	galaxy_sprite->set_height(galaxy_rush_data.height());
	galaxy_sprite->set_position(Vector4(platform_.width() / 2, platform_.height() / 2, 1));
	image_repository.insert(std::pair<string, Sprite*>("title", galaxy_sprite));

	gef::ImageData lightSpeed_data;
	gef::Sprite* lightSpeed_sprite = new Sprite();

	png_loader_->Load("textures/LightSpeed.png", platform_, lightSpeed_data);
	lightSpeed_sprite->set_texture(gef::Texture::Create(platform_, lightSpeed_data));
	lightSpeed_sprite->set_width(lightSpeed_data.width());
	lightSpeed_sprite->set_height(lightSpeed_data.height());
	lightSpeed_sprite->set_position(Vector4(platform_.width() / 2, platform_.height() / 2, 1));
	image_repository.insert(std::pair<string, Sprite*>("title_background", lightSpeed_sprite));


	gef::ImageData stars_data;
	gef::Sprite* stars_sprite = new Sprite();

	png_loader_->Load("textures/seamless_stars.png", platform_, stars_data);
	stars_sprite->set_texture(gef::Texture::Create(platform_, stars_data));
	stars_sprite->set_width(stars_data.width());
	stars_sprite->set_height(stars_data.height());
	stars_sprite->set_position(Vector4(platform_.width() / 2, platform_.height() / 2, 1));
	image_repository.insert(std::pair<string, Sprite*>("seamless_stars", stars_sprite));
}

void SceneApp::LoadModels()
{
	SCNLoader("space_frigate_6"   , "space_frigate", "space_frigate_color");
	SCNLoader("dark_fighter_6"	  , "dark_fighter" , "dark_fighter_color" );
	SCNLoader("small_fighter_1"   , "small_fighter", "small_fighter_color");
	SCNLoader("asteroid_crystal_6", "asteroid", "asteroid_crystal");
	SCNLoader("Bomb", "torpedo", "torpedo_txr");
}

void SceneApp::SCNLoader(std::string filename, std::string repositoryName, std::string textureRepoName)
{
	gef::Scene* model_scene_ = new gef::Scene();
	std::string extension = filename + ".scn";
	model_scene_->ReadSceneFromFile(platform_, extension.c_str());
	model_scene_->CreateMaterials(platform_);

	if (model_scene_->meshes.size() > 0)
	{
		Mesh* mesh = model_scene_->CreateMesh(platform_, model_scene_->meshes.front());
		mesh_repository.insert(std::pair<string, Mesh*>(repositoryName, mesh));
		if (model_scene_->materials.size() > 0)
			material_repository.insert(std::pair<string, Material*>(textureRepoName, model_scene_->materials.front()));
	}
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

	//Update input
	Keyboard* kb = input_manager->keyboard();
	input_manager->Update();
	camera_.Update(fps_);

	if (index_ >= 0)
		game_states_[index_]->Update(frame_time);

	if (kb->IsKeyPressed(gef::Keyboard::KC_TAB))
		PopState();
	//if escape pressed exit application
	if (kb->IsKeyPressed(gef::Keyboard::KC_ESCAPE))
		is_Running_ = false;
	
	return is_Running_;
}

void SceneApp::Render()
{
	camera_.Render(renderer_3d_, platform_);		
	int i = sizeof(Vector4);
	if(index_ >=0)
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