#include "Box2D_Constraint.h"
#include "World.h"

Box2D_Constraint::Box2D_Constraint(World* world)
{
	this->world = world;
	this->physicsWorld = world->getPhysicsWorld();
}


Box2D_Constraint::~Box2D_Constraint(void)
{
}

bool Box2D_Constraint::update(float timeStep)
{
	return false;
}

void Box2D_Constraint::render(void)
{
}

void Box2D_Constraint::dispose(void)
{
}