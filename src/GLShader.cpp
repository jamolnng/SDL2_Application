#include "GLShader.h"

void printShaderLog(GLuint shader)
{
	if( glIsShader( shader ) )
	{
		int infoLogLength = 0;
		int maxLength = infoLogLength;
		glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &maxLength );
		char* infoLog = new char[ maxLength ];
		glGetShaderInfoLog( shader, maxLength, &infoLogLength, infoLog );
		if( infoLogLength > 0 )
		{
			printf( "%s\n", infoLog );
		}
		delete[] infoLog;
	}
	else
	{
		printf( "Name %d is not a shader\n", shader );
	}
}

GLShader::GLShader(const char* vertex, const char* fragment)
{
	createShaderProgramFromFile(vertex, fragment);
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

void GLShader::createShaderProgramFromFile(const char* vertexFile, const char* fragmentFile)
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

void GLShader::createShaderProgram(const char* vertexSource, const char* fragmentSource)
{
	if (vertexSource != "")
	{
		vertexProgram = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexProgram, 1, (const GLchar**)&vertexSource, 0);
		glCompileShader(vertexProgram);

		GLint vShaderCompiled = GL_FALSE;
		glGetShaderiv(vertexProgram, GL_COMPILE_STATUS, &vShaderCompiled);
		if (vShaderCompiled != GL_TRUE)
		{
			printf("Unable to compile vertex shader %d!\n", vertexProgram);
			printShaderLog(vertexProgram);
		}
	}
	if (fragmentSource != "")
	{
		fragmentProgram = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentProgram, 1, (const GLchar**)&fragmentSource, 0);
		glCompileShader(fragmentProgram);

		GLint vShaderCompiled = GL_FALSE;
		glGetShaderiv(fragmentProgram, GL_COMPILE_STATUS, &vShaderCompiled);
		if (vShaderCompiled != GL_TRUE)
		{
			printf("Unable to compile fragment shader %d!\n", fragmentProgram);
			printShaderLog(fragmentProgram);
		}
	}

	value = glCreateProgram();
	if (vertexSource != "") glAttachShader(value, vertexProgram);
	if (fragmentSource != "") glAttachShader(value, fragmentProgram);
	link();
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

GLuint GLShader::get(void)
{
	return value;
}

GLuint* GLShader::create(const char* vertexSource, const char* fragmentSource)
{
	GLuint out[3];
	if (vertexSource != "")
	{
		out[1] = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(out[1], 1, (const GLchar**)&vertexSource, 0);
		glCompileShader(out[1]);

		GLint vShaderCompiled = GL_FALSE;
		glGetShaderiv(out[1], GL_COMPILE_STATUS, &vShaderCompiled);
		if (vShaderCompiled != GL_TRUE)
		{
			printf("Unable to compile vertex shader %d!\n", out[1]);
			printShaderLog(out[1]);
		}
	}
	if (fragmentSource != "")
	{
		out[2] = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(out[2], 1, (const GLchar**)&fragmentSource, 0);
		glCompileShader(out[2]);

		GLint vShaderCompiled = GL_FALSE;
		glGetShaderiv(out[2], GL_COMPILE_STATUS, &vShaderCompiled);
		if (vShaderCompiled != GL_TRUE)
		{
			printf("Unable to compile fragment shader %d!\n", out[2]);
			printShaderLog(out[2]);
		}
	}

	out[0] = glCreateProgram();
	if (vertexSource != "") glAttachShader(out[0], out[1]);
	if (fragmentSource != "") glAttachShader(out[0], out[2]);
	glLinkProgram(out[0]);
	return out;
}