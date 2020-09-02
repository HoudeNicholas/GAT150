#include "pch.h"
#include "Renderer.h"

bool nc::Renderer::startup()
{


	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	return true;
}

void nc::Renderer::shutdown()
{
	IMG_Quit();
}

void nc::Renderer::update()
{
}

bool nc::Renderer::create(const std::string& name, int w, int h)
{
	m_window = SDL_CreateWindow(name.c_str(), 100, 100, 800, 600, SDL_WINDOW_SHOWN);
	if (m_window == nullptr) {
		std::cout << "Error: " << SDL_GetError() << std::endl;
		return false;
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_renderer == nullptr) {
		std::cout << "Error: " << SDL_GetError() << std::endl;
		return false;
	}


	return true;
}

void nc::Renderer::begin()
{
	SDL_RenderClear(m_renderer);
}

void nc::Renderer::end()
{
	SDL_RenderPresent(m_renderer);
}
