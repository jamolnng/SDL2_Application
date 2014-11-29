#include "GLShader.h"

GLShader::GLShader(const char* vertex, const char* fragment)
{
	createShaderProgram(vertex, fragment);
}

GLShader::GLShader(void)
{
}

GLShader::~GLShader(void)
{
}

void GLShader::createVertexProgram(const char* vertexFile)
{
	const char* shader = SDL_Utils::readFile(vertexFile);
	vertexProgram = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexProgram, 1, (const GLchar**)&shader, 0);
	glCompileShader(vertexProgram);
}

void GLShader::createFragmentProgram(const char* fragmentFile)
{
	const char* shader = SDL_Utils::readFile(fragmentFile);
	fragmentProgram = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentProgram, 1, (const GLchar**)&shader, 0);
	glCompileShader(fragmentProgram);
}

void GLShader::createShaderProgram(const char* vertexFile, const char* fragmentFile)
{
	createVertexProgram(vertexFile);
	createFragmentProgram(fragmentFile);
	createShaderProgram(vertexProgram, fragmentProgram);
}

void GLShader::createShaderProgram(GLuint vertexProgram, GLuint fragmentProgram)
{
	value = glCreateProgram();
	glAttachShader(value, vertexProgram);
	glAttachShader(value, fragmentProgram);
}

void GLShader::link(void)
{
	glLinkProgram(value);
}

GLuint GLShader::getVertexProgram(void)
{
	return vertexProgram;
}

GLuint GLShader::getFragmentProgram(void)
{
	return fragmentProgram;
}

bool GLShader::registerUniform(const char* name)
{
	if (value == 0) return 0;
	map<const char*, GLuint>::iterator it = uniforms.find(name);
	//if (it == uniforms.end()) return false;
	GLuint id = glGetUniformLocation(value, name);
	if (id != 0)
	{
		uniforms[name] = id;
		return true;
	}
	return false;
}

bool GLShader::registerAttrib(const char* name)
{
	if (value == 0) return 0;
	map<const char*, GLuint>::iterator it = attribs.find(name);
	//if (it == uniforms.end()) return false;
	GLuint id = glGetAttribLocation(value, name);
	if (id != 0)
	{
		attribs[name] = id;
		return true;
	}
	return false;
}

void GLShader::dispose(void)
{
	glDeleteProgram(value);
	uniforms.clear();
	attribs.clear();
}

bool GLShader::setUniformd(const char* name, double* values, unsigned int count)
{
	if (value == 0) return 0;
	if (uniforms.empty()) return false;
	map<const char*, GLuint>::iterator it = uniforms.find(name);
	if (it == uniforms.end()) return false;
	
	switch (count)
	{
		case 1:
			glUniform1d(it->second, *values);
			break;
		case 2:
			glUniform2d(it->second, values[0], values[1]);
			break;
		case 3:
			glUniform3d(it->second, values[0], values[1], values[2]);
			break;
		case 4:
			glUniform4d(it->second, values[0], values[1], values[2], values[3]);
			break;
		default:
			return false;
	}
	return true;
}

bool GLShader::setUniformdv(const char* name, double* values, unsigned int count)
{
	if (value == 0) return 0;
	if (uniforms.empty()) return false;
	map<const char*, GLuint>::iterator it = uniforms.find(name);
	if (it == uniforms.end()) return false;

	switch (count)
	{
		case 1:
			glUniform1dv(it->second, count, values);
			break;
		case 2:
			glUniform2dv(it->second, count, values);
			break;
		case 3:
			glUniform3dv(it->second, count, values);
			break;
		case 4:
			glUniform4dv(it->second, count, values);
			break;
		default:
			return false;
	}
	return true;
}

bool GLShader::setUnformf(const char* name, float* values, unsigned int count)
{
	if (value == 0) return 0;
	if (uniforms.empty()) return false;
	map<const char*, GLuint>::iterator it = uniforms.find(name);
	if (it == uniforms.end()) return false;

	switch (count)
	{
		case 1:
			glUniform1f(it->second, *values);
			break;
		case 2:
			glUniform2f(it->second, values[0], values[1]);
			break;
		case 3:
			glUniform3f(it->second, values[0], values[1], values[2]);
			break;
		case 4:
			glUniform4f(it->second, values[0], values[1], values[2], values[3]);
			break;
		default:
			return false;
	}
	return true;
}

bool GLShader::setUnformfv(const char* name, float* values, unsigned int count)
{
	if (value == 0) return 0;
	if (uniforms.empty()) return false;
	map<const char*, GLuint>::iterator it = uniforms.find(name);
	if (it == uniforms.end()) return false;

	switch (count)
	{
		case 1:
			glUniform1fv(it->second, count, values);
			break;
		case 2:
			glUniform2fv(it->second, count, values);
			break;
		case 3:
			glUniform3fv(it->second, count, values);
			break;
		case 4:
			glUniform4fv(it->second, count, values);
			break;
		default:
			return false;
	}
	return true;
}

bool GLShader::setUniformi(const char* name, int* values, unsigned int count)
{
	if (value == 0) return 0;
	if (uniforms.empty()) return false;
	map<const char*, GLuint>::iterator it = uniforms.find(name);
	if (it == uniforms.end()) return false;

	switch (count)
	{
		case 1:
			glUniform1d(it->second, *values);
			break;
		case 2:
			glUniform2d(it->second, values[0], values[1]);
			break;
		case 3:
			glUniform3d(it->second, values[0], values[1], values[2]);
			break;
		case 4:
			glUniform4d(it->second, values[0], values[1], values[2], values[3]);
			break;
		default:
			return false;
	}
	return true;
}

bool GLShader::setUniformiv(const char* name, int* values, unsigned int count)
{
	if (value == 0) return 0;
	if (uniforms.empty()) return false;
	map<const char*, GLuint>::iterator it = uniforms.find(name);
	if (it == uniforms.end()) return false;

	switch (count)
	{
		case 1:
			glUniform1iv(it->second, count, values);
			break;
		case 2:
			glUniform2iv(it->second, count, values);
			break;
		case 3:
			glUniform3iv(it->second, count, values);
			break;
		case 4:
			glUniform4iv(it->second, count, values);
			break;
		default:
			return false;
	}
	return true;
}

GLuint GLShader::getAttrib(const char* name)
{
	if (value == 0) return 0;
	if (attribs.empty()) return 0;
	map<const char*, GLuint>::iterator it = attribs.find(name);
	if (it == attribs.end()) return 0;
	return it->second;
}

GLuint GLShader::getUniform(const char* name)
{
	if (value == 0) return 0;
	if (uniforms.empty()) return 0;
	map<const char*, GLuint>::iterator it = uniforms.find(name);
	if (it == uniforms.end()) return 0;
	return it->second;
}