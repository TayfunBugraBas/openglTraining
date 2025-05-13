#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

class ShaderClass {

public:
	unsigned int ID;
	ShaderClass(const char* vShadeFileName, const char* fShaderFileName) {
		std::string vFileString;
		std::string fFileString;
		std::ifstream vFileStream;
		std::ifstream fFileStream;

		vFileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fFileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try {
			vFileStream.open(vShadeFileName);
			fFileStream.open(fShaderFileName);

			std::stringstream tempStrv;
			std::stringstream tempStrf;

			tempStrv << vFileStream.rdbuf();
			tempStrf << fFileStream.rdbuf();

			vFileString = tempStrv.str();
			fFileString = tempStrf.str();

			vFileStream.close();
			fFileStream.close();
		}
		catch (std::ifstream::failure e) {
			std::cout << " Init Shader Failed" << std::endl;
		}
		const char* vChar;
		const char* fChar;

		vChar = vFileString.c_str();
		fChar = fFileString.c_str();

		unsigned int vertex, fragment;

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vChar, NULL);
		glCompileShader(vertex);
		CheckCompileStatus(vertex, 0);

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fChar, NULL);
		glCompileShader(fragment);
		CheckCompileStatus(fragment, 1);

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		CheckCompileStatus(ID, 2);

		glDeleteShader(vertex);
		glDeleteShader(fragment);

	}
	void Use() {
		glUseProgram(ID);
	}
	void setBool(const std::string& name, bool value) {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), int(value));
	}
	void setInteger(const std::string& name, int value) {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setFloat(const std::string& name, float value) {
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}
private:
	void CheckCompileStatus(unsigned int shader, int type) {
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