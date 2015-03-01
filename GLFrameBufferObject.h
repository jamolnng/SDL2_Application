#pragma once

#include <GL\glew.h>
#include <GL\GL.h>
#include <GL\GLU.h>
#include "GLObject.h"
#include <vector>

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

		std::vector<GLfloat> getVertexArray(void);
		
		void dispose(void);

		/*
		 * Returns a 1 dimensional array with 3 objects in it. The first object is the frame buffer, the second one is the texture
		 * The last object is the depth buffer which will be 0 unless hasDepth is true
		 */
		static GLuint* create(GLuint width, GLuint height, bool hasDepth = false, bool useEXT = false);

	private:
		GLuint texture, depthBuffer, width, height;
		bool _hasDepth;
		std::vector<GLfloat> vertexArray;
};

typedef GLFrameBufferObject GLfbo;