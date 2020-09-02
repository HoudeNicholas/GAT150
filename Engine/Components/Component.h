#pragma once
#include "Objects/GameObject.h"

namespace nc
{
	class GameObject;

	class Component : public Object
	{
	public:
		virtual void update() = 0;

		friend class GameObject;

	public:
		GameObject* owner{ nullptr };
	};
}