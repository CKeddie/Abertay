#ifndef _SCENE_APP_H
#define _SCENE_APP_H


#include <system/application.h>
#include <system/platform.h>
#include <system/debug_log.h>

#include <graphics/mesh_instance.h>
#include <graphics/sprite_renderer.h>
#include <graphics/renderer_3d.h>
#include <graphics/font.h>
#include <graphics/scene.h>
#include <graphics\mesh.h>

#include <maths/vector2.h>
#include <maths/math_utils.h>

#include "assets\obj_loader.h"
#include "assets\png_loader.h"

#include "input\input_manager.h"
#include "input\keyboard.h"

#include "box2d\Box2D.h"
#include <vector>

#include "primitive_builder.h"

#include "GameScreens.h"

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

	void PushState();
	void PopState();
	void Quit();

	gef::Mesh* GetMesh(std::string id) { return mesh_repository[id]; }
	gef::Sprite* GetImage(std::string id) { return image_repository[id]; }
	gef::Material* GetMaterial(std::string id) { return material_repository[id]; }
	
	gef::AudioManager* GetAudioManager() { return audio_manager_; }
	gef::SpriteRenderer* GetSpriteRenderer() { return sprite_renderer_; }
	gef::Font* GetFont() { return font_; }
	gef::InputManager* GetInputManager() { return input_manager; }
	gef::Renderer3D* GetRenderer() { return renderer_3d_; }

private:
	void InitFont();
	void CleanUpFont();
	void DrawHUD();
	void SetupLights();

	void LoadImages();

	void LoadModels();

	void SCNLoader(std::string filename, std::string repositoryName, std::string textureRepoName);

	void SpriteLoader(std::string path, std::string repositoryName);


	gef::AudioManager* audio_manager_;
	gef::SpriteRenderer* sprite_renderer_;
	gef::Font* font_;
	gef::InputManager* input_manager;
	gef::Renderer3D* renderer_3d_;
	gef::OBJLoader* obj_loader_ = new gef::OBJLoader();
	gef::Keyboard* keyboard_;
	gef::PNGLoader* png_loader_ = new gef::PNGLoader();
	PrimitiveBuilder* primitive_builder_;

	float fps_;

	//GameState Management
	std::vector<GameState*> game_states_;

	int index_ = -1;
	bool is_Running_ = true;

	std::map <std::string, gef::Mesh*> mesh_repository;
	std::map <std::string, gef::Sprite*> image_repository;
	std::map <std::string, gef::Material*> material_repository;
};

#endif // _SCENE_APP_H
