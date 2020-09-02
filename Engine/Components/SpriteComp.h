#pragma once
#include "RenderComp.h"


namespace nc
{
	class SpriteComp : public RenderComp
	{
	public:
		virtual bool create(void* data = nullptr) override;
		virtual void destroy() override;

		virtual void update() override;
		virtual void draw() override;

	protected:
		class Texture* texture;
	};
}