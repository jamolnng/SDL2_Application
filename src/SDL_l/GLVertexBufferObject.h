#pragma once

#include "gl3w.h"
#include <GL\GL.h>
#include <GL\GLU.h>
#include "GLObject.h"

class GLVertexBufferObject : public GLObject<GLuint>
{
	public:
		GLVertexBufferObject(GLvoid* vertices, GLuint size);
		GLVertexBufferObject(void);
		~GLVertexBufferObject(void);

		void createVertexBufferObject(GLvoid* vertices, GLuint size);
		void dispose(void);
};

typedef GLVertexBufferObject GLvbo;