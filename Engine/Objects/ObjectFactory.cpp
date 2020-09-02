#include "pch.h"
#include "ObjectFactory.h"
#include "Audio/AudioComponent.h"
#include "Components/SpriteComp.h"
#include "Components/PhysicsComp.h"
//#include "Components/RigidBodyComponent.h"
//#include "Components/SpriteAnimationComponent.h"*/

namespace nc {
	void ObjectFactoryImpl::initialize()
	{
		ObjectFactory::instance().registerThing("GameObject", new Creator<GameObject, Object>);
		ObjectFactory::instance().registerThing("PhysicsComponent", new Creator<PhysicsComp, Object>);
		ObjectFactory::instance().registerThing("SpriteComponent", new Creator<SpriteComp, Object>);
		//ObjectFactory::instance().registerThing("SpriteAnimationComponent", new Creator<SpriteAnimationComponent, Object>);
		//ObjectFactory::instance().registerThing("RigidBodyComponent", new Creator<RigidBodyComponent, Object>);
		ObjectFactory::instance().registerThing("AudioComponent", new Creator<AudioComponent, Object>);
	}
}
