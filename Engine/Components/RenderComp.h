#pragma once
#include "pch.h"
#include "Component.h"

namespace nc
{
	class RenderComp : public Component
	{
	public:
		virtual void draw() = 0;

	};
}