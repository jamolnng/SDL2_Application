#pragma once

#include <string>
#include <GL\glew.h>
#include <map>

class GLShader
{
	public:
		GLShader();
		~GLShader();

		GLuint getUniformLocation(const std::string& uniformName);
		GLuint getAttribLocation(const std::string& attribName);
		GLuint getShader(void);

		void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
		void compileShaders(const std::string& shaderName);
		void compileShadersFromSource(const std::string& vertexSource, const std::string& fragmentSource);
		void linkShaders(void);
		void addAttribute(const std::string& attributeName);
		void use(void);
		void unuse(void);
		void dispose(void);

	private:
		void compileShader(const std::string& filepath, GLuint id);

		int _numAttributes;
		GLuint _programID;
		GLuint _vertexShaderID;
		GLuint _fragmentShaderID;
};