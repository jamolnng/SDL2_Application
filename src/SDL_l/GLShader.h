#pragma once

#include "gl3w.h"
#include <GL\GL.h>
#include <GL\GLU.h>
#include "SDL_Utils.h"
#include "GLObject.h"
#include <map>
#include <utility>
#include <vector>

using std::map;
using std::vector;

class GLShader : public GLObject<GLuint>
{
	public:
		GLShader(const char* vertexFile, const char* fragmentFile);
		GLShader(void);
		~GLShader(void);

		void createVertexProgram(const char* vertexFile);
		void createFragmentProgram(const char* fragmentFile);
		void createShaderProgram(const char* vertexFile, const char* fragmentFile);
		void createShaderProgram(GLuint vertexProgram, GLuint fragmentProgram);
		void link(void);
		GLuint getVertexProgram(void);
		GLuint getFragmentProgram(void);
		bool registerUniform(const char* name);
		bool registerAttrib(const char* name);
		void dispose(void);
		bool setUniformd(const char* name, double* values, unsigned int count = 1);
		bool setUniformdv(const char* name, double* values, unsigned int count = 1);
		bool setUnformf(const char* name, float* values, unsigned int count = 1);
		bool setUnformfv(const char* name, float* values, unsigned int count = 1);
		bool setUniformi(const char* name, int* values, unsigned int count = 1);
		bool setUniformiv(const char* name, int* values, unsigned int count = 1);
		GLuint getAttrib(const char* name);
		GLuint getUniform(const char* name);

	private:
		GLuint vertexProgram, fragmentProgram;
		map<const char*, GLuint> uniforms;
		map<const char*, GLuint> attribs;
};