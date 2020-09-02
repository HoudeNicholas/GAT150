#pragma once
#include "pch.h"
#include <Graphics/Renderer.h>
#include "Resources/ResourceManager.h"
#include "Input/InputSystem.h"
#include "Physics/PhysicsSystem.h"
#include "Core/Timer.h"
#include "Audio/AudioSystem.h"
#include "Core/System.h"


namespace nc 
{
	class System;
	class Engine
	{
	public:

		bool startup();
		void shutdown();

		void update();

		template<typename T>
		T* getSystem();

		FrameTimer& getTimer() { return timer; }

	protected:
		std::vector<System*> systems;

		FrameTimer timer;
		 
	};

	template<typename T>
	inline T* Engine::getSystem() {
		T* result = nullptr;
		for (auto system : systems) {
			result = dynamic_cast<T*>(system);
			if (result) break;
		}
		return result;
	}
}