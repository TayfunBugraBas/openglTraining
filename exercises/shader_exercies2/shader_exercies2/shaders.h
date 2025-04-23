#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

enum shader_en {
	VERTEX = 0,
	FRAGMENT = 1,
	PROGRAM = 2
};

class shaderClass
{
public:
	unsigned int ID;
	shaderClass(const char* vShaderSource, const char* fShaderSource) {
		std::string vShaderCode;
		std::string fShaderCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;

		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try {
			vShaderFile.open(vShaderSource);
			fShaderFile.open(fShaderSource);

			std::stringstream vStream, fStream;

			
			vStream << vShaderFile.rdbuf();
			fStream << fShaderFile.rdbuf();

			vShaderCode = vStream.str();
			fShaderCode = fStream.str();

			vShaderFile.close();
			fShaderFile.close();

		}
		catch(std::ifstream::failure e){

		}
		const char* vCode = vShaderCode.c_str();
		const char* fCode = fShaderCode.c_str();

		unsigned int vertex, fragment;

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vCode, NULL);
		glCompileShader(vertex);
		ShaderCompileControl(vertex, VERTEX);


		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fCode, NULL);
		glCompileShader(fragment);
		ShaderCompileControl(fragment, FRAGMENT);

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		ShaderCompileControl(ID, PROGRAM);

		glDeleteShader(vertex);
		glDeleteShader(fragment);

	}

	void Use() {
		glUseProgram(ID);
	}

	void setBool(const std::string& name, bool value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), int(value));
	}
	void setInt(const std::string& name, int value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setFloat(const std::string& name, float value) const {
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}



	~shaderClass();

private:

	void ShaderCompileControl(unsigned int shader, shader_en Type) {
		int Success;
		char infolog[512];
		if (Type != 2) {
			glGetShaderiv(shader, GL_COMPILE_STATUS, &Success);
			if (!Success) {
				glGetShaderInfoLog(shader, 512, NULL, infolog);
				std::cout << infolog << std::endl;
			}

		}
		else {
			glGetProgramiv(shader, GL_LINK_STATUS, &Success);
			if (!Success) {
				glGetProgramInfoLog(shader, 512, NULL, infolog);
				std::cout << infolog << std::endl;
			}
		}

	}

};




shaderClass::~shaderClass()
{
}

#endif

