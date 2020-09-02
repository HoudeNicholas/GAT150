#include "pch.h"
#include "Engine.h"

namespace nc
{
	bool Engine::startup()
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
			return false;
		}

		systems.push_back(new Renderer);
		systems.push_back(new InputSystem);
		systems.push_back(new ResourceManager);
		systems.push_back(new PhysicsSystem);
		systems.push_back(new AudioSystem);
		for (auto system : systems) {
			system->startup();
		}

		getSystem<Renderer>()->create("GAT150", 800, 600);

		return true;
	}

	void Engine::shutdown()
	{

		for (auto system : systems) {
			system->shutdown();
			delete system;
		}
		systems.clear();

		SDL_Quit();
	}

	void Engine::update()
	{
		timer.tick();
		for (auto system : systems) {
			system->update();
		}
	}
}
