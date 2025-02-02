module;

#include <glad/glad.h>
#include <string>
#include <iostream>

export module GLSLUtil;


using namespace std;

export namespace GLSLUtil {


	int compileShader(const GLchar* vertexShaderSource, const GLchar* fragmentShaderSource) {

		unsigned int vertexShader;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);

		unsigned int fragmentShader;
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);


		int success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

		if (!success) {
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			throw runtime_error("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" + (string)infoLog);
		}

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			throw runtime_error("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" + (string)infoLog);
		}

		unsigned int shaderProgram = glCreateProgram();

		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			throw runtime_error("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" + (string)infoLog);
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		return shaderProgram;
	}

}