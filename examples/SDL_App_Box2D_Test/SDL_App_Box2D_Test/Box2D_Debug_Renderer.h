#pragma once

#include <GL\glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL\GL.h>
#include <GL\GLU.h>
#include <Box2D\Box2D.h>

class Box2D_Debug_Renderer : public b2Draw
{
	public:
		Box2D_Debug_Renderer(bool immediateMode = false);
		void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);

		void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);

		void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);

		void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);

		void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);

		void DrawTransform(const b2Transform& xf);

		void setImmediateRendering(bool immediateRendering);
		bool isImmediateRendering(void);

	private:
		bool immediateModeRendering;
};