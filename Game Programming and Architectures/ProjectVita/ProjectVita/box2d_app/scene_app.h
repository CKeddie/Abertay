#ifndef _SCENE_APP_H
#define _SCENE_APP_H

#include <system\application.h>

#include <map>
#include <vector>

#include "primitive_builder.h"

#include <graphics\model.h>
#include <graphics\mesh_instance.h>
#include <graphics\sprite_renderer.h>
#include <graphics\sprite.h>
#include <graphics\image_data.h>
#include <graphics\texture.h>

#include "assets\obj_loader.h"
#include "assets\png_loader.h"

#include "input\input_manager.h"
#include "input\keyboard.h"

#include "box2d\Box2D.h"

#include "Camera.h"
#include "GameObject.h"

#include <TitleScreen.h>
#include <MenuScreen.h>
#include <MainGame.h>

// FRAMEWORK FORWARD DECLARATIONS
namespace gef
{
	class Platform;
	class SpriteRenderer;
	class Font;
	class InputManager;
	class Renderer3D;
}

class SceneApp : public gef::Application
{
public:
	SceneApp(gef::Platform& platform);
	void Init();
	void ChangeState();
	void CleanUp();
	bool Update(float frame_time);
	void Render();

	void InitFont();

	void LoadModels();
	void LoadImages();
	void LoadMaterials();

	void PushState();
	void PopState();

	void Quit();
		
	void CleanUpFont();
	void SetupLights();
	void DrawHUD();

	//Game components
	gef::AudioManager* audio_manager_;
	gef::SpriteRenderer* sprite_renderer_;
	gef::Font* font_;
	gef::InputManager* input_manager;
	gef::Renderer3D* renderer_3d_;
	gef::OBJLoader* obj_loader_ = new gef::OBJLoader();
	gef::Keyboard* keyboard_;
	gef::PNGLoader* png_loader_ = new gef::PNGLoader();
	PrimitiveBuilder* primitive_builder_;

	//GameState Management
	std::vector<GameState*> game_states_;
	int index_ = -1;
	bool is_Running_ = true;

	//Model Storage
	std::map <string, Model*> model_Repository;
	std::map <string, Sprite*> image_Repository;
	std::map <string, Texture*> texture_Repository;

	float fps_;
};

#endif // _SCENE_APP_H
