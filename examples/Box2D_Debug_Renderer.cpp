#include "Box2D_Debug_Renderer.h"
#include <glm\glm.hpp>
#include "World.h"

float mtp(float meters)
{
	return meters * World::unitRatio;
}

Box2D_Debug_Renderer::Box2D_Debug_Renderer(bool immediateMode)
{
	this->immediateModeRendering = immediateMode;
}

void Box2D_Debug_Renderer::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	if (immediateModeRendering)
	{
		glPushMatrix();
		glColor4f(color.r, color.g, color.b, color.a);
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < vertexCount; i++)
		{
			glVertex2f(mtp(vertices[i].x), mtp(vertices[i].y));
		}
		glEnd();
		glPopMatrix();
	}
	else
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glPushMatrix();
		glScalef(World::unitRatio, World::unitRatio, 1.0f);
		glColor4f(color.r, color.g, color.b, 1);
		glVertexPointer(2, GL_FLOAT, 0, vertices);
		glDrawArrays(GL_LINE_LOOP, 0, vertexCount);
		glPopMatrix();
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}

void Box2D_Debug_Renderer::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	glCullFace(GL_BACK);
	if (immediateModeRendering)
	{
		glPushMatrix();
		glColor4f(color.r, color.g, color.b, color.a * 0.1f);
		glBegin(GL_POLYGON);
		for (int i = 0; i < vertexCount; i++)
		{
			glVertex2f(mtp(vertices[i].x), mtp(vertices[i].y));
		}
		glEnd();
		glColor4f(color.r, color.g, color.b, color.a);
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < vertexCount; i++)
		{
			glVertex2f(mtp(vertices[i].x), mtp(vertices[i].y));
		}
		glEnd();
		glPopMatrix();
	}
	else
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glCullFace(GL_BACK);
		glPushMatrix();
		glScalef(World::unitRatio, World::unitRatio, 1.0f);
		glVertexPointer(2, GL_FLOAT, 0, vertices);
		glColor4f(color.r, color.g, color.b, 0.5f);
		glDrawArrays(GL_POLYGON, 0, vertexCount);
		glColor4f(color.r, color.g, color.b, 1);
		glDrawArrays(GL_LINE_LOOP, 0, vertexCount);
		glPopMatrix();
		glDisableClientState(GL_VERTEX_ARRAY);
	}
	glCullFace(GL_FRONT);
}

void Box2D_Debug_Renderer::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
	if (immediateModeRendering)
	{
		glPushMatrix();
		glColor4f(color.r, color.g, color.b, color.a);
		glBegin(GL_LINE_LOOP);

		for (int i = 0; i < 360; i++)
		{
			float degInRad = glm::radians((float)i);
			glVertex2f(cos(degInRad)*mtp(radius) + mtp(center.x), sin(degInRad)*mtp(radius) + mtp(center.y));
		}

		glEnd();
		glPopMatrix();
	}
	else
	{
		const float32 k_segments = 16.0f;
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
		}

		glEnableClientState(GL_VERTEX_ARRAY);
		glPushMatrix();
		glScalef(World::unitRatio, World::unitRatio, 1.0f);
		glColor4f(color.r, color.g, color.b, 1);
		glVertexPointer(2, GL_FLOAT, 0, glVertices);
		glDrawArrays(GL_LINE_LOOP, 0, vertexCount);
		glPopMatrix();
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}

void Box2D_Debug_Renderer::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
	glCullFace(GL_BACK);
	if (immediateModeRendering)
	{
		DrawCircle(center, radius, color);
		glPushMatrix();
		glColor4f(color.r, color.g, color.b, color.a * 0.5f);
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(center.x, center.y);
		for (int i = 0; i < 360; i++)
		{
			float degInRad = glm::radians((float)i);
			glVertex2f(cos(degInRad)*mtp(radius) + mtp(center.x), sin(degInRad)*mtp(radius) + mtp(center.y));
		}
		glEnd();
		glColor4f(color.r, color.g, color.b, color.a);
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < 360; i++)
		{
			float degInRad = glm::radians((float)i);
			glVertex2f(cos(degInRad)*mtp(radius) + mtp(center.x), sin(degInRad)*mtp(radius) + mtp(center.y));
		}
		glEnd();
		glPopMatrix();
	}
	else
	{
		const float32 k_segments = 16.0f;
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
		}
		glEnableClientState(GL_VERTEX_ARRAY);
		glPushMatrix();
		glScalef(World::unitRatio, World::unitRatio, 1.0f);
		glColor4f(color.r, color.g, color.b, 0.5f);
		glVertexPointer(2, GL_FLOAT, 0, glVertices);
		glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);
		glColor4f(color.r, color.g, color.b, 1.0f);
		glDrawArrays(GL_LINE_LOOP, 0, vertexCount);
		glPopMatrix();
		glDisableClientState(GL_VERTEX_ARRAY);
		// Draw the axis line
		DrawSegment(center, center + radius*axis, color);
	}
	glCullFace(GL_FRONT);
}

void Box2D_Debug_Renderer::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
	if (immediateModeRendering)
	{
		glPushMatrix();
		glColor4f(color.r, color.g, color.b, color.a);
		glBegin(GL_LINES);
		glVertex2f(mtp(p1.x), mtp(p1.y));
		glVertex2f(mtp(p2.x), mtp(p2.y));
		glEnd();
		glPopMatrix();
	}
	else
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glPushMatrix();
		glScalef(World::unitRatio, World::unitRatio, 1.0f);
		glColor4f(color.r, color.g, color.b, 1.0f);
		GLfloat glVertices[] = { p1.x, p1.y, p2.x, p2.y };
		glVertexPointer(2, GL_FLOAT, 0, glVertices);
		glDrawArrays(GL_LINES, 0, 2);
		glPopMatrix();
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}

void Box2D_Debug_Renderer::DrawTransform(const b2Transform& xf)
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glPushMatrix();
	glScalef(World::unitRatio, World::unitRatio, 1.0f);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glPointSize(3.0f);
	GLfloat glVertices[] = { xf.p.x, xf.p.y };
	glTranslatef(glVertices[0], glVertices[1], 0.0f);
	glRotatef(xf.q.GetAngle(), 0.0f, 0.0f, 1.0f);
	glTranslatef(-glVertices[0], -glVertices[1], 0.0f);
	glVertexPointer(2, GL_FLOAT, 0, glVertices);
	glDrawArrays(GL_POINTS, 0, 1);
	glPointSize(1.0f);
	glPopMatrix();
	glDisableClientState(GL_VERTEX_ARRAY);
}

void Box2D_Debug_Renderer::setImmediateRendering(bool immediateMode)
{
	this->immediateModeRendering = immediateMode;
}

bool Box2D_Debug_Renderer::isImmediateRendering(void)
{
	return this->immediateModeRendering;
}