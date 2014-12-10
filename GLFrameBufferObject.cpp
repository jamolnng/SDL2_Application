#include "GLFrameBufferObject.h"

GLFrameBufferObject::GLFrameBufferObject(GLuint width, GLuint height, bool hasDepth, bool useEXT)
{
	createFrameBufferObject(width, height, hasDepth, useEXT);
}

GLFrameBufferObject::GLFrameBufferObject(void)
{
}

GLFrameBufferObject::~GLFrameBufferObject(void)
{
}

void GLFrameBufferObject::createFrameBufferObject(GLuint width, GLuint height, bool hasDepth, bool useEXT)
{
	if (value != 0) dispose();
	this->width = width;
	this->height = height;
	this->_hasDepth = hasDepth;

	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	//if (useEXT)
	//{
	//	if (_hasDepth)
	//	{
	//		/* Depth buffer */
	//		glGenRenderbuffersEXT(1, &depthBuffer);
	//		glBindRenderbufferEXT(GL_RENDERBUFFER, depthBuffer);
	//		glRenderbufferStorageEXT(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);
	//		glBindRenderbufferEXT(GL_RENDERBUFFER, 0);
	//	}

	//	/* Framebuffer to link everything together */
	//	glGenFramebuffersEXT(1, &value);
	//	glBindFramebufferEXT(GL_FRAMEBUFFER, value);
	//	glFramebufferTexture2DEXT(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
	//	if (hasDepth)
	//	{
	//		glFramebufferRenderbufferEXT(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
	//	}

	//	glBindFramebufferEXT(GL_FRAMEBUFFER, 0);
	//}
	//else
	{
		if (_hasDepth)
		{
			/* Depth buffer */
			glGenRenderbuffers(1, &depthBuffer);
			glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);
			glBindRenderbuffer(GL_RENDERBUFFER, 0);
		}

		/* Framebuffer to link everything together */
		glGenFramebuffers(1, &value);
		glBindFramebuffer(GL_FRAMEBUFFER, value);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
		if (hasDepth)
		{
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}

void GLFrameBufferObject::resize(GLuint width, GLuint height, bool useEXT)
{
	this->width = width;
	this->height = height;
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (!_hasDepth) return;

	/*if (useEXT)
	{
		glBindRenderbufferEXT(GL_RENDERBUFFER, depthBuffer);
		glRenderbufferStorageEXT(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);
		glBindRenderbufferEXT(GL_RENDERBUFFER, 0);
	}
	else*/
	{
		glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}
}

bool GLFrameBufferObject::hasDepth(void)
{
	return this->_hasDepth;
}

GLuint GLFrameBufferObject::getTexture(void)
{
	return texture;
}

GLuint GLFrameBufferObject::getDepthBuffer(void)
{
	return depthBuffer;
}

GLuint GLFrameBufferObject::getWidth(void)
{
	return width;
}

GLuint GLFrameBufferObject::getHeight(void)
{
	return height;
}

void GLFrameBufferObject::dispose(void)
{
	//glDeleteFramebuffersEXT(1, &value);
	glDeleteFramebuffers(1, &value);
}

GLuint* GLFrameBufferObject::create(GLuint width, GLuint height, bool hasDepth, bool useEXT)
{
	GLuint out[3];
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &out[2]);
	glBindTexture(GL_TEXTURE_2D, out[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glBindTexture(GL_TEXTURE_2D, 0);


	if (hasDepth)
	{
		/* Depth buffer */
		glGenRenderbuffers(1, &out[2]);
		glBindRenderbuffer(GL_RENDERBUFFER, out[2]);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}

	/* Framebuffer to link everything together */
	glGenFramebuffers(1, &out[0]);
	glBindFramebuffer(GL_FRAMEBUFFER, out[0]);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, out[1], 0);
	if (hasDepth)
	{
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, out[2]);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return out;
}