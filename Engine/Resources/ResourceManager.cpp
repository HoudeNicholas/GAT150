#include "pch.h"
#include "ResourceManager.h"

namespace nc
{
	bool nc::ResourceManager::startup()
	{
		return true;
	}

	void nc::ResourceManager::shutdown()
	{
		removeAll();
	}

	void nc::ResourceManager::update()
	{
	}
	void ResourceManager::removeAll()
	{
		for (auto resource : m_resources) {
			resource.second->destroy();
			delete resource.second;
		}
		m_resources.clear();
	}
}

