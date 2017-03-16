#include "ControlManager.h"
#include "input\keyboard.h"
#include "input\sony_controller_input_manager.h"
#include "input\touch_input_manager.h"


ControlManager::ControlManager(gef::Font * font)
{
	_font = font;
}

ControlManager::ControlManager(gef::Font * font, std::vector<Control*> controls)
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
		if(_controls[i]->Enabled())
			_controls[i]->Update(gameTime);

	for (int i = 0; i < _controls.size(); i++)
		if (_controls[i]->Focus())
			_controls[i]->HandleInput(inputManager);

	if (!_acceptInput)
		return;

	gef::Keyboard* kb = inputManager->keyboard();
	
	if (kb->IsKeyPressed(gef::Keyboard::KC_D))
		NextControl();

	if (kb->IsKeyPressed(gef::Keyboard::KC_A))
		PreviousControl();
}

void ControlManager::Draw(gef::SpriteRenderer * spriteRenderer)
{
	for (int i = 0; i < _controls.size(); i++)
		if(_controls[i]->Visible())
			_controls[i]->Draw(spriteRenderer);
}

void ControlManager::NextControl()
{
	if (_controls.size() == 0)
		return;

	int currentControl = _selectedControl;

	_controls[_selectedControl]->SetFocus(false);

	do
	{
		_selectedControl++;

		if (_selectedControl > _controls.size() - 1)
			_selectedControl = 0;

		if (_controls[_selectedControl]->TabStop() && _controls[_selectedControl]->Enabled())
		{
			//if focus changed
			//call focus changed event
			break;
		}

	} while (currentControl != _selectedControl);

	_controls[_selectedControl]->SetFocus(true);
}

void ControlManager::PreviousControl()
{
	if (_controls.size() == 0)
		return;

	int currentControl = _selectedControl;

	_controls[_selectedControl]->SetFocus(false);

	do
	{
		_selectedControl--;
		
		if (_selectedControl < 0)
			_selectedControl = _controls.size() - 1;

		if (_controls[_selectedControl]->TabStop() && _controls[_selectedControl]->Enabled())
		{
			//if focus changed
				//call focus changed event
			break;
		}

	} while (currentControl != _selectedControl);

	_controls[_selectedControl]->SetFocus(true);
}

void ControlManager::AddControl(Control* control)
{
	_controls.push_back(control);
}

void ControlManager::RemoveControl(int index)
{
	_controls.erase(_controls.begin() + index);
}

void ControlManager::SetFont(gef::Font * font)
{
	_font = font;
}
