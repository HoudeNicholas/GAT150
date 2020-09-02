#include "pch.h"
#include "GameObject.h"
#include "Components/Component.h"
#include "Components/RenderComp.h"
#include "Objects/ObjectFactory.h"


namespace nc
{
	GameObject::GameObject(const GameObject& other)
	{
		name = other.name;
		tag = other.tag;
		lifetime = other.lifetime;

		flags = other.flags;

		transform = other.transform;
		engine = other.engine;

		for (Component* component : other.components)
		{
			Component* clone = dynamic_cast<Component*>(component->Clone());
			clone->owner = this;
			addComponent(clone);
		}
	}
	void GameObject::read(const rapidjson::Value& value)
	{
		nc::json::Get(value, "position", transform.position);
		nc::json::Get(value, "scale", transform.scale);
		nc::json::Get(value, "angle", transform.angle);

		bool transient = false;
		json::Get(value, "transient", transient);

		flags[eFlag::TRANSIENT] = transient;

		nc::json::Get(value, "position", transform.position);
		nc::json::Get(value, "scale", transform.scale);
		nc::json::Get(value, "angle", transform.angle);

		if (value.HasMember("Components"))
		{
			const rapidjson::Value& componentsValue = value["Components"];
			if (componentsValue.IsArray())
			{
				readComponents(componentsValue);
			}
		}
	}


	bool GameObject::create(void* data)
	{
		engine = static_cast<Engine*>(data);

		return true;
	}

	void GameObject::destroy()
	{
		removeAll();
	}
	void GameObject::update()
	{
		for (auto component : components) {
			component->update();
		}

		if (flags[eFlag::TRANSIENT])
		{
			lifetime -= engine->getTimer().deltaTime();
			if (lifetime <= 0)
			{
				flags[eFlag::DESTROY] = true;
			}
		}

	}
	void GameObject::draw()
	{
		RenderComp* rendComp = getComponent<RenderComp>();
		if (rendComp) {
			rendComp->draw();
		}
	}
	void GameObject::addComponent(Component* comp)
	{
		if (comp) {
			comp->owner = this;
			components.push_back(comp);
		}

	}
	void GameObject::removeComponent(Component* comp)
	{
		auto iter = std::find(components.begin(), components.end(), comp);
		if (!(iter == components.end())) {
			(*iter)->destroy();
			delete (*iter);
		}
	}
	void GameObject::removeAll()
	{
		for (auto component : components) {
			component->destroy();
			delete component;
		}
		components.clear();
	}

	void GameObject::readComponents(const rapidjson::Value& value)
	{
		for (rapidjson::SizeType i = 0; i < value.Size(); i++)
		{
			const rapidjson::Value& componentValue = value[i];
			if (componentValue.IsObject())
			{
				std::string typeName;
				json::Get(componentValue, "type", typeName);

				Component* component = nc::ObjectFactory::instance().create<Component>(typeName);
				if (component)
				{
					component->create(this);
					component->read(componentValue);
					nc::GameObject::addComponent(component);
				}
			}
		}
	}

	std::vector<GameObject*> GameObject::getContactsWithTag(const std::string& tag)
	{
		std::vector<GameObject*> matchingContacts;

		for (auto contact : contacts)
		{
			if (contact->tag == tag)
			{
				matchingContacts.push_back(contact);
			}
		}
		return matchingContacts;
	}

	void GameObject::beginContact(GameObject* other)
	{
		contacts.push_back(other);
	}

	void GameObject::endContact(GameObject* other)
	{
		contacts.remove(other);
	}
}
