#include "PhysicsComponent.h"


PhysicsComponent::PhysicsComponent(String name, AGameObject* owner): AComponent(name, AComponent::ComponentType::Physics, owner)
{
    BaseSystem::getInstance()->getPhysicsSystem()->registerComponent(this);
    PhysicsCommon* physicsCommon = BaseSystem::getInstance()->getPhysicsSystem()->getPhysicsCommon();
    PhysicsWorld* physicsWorld = BaseSystem::getInstance()->getPhysicsSystem()->getPhysicsWorld();

    Vector3D scale = this->getOwner()->getLocalScale();
    Transform transform; transform.setFromOpenGL(this->getOwner()->getPhysicsLocalMatrix());
    BoxShape* boxshape = physicsCommon->createBoxShape(Vector3(scale.getX() / 2, scale.getY() / 2, scale.getZ() / 2));
    this->rigidbody = physicsWorld->createRigidBody(transform);
    this->rigidbody->addCollider(boxshape, transform);
    this->rigidbody->updateMassPropertiesFromColliders();
    this->rigidbody->setMass(this->mass);
    this->rigidbody->setType(BodyType::DYNAMIC);

    transform = this->rigidbody->getTransform();
    float matrix[16];
    transform.getOpenGLMatrix(matrix);

    this->getOwner()->setLocalMatrix(matrix);

}

PhysicsComponent::~PhysicsComponent()
{
}

void PhysicsComponent::perform(float deltaTime)
{
    const Transform transform = this->rigidbody->getTransform();
    float matrix[16];
    transform.getOpenGLMatrix(matrix);

    this->getOwner()->setLocalMatrix(matrix);
}

RigidBody* PhysicsComponent::getRigidBody()
{
    return nullptr;
}
