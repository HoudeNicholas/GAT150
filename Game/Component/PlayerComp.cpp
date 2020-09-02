#include "pch.h"
#include "PlayerComp.h"
#include "Components/PhysicsComp.h"

bool nc::PlayerComp::create(void* data)
{
	return true;
}

void nc::PlayerComp::destroy()
{
}

void nc::PlayerComp::update()
{
	if (owner->engine->getSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_A) == nc::InputSystem::eButtonState::HELD)
	{
		owner->transform.angle = owner->transform.angle - 200.0f * owner->engine->getTimer().deltaTime();
	}
	if (owner->engine->getSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_D) == nc::InputSystem::eButtonState::HELD)
	{
		owner->transform.angle = owner->transform.angle + 200.0f * owner->engine->getTimer().deltaTime();
	}

	nc::Vector2 force{ 0, 0 };
	if (owner->engine->getSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_W) == nc::InputSystem::eButtonState::HELD) {
		force = nc::Vector2::forward * 1000.0f;
	}
	force = nc::Vector2::rotate(force, nc::degToRad(owner->transform.angle));

	PhysicsComp* component = owner->getComponent<PhysicsComp>();
	if (component) {
		component->applyForce(force);
	}
}
