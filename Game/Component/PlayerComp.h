#pragma once
#include "Components/Component.h"


namespace nc
{
	class PlayerComp : public Component
	{
	public:
		virtual bool create(void* data = nullptr) override;
		virtual void destroy() override;
		virtual void update() override;

		 

	};
}