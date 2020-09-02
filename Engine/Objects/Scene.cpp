#include "pch.h"
#include "Scene.h"
#include "GameObject.h"
#include "ObjectFactory.h"


namespace nc
{
	bool Scene::create(void* data)
	{
		engine = static_cast<Engine*>(data);
		return true;
	}

	void Scene::destroy()
	{
		RemoveAllGameObjects();
	}

	void Scene::read(const rapidjson::Value& value)
	{
		const rapidjson::Value& objectsValue = value["GameObjects"];
		if (objectsValue.IsArray())
		{
			readGameObjects(objectsValue);
		}
	}

	void Scene::readGameObjects(const rapidjson::Value& value)
	{
		for (rapidjson::SizeType i = 0; i < value.Size(); i++)
		{
			const rapidjson::Value& objectValue = value[i];
			if (objectValue.IsObject())
			{
				std::string typeName;
				json::Get(objectValue, "type", typeName);
				GameObject* gameObject = nc::ObjectFactory::instance().create<GameObject>(typeName);

				if (gameObject)
				{
					gameObject->create(engine);
					gameObject->read(objectValue);
					AddGameObject(gameObject);
				}
			}
		}
	}

	void Scene::ReadPrototypes(const rapidjson::Value& value)
	{
		for (rapidjson::SizeType i = 0; i < value.Size(); i++)
		{
			const rapidjson::Value& objectValue = value[i];
			if (objectValue.IsObject())
			{
				std::string typeName;
				json::Get(objectValue, "type", typeName);
				GameObject* gameObject = nc::ObjectFactory::instance().create<GameObject>(typeName);

				if (gameObject)
				{
					gameObject->create(engine);
					gameObject->read(objectValue);

					std::cout << gameObject->name << std::endl;

					//ObjectFactory::instance().registerThing(gameObject->name, new Prototype<Object>(gameObject));
				}
			}
		}
	}

	void Scene::update()
	{
		for (auto gameObject : gameObjects) {
			gameObject->update();
		}
	}

	void Scene::draw()
	{
		for (auto gameObject : gameObjects) {
			gameObject->draw();
		}
	}

	std::vector<GameObject*> Scene::FindByTag(const std::string& tag)
	{





		return std::vector<GameObject*>();
	}

	GameObject* Scene::Find(const std::string& name)
	{
		for (auto gameObject : gameObjects)
		{
			if (gameObject->name == name)
			{
				return gameObject;
			}
		}

		return nullptr;
	}

	void Scene::AddGameObject(GameObject* gameObject)
	{
		gameObjects.push_back(gameObject);
	}

	void Scene::RemoveGameObject(GameObject* gameObject)
	{
		auto iter = std::find(gameObjects.begin(), gameObjects.end(), gameObject);
		if (iter != gameObjects.end())
		{
			(*iter)->destroy();
			delete(*iter);
			gameObjects.erase(iter);
		}
	}

	void Scene::RemoveAllGameObjects()
	{
		for (GameObject* gameObject : gameObjects)
		{
			gameObject->destroy();
			delete gameObject;
		}

		gameObjects.clear();
	}

}
