#include "Box2D_Shape_Circle.h"
#include <GL\glew.h>
#include "World.h"
#include <GL\GL.h>
#include <GL\GLU.h>
#include <cmath>
#include <glm\glm.hpp>
#include <stdio.h>

Box2D_Shape_Circle::Box2D_Shape_Circle(World* world, float x, float y, float radius, float angle, b2BodyType bodyType) : Box2D_Shape(world, x, y, angle, bodyType)
{
	b2CircleShape *shape = new b2CircleShape();
	shape->m_radius = radius;
	this->radius = radius;
	setShape(shape);
}

Box2D_Shape_Circle::~Box2D_Shape_Circle(void)
{
}

void Box2D_Shape_Circle::render(void)
{
	b2Vec2 center = body->GetWorldCenter();
	/*const float32 k_segments = 16.0f;
	const int vertexCount = 16;
	const float32 k_increment = 2.0f * b2_pi / k_segments;
	float32 theta = 0.0f;

	GLfloat glVertices[vertexCount * 2];
	for (int32 i = 0; i < k_segments; ++i)
	{
		b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
		glVertices[i * 2] = v.x;
		glVertices[i * 2 + 1] = v.y;
		theta += k_increment;
	}*/
	glEnableClientState(GL_VERTEX_ARRAY);
	glPushMatrix();
	float a = body->GetAngle();
	glTranslatef(mtp(center.x), mtp(center.y), 0.0f);
	if (a != 0.0f)
	{
		glRotatef(glm::degrees(a), 0.0f, 0.0f, 1.0f);
	}
	glScalef(World::unitRatio * this->radius, World::unitRatio * this->radius, 1.0f);
	glBindBuffer(GL_ARRAY_BUFFER, circleBuffer);
	glVertexPointer(2, GL_FLOAT, NULL, NULL);
	glColor4f(0.25f, 0.25f, 0.25f, 1.0f);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 16);
	glColor4f(color.r, color.g, color.b, 0.5f);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 16);
	glColor4f(color.r, color.g, color.b, 1);
	glDrawArrays(GL_LINE_LOOP, 0, 16);
	glDrawArrays(GL_LINES, 16, 2);
	glBindBuffer(GL_ARRAY_BUFFER, NULL);

	glPopMatrix();
	glDisableClientState(GL_VERTEX_ARRAY);
	// Draw the axis line

	/*b2Vec2 p2 = center + radius*b2Mul(body->GetTransform().q, b2Vec2(1.0f, 0.0f));

	glPushMatrix();
	glColor4f(color.r, color.g, color.b, color.a);
	glBegin(GL_LINES);
	glVertex2f(mtp(center.x), mtp(center.y));
	glVertex2f(mtp(p2.x), mtp(p2.y));
	glEnd();
	glPopMatrix();*/
}

void Box2D_Shape_Circle::setVertices(void)
{
}