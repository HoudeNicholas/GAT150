#pragma once
#include "Object.h"
#include <list>

namespace nc
{
	class Engine;
	class GameObject;

	class Scene : public Object
	{
	public:
		virtual bool create(void* data = nullptr) override;
		virtual void destroy() override;
		void read(const rapidjson::Value& value) override;
		void readGameObjects(const rapidjson::Value& value);
		void ReadPrototypes(const rapidjson::Value& value);
		void update();
		void draw();
		std::vector<GameObject*> FindByTag(const std::string& tag);
		GameObject* Find(const std::string& name);
		void AddGameObject(GameObject* gameObject);
		void RemoveGameObject(GameObject* gameObject);
		void RemoveAllGameObjects();

	protected:
		Engine* engine{ nullptr };
		std::list<GameObject*> gameObjects;
	};
}
