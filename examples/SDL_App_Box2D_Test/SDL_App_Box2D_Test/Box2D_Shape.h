#pragma once

#include <GLVertexBufferObject.h>
#include <Box2D\Box2D.h>
#include <vector>

using std::vector;

class World;

class Box2D_Shape
{
	public:
		Box2D_Shape(World* world, float x, float y, float angle = 0.0f, b2BodyType bodyType = b2_staticBody);
		~Box2D_Shape(void);

		void create(b2Shape*, b2FixtureDef fixtureDef);
		void create(b2Shape*, float density = 0.0f);

		void setBodyDef(b2BodyDef bodyDef);
		void setShape(b2Shape* shape);
		void setFixutreDef(b2FixtureDef* fixtureDef);
		void setPosition(float x, float y);
		void setRotation(float angle, bool inDegrees = false);
		void setColor(b2Color color);

		void rotate(float angle, bool inDegrees = false);
		virtual void render(void);

		float unitRatio(void);
		void dispose(void);
		vector<b2Vec2> getVertices(void);

		b2BodyDef* getBodyDef(void);
		b2Body* getBody(void);
		b2Shape* getShape(void);
		b2BodyType getType(void);
		b2FixtureDef* getFixtureDef(void);

		static vector<b2Vec2> rectangleVertices;
		static vector<b2Vec2> circleVertices;
		static GLVertexBufferObject rectangleBuffer;
		static GLVertexBufferObject circleBuffer;
		static void populateBasicShapeVertices(void);

	protected:
		World* world;
		b2World* physicsWorld;
		vector<b2Vec2> vertices;
		float mtp(float meters);
		float ptm(float pixels);

		b2Color color;

		b2BodyDef* bodyDef;
		b2Body* body;
		b2Shape* shape;
		b2BodyType type;
		b2FixtureDef* fixtureDef;
		float x, y, angle;
};