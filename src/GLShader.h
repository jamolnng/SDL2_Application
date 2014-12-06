#pragma once

#include <string>
#include <GL\glew.h>

class GLShader
{
	public:
		GLShader();
		~GLShader();

		GLuint getUniformLocation(const std::string& uniformName);
		GLuint getAttribLocation(const std::string& attribName);

		void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
		void compileShaders(const std::string& shaderName);
		void compileShadersFromSource(const std::string& vertexSource, const std::string& fragmentSource);
		void linkShaders();
		void addAttribute(const std::string& attributeName);
		void use();
		void unuse();

		static GLShader defaultShader(void);
		static GLuint mvploc;
		static GLuint texloc;

	private:
		void compileShader(const std::string& filepath, GLuint id);

		int _numAttributes;
		GLuint _programID;
		GLuint _vertexShaderID;
		GLuint _fragmentShaderID;

		static GLShader d_shader;
};