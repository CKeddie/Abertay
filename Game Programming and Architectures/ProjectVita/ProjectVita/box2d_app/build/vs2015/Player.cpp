#include "Player.h"



Player::Player(GameObject& parent, gef::InputManager& inputManager) : Component::Component(parent), _inputManager(inputManager)
{

}

void Player::Update(float deltaTime)
{
}

void Player::Render(gef::Renderer3D * renderer)
{
}


Player::~Player()
{
}
