#include "GLVertexBufferObject.h"

GLVertexBufferObject::GLVertexBufferObject(GLvoid* vertices, GLuint size)
{
	createVertexBufferObject(vertices, size);
}

GLVertexBufferObject::GLVertexBufferObject(void)
{
}

GLVertexBufferObject::~GLVertexBufferObject(void)
{
}

void GLVertexBufferObject::createVertexBufferObject(GLvoid* vertices, GLuint size)
{
	if (value != 0) dispose();
	glGenBuffers(1, &value);
	glBindBuffer(GL_ARRAY_BUFFER, value);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GLVertexBufferObject::dispose(void)
{
	glDeleteBuffers(1, &value);
}