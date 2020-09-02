#pragma once
#include <Core/System.h>


namespace nc
{
	class Renderer : public System
	{
	public:
		virtual bool startup() override;

		virtual void shutdown() override;

		virtual void update() override;

		bool create(const std::string& name, int w = 800, int h = 600);

		void begin();
		void end();

		friend class Texture;

	protected:
		SDL_Window* m_window{ nullptr }; 
		SDL_Renderer* m_renderer{ nullptr };

	};
}