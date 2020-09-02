#include "pch.h"
#include "SpriteComp.h"
#include "Texture.h"

bool nc::SpriteComp::create(void* data)
{
	texture = owner->engine->getSystem<nc::ResourceManager>()->Get<nc::Texture>("cars.png", owner->engine->getSystem<nc::Renderer>());
	return true;
}

void nc::SpriteComp::destroy()
{
}

void nc::SpriteComp::update()
{
}

void nc::SpriteComp::draw()
{
	texture->draw({ 0, 16, 64, 144 }, owner->transform.position, { 1, 1 }, owner->transform.angle);
}
