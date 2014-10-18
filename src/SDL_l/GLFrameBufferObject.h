#pragma once

#include <GL\glew.h>
#include <GL\GL.h>
#include <GL\GLU.h>
#include "GLObject.h"

class GLFrameBufferObject : public GLObject<GLuint>
{
	public:
		GLFrameBufferObject(GLuint width, GLuint height, bool hasDepth = false, bool useEXT = false);
		GLFrameBufferObject(void);
		~GLFrameBufferObject(void);

		void createFrameBufferObject(GLuint width, GLuint height, bool hasDepth = false, bool useEXT = false);
		void resize(GLuint width, GLuint height, bool useEXT = false);

		bool hasDepth(void);

		GLuint getTexture(void);
		GLuint getDepthBuffer(void);
		GLuint getWidth(void);
		GLuint getHeight(void);
		
		void dispose(void);

	private:
		GLuint texture, depthBuffer, width, height;
		bool _hasDepth;
};

typedef GLFrameBufferObject GLfbo;