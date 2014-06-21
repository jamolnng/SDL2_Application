#pragma once

#include <GL\glew.h>
#include <GL\GL.h>
#include <GL\GLU.h>
#include "SDL_Utils.h"

struct GLShadera
{
public:
	GLShadera(const char* vertex, const char* fragment, bool v = true, bool f = true)
	{
		vertexProgram = makeVertexProgram(vertex);
		fragmentProgram = makeFragmentProgram(fragment);
		shaderProgram = makeShaderProgram(vertexProgram, fragmentProgram, v, f);
	}

	GLuint makeVertexProgram(const char* file)
	{
		const char* shader = SDL_Utils::readFile(file);
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, (const GLchar**)&shader, NULL);
		glCompileShader(vertexShader);
		return vertexShader;
	}

	GLuint makeFragmentProgram(const char* file)
	{
		const char* shader = SDL_Utils::readFile(file);
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, (const GLchar**)&shader, NULL);
		glCompileShader(fragmentShader);
		return fragmentShader;
	}

	GLuint makeShaderProgram(GLuint vertexShader, GLuint fragmentShader, bool vertex = true, bool fragment = true)
	{
		GLuint shaderID = glCreateProgram();
		if(vertex) glAttachShader(shaderID, vertexShader);
		if(fragment) glAttachShader(shaderID, fragmentShader);
		glLinkProgram(shaderID);
		return shaderID;
	}

	GLuint vertexProgram, fragmentProgram, shaderProgram;

	void dispose(void)
	{
		glDeleteShader(shaderProgram);
	}
};

struct GLVertexBufferObject
{
public:
	GLVertexBufferObject(GLvoid* vertices, int size)
	{
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	GLVertexBufferObject(GLvoid* vertices)
	{
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(float) * sizeof(vertices), vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	GLVertexBufferObject(void)
	{
	}

	void dispose(void)
	{
		glDeleteBuffers(1, &vbo);
	}

	GLuint vbo;
};

struct GLFrameBufferObject
{
public:
	GLFrameBufferObject(unsigned int screen_width, unsigned int screen_height)
	{
		glActiveTexture(GL_TEXTURE0);
		glGenTextures(1, &fbo_texture);
		glBindTexture(GL_TEXTURE_2D, fbo_texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, screen_width, screen_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glBindTexture(GL_TEXTURE_2D, 0);

		/* Depth buffer */
		glGenRenderbuffersEXT(1, &rbo_depth);
		glBindRenderbufferEXT(GL_RENDERBUFFER, rbo_depth);
		glRenderbufferStorageEXT(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, screen_width, screen_height);
		glBindRenderbufferEXT(GL_RENDERBUFFER, 0);

		/* Framebuffer to link everything together */
		glGenFramebuffersEXT(1, &fbo);
		glBindFramebufferEXT(GL_FRAMEBUFFER, fbo);
		glFramebufferTexture2DEXT(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbo_texture, 0);
		glFramebufferRenderbufferEXT(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo_depth);
		GLenum status;
		if ((status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER)) != GL_FRAMEBUFFER_COMPLETE) {
			fprintf(stderr, "glCheckFramebufferStatus: error %p", status);
			return;
		}
		glBindFramebufferEXT(GL_FRAMEBUFFER, 0);
	}

	void resize(unsigned int screen_width, unsigned int screen_height)
	{
		glBindTexture(GL_TEXTURE_2D, fbo_texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, screen_width, screen_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glBindTexture(GL_TEXTURE_2D, 0);

		glBindRenderbufferEXT(GL_RENDERBUFFER, rbo_depth);
		glRenderbufferStorageEXT(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, screen_width, screen_height);
		glBindRenderbufferEXT(GL_RENDERBUFFER, 0);
	}

	void dispose(void)
	{
		glDeleteFramebuffers(1, &fbo);
	}

	GLuint fbo_texture, fbo, rbo_depth;
};