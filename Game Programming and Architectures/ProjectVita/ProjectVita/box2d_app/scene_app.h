#ifndef _SCENE_APP_H
#define _SCENE_APP_H

#include <system/application.h>

#include <maths/vector2.h>

#include "primitive_builder.h"

#include <graphics/mesh_instance.h>
#include "graphics/sprite_renderer.h"

#include "input/input_manager.h"
#include "input/keyboard.h"

#include "Camera.h"
#include "GameObject.h"


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
	
	gef::SpriteRenderer* sprite_renderer_;
	gef::Font* font_;	
	gef::InputManager* input_manager;
	gef::Renderer3D* renderer_3d_;
	
	gef::Keyboard* keyboard_;

	PrimitiveBuilder* primitive_builder_;

	gef::MeshInstance player_;


	float fps_;
};

#endif // _SCENE_APP_H