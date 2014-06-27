#pragma once

#include "Box2D_Shape.h"

class Box2D_Shape_Rect : public Box2D_Shape
{
	public:
		Box2D_Shape_Rect(World* world, float x, float y, float width, float height, float angle = 0.0f, b2BodyType bodyType = b2_staticBody);
		~Box2D_Shape_Rect(void);

		void render(void);
		void setVertices(void);

		float getWidth(void);
		float getHeight(void);

		b2Vec2& applyRotation(b2Vec2& v, b2Vec2& c, float angle);

	private:
		float width;
		float height;
};