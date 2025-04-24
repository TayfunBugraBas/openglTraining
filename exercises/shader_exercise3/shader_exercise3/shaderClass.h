#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
enum shader_en {
	VERTEX = 0,
	FRAGMENT = 1, 
	PROGRAM = 2
};

class shaderClass {
public:
	unsigned int ID;
	shaderClass(const char* vShaderFile, const char* fShaderFile)
	{
		std::string vShaderCode;
		std::string fShaderCode;
		std::ifstream vfile;
		std::ifstream ffile;

		vfile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		ffile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try {
			vfile.open(vShaderFile);
			ffile.open(fShaderFile);

			std::stringstream vCodeStream;
			vCodeStream << vfile.rdbuf();
			std::stringstream fCodeStream;
			fCodeStream << ffile.rdbuf();

			vShaderCode = vCodeStream.str();
			fShaderCode = fCodeStream.str();

			

		}
		catch(std::ifstream::failure e){
			std::cout << "FAILED TO CONSTRUCT SHADER" << std::endl;
		}
		const char* vCode;
		const char* fCode;
		vCode = vShaderCode.c_str();
		fCode = fShaderCode.c_str();
		unsigned int vertex, fragment;

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vCode, NULL);
		glCompileShader(vertex);
		CheckShaderCompile(vertex, VERTEX);

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fCode, NULL);
		glCompileShader(fragment);
		CheckShaderCompile(fragment, FRAGMENT);

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);

		glDeleteShader(vertex);
		glDeleteShader(fragment);

	}
	void Use() {
		glUseProgram(ID);
	}
	void setBool(const std::string& uniform, bool value) {
		glUniform1i(glGetUniformLocation(ID, uniform.c_str()), int(value));
	}
	void setInteger(const std::string& uniform, int value) {
		glUniform1i(glGetUniformLocation(ID, uniform.c_str()), value);
	}
	void setFloat(const std::string& uniform, float value) {
		glUniform1f(glGetUniformLocation(ID, uniform.c_str()), value);
	}

private:

	void CheckShaderCompile(unsigned int shader, shader_en type) {
		int success;
		char infolog[512];
		if (type != 2) {
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(shader, 512, NULL, infolog);
				std::cout << infolog << std::endl;
			}
		}
		else {
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(shader, 512, NULL, infolog);
				std::cout << infolog << std::endl;
			}
		}
	}

};

#endif