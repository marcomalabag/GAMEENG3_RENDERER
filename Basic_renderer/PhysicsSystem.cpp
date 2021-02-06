#include "PhysicsSystem.h"
#include <reactphysics3d/reactphysics3d.h>

PhysicsSystem::PhysicsSystem()
{
	this->physicsCommon = new PhysicsCommon();
	PhysicsWorld::WorldSettings settings;
	settings.defaultVelocitySolverNbIterations = 50;
	settings.gravity = Vector3(0, -1.81, 0);
	this->physicsWorld = this->physicsCommon->createPhysicsWorld(settings);
}

PhysicsSystem::~PhysicsSystem()
{
}

void PhysicsSystem::registerComponent(PhysicsComponent* component)
{
	this->componentTable[component->getName()] = component;
	this->componentList.push_back(component);
}

void PhysicsSystem::unregisterComponent(PhysicsComponent* component)
{
	if (this->componentTable[component->getName()] != NULL) {
		this->componentTable.erase(component->getName());
		for (int i = 0; i < this->componentList.size(); i++) {
			if (this->componentList[i] == component) {
				this->componentList.erase(this->componentList.begin() + i);
				break;
			}
		}

	}
}

void PhysicsSystem::unregisterComponentByName(String name)
{
	if (this->componentTable[name] != NULL) {
		this->unregisterComponent(this->componentTable[name]);
	}
}

PhysicsComponent* PhysicsSystem::findComponentByName(String name)
{
	return this->componentTable[name];
}

PhysicsSystem::ComponentList PhysicsSystem::getAllComponents()
{
	return this->componentList;
}

void PhysicsSystem::updateAllComponents()
{
	if (EngineTime::getDeltaTime() > 1.0) {
		this->physicsWorld->update(EngineTime::getDeltaTime());
		for (int i = 0; i < this->componentList.size(); i++) {
			this->componentList[i]->perform(EngineTime::getDeltaTime());
		}
	}
}

PhysicsWorld* PhysicsSystem::getPhysicsWorld()
{
	return this->physicsWorld;
}

PhysicsCommon* PhysicsSystem::getPhysicsCommon()
{
	return this->physicsCommon;
}
