#ifndef _SCENE_APP_H
#define _SCENE_APP_H

#include <system\application.h>

#include <maths\vector2.h>
#include <map>

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
#include "ControlManager.h"
#include "Button.h"
#include "Player.h"

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
	void CleanUp();
	bool Update(float frame_time);
	void Render();
	
private:
	void InitFont();
	void CleanUpFont();
	void DrawHUD();
	void SetupLights();

	void BroadPhase();

	void BuildLevel();
	void BuildPlayer();
	
	gef::AudioManager* audio_manager_;
	gef::SpriteRenderer* sprite_renderer_;
	gef::Font* font_;	
	gef::InputManager* input_manager;
	gef::Renderer3D* renderer_3d_;
	gef::OBJLoader* obj_loader_ = new gef::OBJLoader();
	gef::Keyboard* keyboard_;
	gef::PNGLoader* png_loader_ = new gef::PNGLoader();
	ControlManager control_manager;
	PrimitiveBuilder* primitive_builder_;

	//gameplay members
	b2World* world_;

	std::map <string, Model*> model_Repository;

	gef::MeshInstance player_;
	gef::MeshInstance ground_;
	Model* model;

	gef::Material* material;

	gef::Sprite sprite_;

	GameObject _player = GameObject("Player", Vector4(0, 10, 0), Vector4(0, 0, 0), Vector4(1.1f, 1.1f, 1.1f));
	GameObject _ground = GameObject("Ground",Vector4(0, -1, 0));

	Button* button_;

	float fps_;
};

#endif // _SCENE_APP_H
