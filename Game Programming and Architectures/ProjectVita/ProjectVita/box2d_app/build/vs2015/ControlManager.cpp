#include "ControlManager.h"



ControlManager::ControlManager(gef::Font * font)
{
	_font = font;
}

ControlManager::ControlManager(gef::Font * font, std::vector<UIControl> controls)
{
	_font = font;
	_controls = controls;
}

ControlManager::~ControlManager()
{
}

void ControlManager::Update(float gameTime, gef::InputManager * inputManager)
{
	for (int i = 0; i < _controls.size(); i++)
		_controls[i].Update(gameTime);
}

void ControlManager::Draw(gef::SpriteRenderer * spriteRenderer)
{
	for (int i = 0; i < _controls.size(); i++)
		_controls[i].Draw(spriteRenderer);
}

void ControlManager::NextControl()
{

}

void ControlManager::PreviousControl()
{
}

void ControlManager::AddControl(UIControl control)
{
	_controls.push_back(control);
}

void ControlManager::RemoveControl(int index)
{
	
}

void ControlManager::SetFont(gef::Font * font)
{
}
