#include "pch.h"
#include "Components/Component.h"
#include "Components/PhysicsComp.h"
#include "Components/SpriteComp.h"
#include "Component/PlayerComp.h"
#include <SDL_image.h>
#include "pch.h"
#include "Texture.h"
#include "Math/Math.h"
#include "Engine.h"
#include "Objects/GameObject.h"
#include "Core/Json.h"
#include "Objects/Factory.h"


nc::Engine engine;
float angle1;
nc::Factory<nc::Object, std::string> factory;


int main(int, char**)
{
	rapidjson::Document document;

	engine.startup();

	factory.registerThing("GameObject", nc::Object::Instantiate<nc::GameObject>);
	factory.registerThing("PhysicsComp", nc::Object::Instantiate<nc::PhysicsComp>);

	nc::GameObject* player = factory.create<nc::GameObject>("GameObject");

	player->create(&engine);
	nc::json::Load("player.txt", document);
	
	player->read(document);

	//nc::Component* component;
	//component = factory.create<nc::Component>("physicsComponent");

	//player->addComponent(component);
	//component->create();
	


	//component = new nc::SpriteComp;
	//player->addComponent(component);
	//component->create();

	//component = new nc::PlayerComp;
	//player->addComponent(component);
	//component->create();


	nc::Texture* background = engine.getSystem<nc::ResourceManager>()->Get<nc::Texture>("background.png", engine.getSystem<nc::Renderer>());

	SDL_Event event;
	bool quit = false;

	while (!quit) {
		SDL_PollEvent(&event);
		switch (event.type) {
		case SDL_QUIT:
			quit = true;
			break;

		default:
			break;
		}

		engine.update();
		player->update();

		if (engine.getSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_ESCAPE) == nc::InputSystem::eButtonState::PRESSED) {
			quit = true;
		}


		engine.getSystem<nc::Renderer>()->begin();

		background->draw({ 0, 0 }, { 1, 1 }, 0);
		player->draw();


		engine.getSystem<nc::Renderer>()->end();
	}
	engine.shutdown();

	return 0;
}


/*	rapidjson::Document document;
	nc::json::Load("json.txt", document);

	std::string str;
	nc::json::Get(document, "string", str);
	std::cout << str << std::endl;

	bool b;
	nc::json::Get(document, "bool", b);
	std::cout << b << std::endl;

	int i1;
	nc::json::Get(document, "integer1", i1);
	std::cout << i1 << std::endl;

	int i2;
	nc::json::Get(document, "integer2", i2);
	std::cout << i2 << std::endl;

	float f;
	nc::json::Get(document, "float", f);
	std::cout << f << std::endl;

	nc::Vector2 v2;
	nc::json::Get(document, "vector2", v2);
	std::cout << v2 << std::endl;

	nc::Color color;
	nc::json::Get(document, "color", color);
	std::cout << color << std::endl;*/