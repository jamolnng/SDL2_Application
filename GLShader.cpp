#include "GLShader.h"
#include <vector>
#include <fstream>

std::string read(std::string value)
{
	std::ifstream t(value);
	std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
	return str;
}

GLShader::GLShader(void) : _numAttributes(0), _programID(0), _vertexShaderID(0), _fragmentShaderID(0)
{
}


GLShader::~GLShader(void)
{
}

GLuint GLShader::getShader(void)
{
	return _programID;
}

void GLShader::compileShaders(const std::string& shaderName)
{
	std::string vertexShaderFilePath = "../data/shaders/vertex/" + shaderName + ".glsl";
	std::string fragmentShaderFilePath = "../data/shaders/fragment/" + shaderName + ".glsl";
	//Vertex and fragment shaders are successfully compiled.
	//Now time to link them together into a program.
	//Get a program object.
	_programID = glCreateProgram();

	//Create the vertex shader object, and store its ID
	_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (_vertexShaderID == 0)
	{
		printf("Vertex shader failed to be created!\n");
	}

	//Create the fragment shader object, and store its ID
	_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (_fragmentShaderID == 0)
	{
		printf("Fragment shader failed to be created!\n");
	}

	//Compile each shader
	compileShader(vertexShaderFilePath, _vertexShaderID);
	compileShader(fragmentShaderFilePath, _fragmentShaderID);
}

//Compiles the shaders into a form that your GPU can understand
void GLShader::compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
{
	//Vertex and fragment shaders are successfully compiled.
	//Now time to link them together into a program.
	//Get a program object.
	_programID = glCreateProgram();

	//Create the vertex shader object, and store its ID
	_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (_vertexShaderID == 0)
	{
		printf("Vertex shader failed to be created!\n");
	}

	//Create the fragment shader object, and store its ID
	_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (_fragmentShaderID == 0)
	{
		printf("Fragment shader failed to be created!\n");
	}

	//Compile each shader
	compileShader(vertexShaderFilePath, _vertexShaderID);
	compileShader(fragmentShaderFilePath, _fragmentShaderID);
}

void GLShader::linkShaders(void)
{
	//Attach our shaders to our program
	glAttachShader(_programID, _vertexShaderID);
	glAttachShader(_programID, _fragmentShaderID);

	//Link our program
	glLinkProgram(_programID);

	//Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		//std::vector<char> errorLog1(maxLength);
		//glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);



		//We don't need the program anymore.
		glDeleteProgram(_programID);
		//Don't leak shaders either.
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);

		//print the error log and quit
		//std::printf("%s\n", &(errorLog[0]));
		printf("Shaders failed to link!\n");
	}

	//Always detach shaders after a successful link.
	glDetachShader(_programID, _vertexShaderID);
	glDetachShader(_programID, _fragmentShaderID);
	glDeleteShader(_vertexShaderID);
	glDeleteShader(_fragmentShaderID);
}

//Adds an attribute to our shader. SHould be called between compiling and linking.
void GLShader::addAttribute(const std::string& attributeName)
{
	glBindAttribLocation(_programID, _numAttributes++, attributeName.c_str());
}

GLuint GLShader::getUniformLocation(const std::string& uniformName)
{
	GLint location = glGetUniformLocation(_programID, uniformName.c_str());
	if (location == GL_INVALID_INDEX)
	{
		printf(std::string("Uniform " + uniformName + " not found in shader!\n").c_str());
	}

	return location;
}


//enable the shader, and all its attributes
void GLShader::use(void)
{
	glUseProgram(_programID);
	//enable all the attributes we added with addAttribute
	for (int i = 0; i < _numAttributes; i++) {
		glEnableVertexAttribArray(i);
	}
}

//disable the shader
void GLShader::unuse(void)
{
	glUseProgram(0);
	for (int i = 0; i < _numAttributes; i++) {
		glDisableVertexAttribArray(i);
	}

}

//Compiles a single shader file
void GLShader::compileShader(const std::string& filePath, GLuint id)
{

	//Open the file
	/*std::ifstream shaderFile(filePath);
	if (shaderFile.fail())
	{
	perror(filePath.c_str());
	std::string s("Failed to open " + filePath + "\n");
	printf(s.c_str());
	}

	//File contents stores all the text in the file
	std::string fileContents = "";
	//line is used to grab each line of the file
	std::string line;

	//Get all the lines in the file and add it to the contents
	while (std::getline(shaderFile, line))
	{
	fileContents += line + "\n";
	}

	shaderFile.close();//*/


	std::string fileContents = read(filePath);

	//get a pointer to our file contents c string;
	const char* contentsPtr = fileContents.c_str();
	//tell opengl that we want to use fileContents as the contents of the shader file
	glShaderSource(id, 1, &contentsPtr, nullptr);

	//compile the shader
	glCompileShader(id);

	//check for errors
	GLint success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

		//Provide the infolog in whatever manor you deem best.
		//Exit with failure.
		glDeleteShader(id); //Don't leak the shader.

		//Print error log and quit
		std::printf("%s\n", &(errorLog[0]));
		printf(std::string("Shader " + filePath + " failed to compile").c_str());
	}

}

GLuint GLShader::getAttribLocation(const std::string& attribName)
{
	return glGetAttribLocation(_programID, attribName.c_str());
}

void GLShader::compileShadersFromSource(const std::string& vertexSource, const std::string& fragmentSource)
{
	//Vertex and fragment shaders are successfully compiled.
	//Now time to link them together into a program.
	//Get a program object.
	_programID = glCreateProgram();

	//Create the vertex shader object, and store its ID
	_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (_vertexShaderID == 0)
	{
		printf("Vertex shader failed to be created!\n");
	}

	//Create the fragment shader object, and store its ID
	_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (_fragmentShaderID == 0)
	{
		printf("Fragment shader failed to be created!\n");
	}

	GLuint id = _vertexShaderID;

	//Compile each shader
	std::string fileContents = vertexSource;

	//get a pointer to our file contents c string;
	const char* contentsPtr = fileContents.c_str();
	//tell opengl that we want to use fileContents as the contents of the shader file
	glShaderSource(id, 1, &contentsPtr, nullptr);

	//compile the shader
	glCompileShader(id);

	//check for errors
	GLint success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

		//Provide the infolog in whatever manor you deem best.
		//Exit with failure.
		glDeleteShader(id); //Don't leak the shader.

		//Print error log and quit
		std::printf("%s\n", &(errorLog[0]));
		printf(std::string("Shader \n\"" + vertexSource + "\"\n failed to compile").c_str());
	}

	id = _fragmentShaderID;

	fileContents = fragmentSource;

	//get a pointer to our file contents c string;
	contentsPtr = fileContents.c_str();
	//tell opengl that we want to use fileContents as the contents of the shader file
	glShaderSource(id, 1, &contentsPtr, nullptr);

	//compile the shader
	glCompileShader(id);

	//check for errors
	success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

		//Provide the infolog in whatever manor you deem best.
		//Exit with failure.
		glDeleteShader(id); //Don't leak the shader.

		//Print error log and quit
		std::printf("%s\n", &(errorLog[0]));
		printf(std::string("Shader \n\"" + fragmentSource + "\"\n failed to compile").c_str());
	}
}

void GLShader::dispose(void)
{
	glDeleteProgram(_programID);
}