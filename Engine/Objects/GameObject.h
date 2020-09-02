#pragma once
#include "Object.h"
#include "Math/Transform.h"
#include "Engine.h"
#include "GameObject.h"
#include <vector>
#include <bitset>

namespace nc 
{
	class Component;

	class GameObject : public Object
	{
	public:
		enum eFlag
		{
			ACTIVE,
			VISIBLE,
			DESTROY,
			TRANSIENT
		};
	public:
		GameObject() = default;
		GameObject(const GameObject & other);

	public:

		void read(const rapidjson::Value& value) override;

		friend class Component;
		friend class PhysicsComp;
		// Inherited via Object
		virtual bool create(void* data = nullptr) override;
		virtual void destroy() override;

		void update();
		void draw();

		template<typename T>
		T* getComponent();

		void addComponent(Component* comp);
		void removeComponent(Component* comp);
		void removeAll();

		void beginContact(GameObject* other);
		void endContact(GameObject* other);

		transform transform; 
		Engine* engine;

		void readComponents(const rapidjson::Value& value);

		std::string name;
		std::string tag;
		float lifetime{ 0 };

		std::vector<GameObject*> getContactsWithTag(const std::string& tag);

		std::bitset<32> flags;

	protected:
		std::vector<Component*> components;
		std::list<GameObject*> contacts;
	};

	template<typename T>
	T* GameObject::getComponent() {
		T* result = nullptr;
		for (auto component : components) {
			result = dynamic_cast<T*>(component);
			if (result) break;
		}
		return result;
	}
}