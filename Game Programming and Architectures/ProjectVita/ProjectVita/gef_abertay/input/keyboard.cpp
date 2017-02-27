#include "keyboard.h"
#include <iostream>

namespace gef
{
	Keyboard::~Keyboard()
	{

	}

	bool Keyboard::IsKeyDown(KeyCode key) const
	{
		return (std::cin.get() & (int)key);
	}

	bool Keyboard::IsKeyPressed(KeyCode key) const
	{		
		return false;
	}

	bool Keyboard::IsKeyReleased(KeyCode key) const
	{
		return false;
	}
}
