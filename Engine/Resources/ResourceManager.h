#pragma once
#include <Core/System.h>
#include <Resources/Resource.h>
#include <map>

namespace nc
{
	class ResourceManager : public System
	{
	public:
		// Inherited via System
		virtual bool startup() override;
		virtual void shutdown() override;
		virtual void update() override;

		template <typename T>
		T* Get(const std::string& name, void* data = nullptr);

		void removeAll();

	protected:
		std::map<std::string, Resource*> m_resources;
	};

	template<typename T>
	inline T* ResourceManager::Get(const std::string& name, void* data)
	{
		T* resource = dynamic_cast<T*>(m_resources[name]);

		if (resource == nullptr) {
			resource = new T;
			resource->create(name, data);

			m_resources[name] = resource;
		}

		return resource;
	}
}