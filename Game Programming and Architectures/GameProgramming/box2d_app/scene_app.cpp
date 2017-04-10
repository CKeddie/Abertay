#include "scene_app.h"

#include <graphics\mesh.h>
#include <graphics\sprite.h>
#include <graphics\image_data.h>
#include <graphics\texture.h>

#include <GameScreens.h>

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

	gef::Keyboard* kb = input_manager->keyboard();
	input_manager->Update();

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
	// setup camera

	// projection
	float fov = gef::DegToRad(45.0f);
	float aspect_ratio = (float)platform_.width() / (float)platform_.height();
	gef::Matrix44 projection_matrix;
	projection_matrix = platform_.PerspectiveProjectionFov(fov, aspect_ratio, 0.1f, 100.0f);
	renderer_3d_->set_projection_matrix(projection_matrix);

	// view
	gef::Vector4 camera_eye(0.0f, 0, 10.0f);
	gef::Vector4 camera_lookat(0.0f, 0.0f, 0.0f);
	gef::Vector4 camera_up(0.0f, 1.0f, 0.0f);
	gef::Matrix44 view_matrix;
	view_matrix.LookAt(camera_eye, camera_lookat, camera_up);
	renderer_3d_->set_view_matrix(view_matrix);


	// draw 3d geometry
	renderer_3d_->Begin();
	if(index_ >= 0)
		game_states_[index_]->Draw();
	renderer_3d_->End();

	// start drawing sprites, but don't clear the frame buffer
	sprite_renderer_->Begin(false);
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
		//font_->RenderText(sprite_renderer_, gef::Vector4(850.0f, 510.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_LEFT, "FPS: %.1f", fps_);
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

void SceneApp::LoadImages()
{
	SpriteLoader("textures/glassPanel", "glass_button");
	SpriteLoader("textures/seamless space_0", "space_background");
	SpriteLoader("textures/GalaxyRush", "title");
	SpriteLoader("textures/LightSpeed", "title_background");
	SpriteLoader("textures/bubble-field", "player_lives");
	SpriteLoader("textures/alien-skull", "alien_skull");
}

void SceneApp::LoadModels()
{
	SCNLoader("space_frigate_6", "space_frigate", "space_frigate_color");
	SCNLoader("dark_fighter_6", "dark_fighter", "dark_fighter_color");
	SCNLoader("small_fighter_1", "small_fighter", "small_fighter_color");
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
		gef::Mesh* mesh = model_scene_->CreateMesh(platform_, model_scene_->meshes.front());
		mesh_repository.insert(std::pair<std::string, gef::Mesh*>(repositoryName, mesh));

		if (model_scene_->materials.size() > 0)
			material_repository.insert(std::pair<std::string, gef::Material*>(textureRepoName, model_scene_->materials.front()));
	}
}

void SceneApp::SpriteLoader(std::string path, std::string repositoryName)
{
	gef::ImageData data;
	gef::Sprite* sprite = new gef::Sprite();
	
	std::string asset = path + ".png";
	png_loader_->Load(asset.c_str(), platform_, data);

	sprite->set_texture(gef::Texture::Create(platform_, data));

	sprite->set_height(data.height());
	sprite->set_width(data.width());

	//Store sprite for later use
	image_repository.insert(std::pair<std::string, gef::Sprite*>(repositoryName, sprite));
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