#pragma once
#include "pch.h"
#include "Component.h"
#include "Math/Vector2.h"



namespace nc
{
	class PhysicsComp : public Component
	{
	public:
		virtual bool create(void* data = nullptr) override;
		virtual void destroy() override;
		virtual void update() override;

		void applyForce(nc::Vector2& force);


	protected:
		Vector2 velocity;
		Vector2 force;
		float drag = 1;

	};
}