#include "pch.h"
#include "PhysicsComp.h"
#include "Objects/GameObject.h"

bool nc::PhysicsComp::create(void* data)
{
	drag = 0.95f;
	return true;
}

void nc::PhysicsComp::destroy()
{
}

void nc::PhysicsComp::update()
{
	velocity = velocity + force * owner->engine->getTimer().deltaTime();// * timer.deltaTime();
	velocity = velocity * drag;
	owner->transform.position = owner->transform.position + velocity * owner->engine->getTimer().deltaTime();// *timer.deltaTime();
}

void nc::PhysicsComp::applyForce(nc::Vector2& force)
{
	this->force = force;
}
