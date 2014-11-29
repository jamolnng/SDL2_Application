#include "Box2D_Shape.h"
#include "World.h"

std::vector<b2Vec2> Box2D_Shape::rectangleVertices = std::vector<b2Vec2>();
std::vector<b2Vec2> Box2D_Shape::circleVertices = std::vector<b2Vec2>();
GLVertexBufferObject Box2D_Shape::rectangleBuffer = GLVertexBufferObject();
GLVertexBufferObject Box2D_Shape::circleBuffer = GLVertexBufferObject();

Box2D_Shape::Box2D_Shape(World* world, float x, float y, float angle, b2BodyType bodyType)
{
	this->world = world;
	this->physicsWorld = world->getPhysicsWorld();
	type = bodyType;
	this->x = x;
	this->y = y;
	this->angle = angle;
}

Box2D_Shape::~Box2D_Shape(void)
{
}

void Box2D_Shape::create(b2Shape* shape, b2FixtureDef fixtureDef)
{
	if (shape == NULL) return;
	this->shape = shape;
	if (bodyDef == NULL)
	{
		bodyDef = new b2BodyDef();
		bodyDef->type = type;
		bodyDef->angle = angle;
		bodyDef->position.Set(x, y);
	}

	body = physicsWorld->CreateBody(bodyDef);

	this->fixtureDef = &fixtureDef;
	this->fixtureDef->shape = shape;
	body->CreateFixture(this->fixtureDef);
}

void Box2D_Shape::create(b2Shape* shape, float density)
{
	if (shape == NULL) return;
	this->shape = shape;
	if (bodyDef == NULL)
	{
		bodyDef = new b2BodyDef();
		bodyDef->type = type;
		bodyDef->angle = angle;
		bodyDef->position.Set(x, y);
	}

	body = physicsWorld->CreateBody(bodyDef);
	body->CreateFixture(shape, density);
}

void Box2D_Shape::setBodyDef(b2BodyDef bodyDef)
{
	this->bodyDef = &bodyDef;
}

void Box2D_Shape::setShape(b2Shape* shape)
{
	this->shape = shape;
}

void Box2D_Shape::setFixutreDef(b2FixtureDef* fixtureDef)
{
	this->fixtureDef = fixtureDef;
}

void Box2D_Shape::setPosition(float x, float y)
{
	if (bodyDef != NULL)
	{
		bodyDef->position.Set(x, y);
	}
}

void Box2D_Shape::setRotation(float angle, bool inDegrees)
{
	if (body != NULL)
	{
		if (inDegrees) angle = glm::radians(angle);
		body->SetTransform(body->GetPosition(), angle);
	}
}

void Box2D_Shape::setColor(b2Color color)
{
	this->color = color;
}

void Box2D_Shape::rotate(float angle, bool inDegrees)
{
	if (body != NULL)
	{
		if (inDegrees) angle = glm::radians(angle);
		body->SetTransform(body->GetPosition(), body->GetAngle() + angle);
	}
}

void Box2D_Shape::render(void)
{
}

float Box2D_Shape::unitRatio(void)
{
	return world->unitRatio;
}

void Box2D_Shape::dispose(void)
{
	world = 0;
	physicsWorld = 0;
	delete fixtureDef;
	delete bodyDef;
	delete this->shape;
}

vector<b2Vec2> Box2D_Shape::getVertices(void)
{
	return vertices;
}

b2BodyDef* Box2D_Shape::getBodyDef(void)
{
	return bodyDef;
}

b2Body* Box2D_Shape::getBody(void)
{
	return body;
}

b2Shape* Box2D_Shape::getShape(void)
{
	return shape;
}

b2BodyType Box2D_Shape::getType(void)
{
	return type;
}

b2FixtureDef* Box2D_Shape::getFixtureDef(void)
{
	return fixtureDef;
}

float Box2D_Shape::mtp(float meters)
{
	return world->mtp(meters);
}

float Box2D_Shape::ptm(float pixels)
{
	return world->ptm(pixels);
}

void Box2D_Shape::populateBasicShapeVertices(void)
{
	rectangleVertices.push_back(b2Vec2(0.5f, 0.5f));
	rectangleVertices.push_back(b2Vec2(-0.5f, 0.5f));
	rectangleVertices.push_back(b2Vec2(-0.5f, -0.5f));
	rectangleVertices.push_back(b2Vec2(0.5f, -0.5f));

	const float32 k_segments = 16.0f;
	const int vertexCount = 16;
	const float32 k_increment = 2.0f * b2_pi / k_segments;
	float32 theta = 0.0f;

	for (int i = 0; i < k_segments; ++i)
	{
		circleVertices.push_back(b2Vec2(cosf(theta), sinf(theta)));
		theta += k_increment;
	};
	circleVertices.push_back(b2Vec2(0, 0));
	circleVertices.push_back(b2Vec2(1, 0));

	Box2D_Shape::rectangleBuffer = GLVertexBufferObject(&rectangleVertices.front(), rectangleVertices.size() * sizeof(float) * 2);
	Box2D_Shape::circleBuffer = GLVertexBufferObject(&circleVertices.front(), circleVertices.size() * sizeof(float) * 2);
}