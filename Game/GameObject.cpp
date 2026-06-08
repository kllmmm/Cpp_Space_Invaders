#include "gameobject.h"
#include "gamestate.h"

GameObject::GameObject(const std::string& name)
	: name(name), state(GameState::getInstance()), id(next_id++)
{
}

int GameObject::next_id = 1;
