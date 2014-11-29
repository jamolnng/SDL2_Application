#pragma once

#include "Box2D_Shape.h"

class Box2D_Shape_Circle : public Box2D_Shape
{
	public:
		Box2D_Shape_Circle(World* world, float x, float y, float radius, float angle = 0.0f, b2BodyType bodyType = b2_staticBody);
		~Box2D_Shape_Circle(void);

		void render(void);
		void setVertices(void);

	private:
		float radius;
};