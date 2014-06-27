#pragma once

#include "Box2D_Shape.h"
#include "Box2D_Constraint.h"
#include <Box2D\Box2D.h>

class World;

class Box2D_Constraint_Joint : public Box2D_Constraint
{
	public:
		Box2D_Constraint_Joint(World* world, b2Body* bodyA, b2Body* bodyB);
		Box2D_Constraint_Joint(World* world, Box2D_Shape* bodyA, Box2D_Shape* bodyB);
		~Box2D_Constraint_Joint(void);

		void create(b2JointType type = b2JointType::e_distanceJoint, b2Vec2& posA = b2Vec2(), b2Vec2& posB = b2Vec2(), float distance = 0.0f, bool collideAnchor = true, bool useAngleLimits = false, b2Vec2& angleLimits = b2Vec2(-45, 45), bool breakable = false, float breakForce = 0.0f, float motorTorque = 0.0f, float motorSpeed = 0.0f);

		bool update(float timeStep);
		void render(void);
		void dispose(void);

		b2JointType getType(void);

	protected:
		b2JointDef* jointDef;
		b2Joint* joint;
		b2JointType type;
		b2Body* bodyA, *bodyB;
		float breakForce;
		bool breakable;
};