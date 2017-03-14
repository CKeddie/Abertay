#pragma once

#include <box2d\Box2D.h>
#include <Player.h>

class GamePhysicsEvents : public b2ContactListener
{
public:
	GamePhysicsEvents();
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	~GamePhysicsEvents();
};

