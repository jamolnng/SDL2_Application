#include "Box2D_Shape_Rect.h"
#include <GL\glew.h>
#include "World.h"
#include <GL\GL.h>
#include <GL\GLU.h>
#include <cmath>
#include <glm\glm.hpp>

using std::cos;
using std::sin;

Box2D_Shape_Rect::Box2D_Shape_Rect(World* world, float x, float y, float width, float height, float angle, b2BodyType bodyType) : Box2D_Shape(world, x, y, angle, bodyType)
{
	b2PolygonShape* shape = new b2PolygonShape();
	shape->SetAsBox(width / 1.0f, height / 1.0f);
	setShape(shape);
	this->width = width;
	this->height = height;
}

Box2D_Shape_Rect::~Box2D_Shape_Rect(void)
{
}

void Box2D_Shape_Rect::render(void)
{
	//setVertices();
	glEnableClientState(GL_VERTEX_ARRAY);
	glPushMatrix();
	b2Vec2 p = body->GetWorldCenter();
	float a = body->GetAngle();
	glTranslatef(mtp(p.x), mtp(p.y), 0.0f);
	if (a != 0.0f)
	{
		glRotatef(glm::degrees(a), 0.0f, 0.0f, 1.0f);
	}
	glScalef(World::unitRatio * width * 2.0f, World::unitRatio * height * 2.0f, 1.0f);
	glBindBuffer(GL_ARRAY_BUFFER, rectangleBuffer);
	glVertexPointer(2, GL_FLOAT, NULL, NULL);
	glColor4f(0.25f, 0.25f, 0.25f, 1.0f);
	glDrawArrays(GL_POLYGON, 0, 4);
	glColor4f(color.r, color.g, color.b, 0.5f);
	glDrawArrays(GL_POLYGON, 0, 4);
	glColor4f(color.r, color.g, color.b, 1);
	glDrawArrays(GL_LINE_LOOP, 0, 4);
	glBindBuffer(GL_ARRAY_BUFFER, NULL);

	glPopMatrix();
	glDisableClientState(GL_VERTEX_ARRAY);
}

void Box2D_Shape_Rect::setVertices(void)
{
	b2Vec2 c = body->GetWorldCenter();
	float a = body->GetAngle();
	b2PolygonShape *s = (b2PolygonShape*)shape;
	vertices.clear();
	for (int i = 0; i < s->GetVertexCount(); i++)
	{
		vertices.push_back(applyRotation(s->GetVertex(i) + body->GetPosition(), c, a));
	}

	/*b2Vec2 c = body->GetWorldCenter();
	float a = body->GetAngle();
	b2Vec2 v1(c.x - (width), c.y - (height));
	b2Vec2 v2(c.x + (width), c.y - (height));
	b2Vec2 v3(c.x + (width), c.y + (height));
	b2Vec2 v4(c.x - (width), c.y + (height));
	vertices.clear();
	vertices.push_back(applyRotation(v1, c, a));
	vertices.push_back(applyRotation(v2, c, a));
	vertices.push_back(applyRotation(v3, c, a));
	vertices.push_back(applyRotation(v4, c, a));*/
}

float Box2D_Shape_Rect::getWidth(void)
{
	return width;
}

float Box2D_Shape_Rect::getHeight(void)
{
	return height;
}

b2Vec2& Box2D_Shape_Rect::applyRotation(b2Vec2& v, b2Vec2& c, float angle)
{
	float ca = cos(angle);
	float sa = sin(angle);
	float ox = v.x - c.x;
	float oy = v.y - c.y;
	float px = (ox * ca - oy * sa);
	float py = (ox * sa + oy * ca);
	v.x = px + c.x;
	v.y = py + c.y;
	return v;
}