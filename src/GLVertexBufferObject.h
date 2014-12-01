#pragma once

#include <GL\glew.h>
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

		static GLuint create(GLvoid* vertices, GLuint size);
};

typedef GLVertexBufferObject GLvbo;