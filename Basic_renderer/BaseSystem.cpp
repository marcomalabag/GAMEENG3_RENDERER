#include "BaseSystem.h"

BaseSystem* BaseSystem::sharedInstance = NULL;

BaseSystem* BaseSystem::getInstance()
{
    return sharedInstance;
}

void BaseSystem::initializs()
{
    sharedInstance = new BaseSystem();
}

void BaseSystem::destroy()
{
    delete sharedInstance;
}

PhysicsSystem* BaseSystem::getPhysicsSystem()
{
    return this->physicsSystem;
}

BaseSystem::BaseSystem()
{
    this->physicsSystem = new PhysicsSystem();
}

BaseSystem::~BaseSystem()
{
}
