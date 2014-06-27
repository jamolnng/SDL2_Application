#pragma once

#include <Box2D\Box2D.h>

class World;

class Box2D_Constraint
{
	public:
		Box2D_Constraint(World* world);
		~Box2D_Constraint(void);

		virtual bool update(float timeStep);
		virtual void render(void);
		virtual void dispose(void);

	protected:
		World* world;
		b2World* physicsWorld;
};