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

class ShaderClass {

public:
	unsigned int ID;
	ShaderClass(const char* vShaderFile, const char* fShaderFile)
	{
		std::string vCodeNonChar;
		std::string fCodenonChar;
		std::ifstream vCodeFile;
		std::ifstream fCodeFile;

		vCodeFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fCodeFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try {
			vCodeFile.open(vShaderFile);
			fCodeFile.open(fShaderFile);

			std::stringstream vCodeStream, fCodeStream;

			vCodeStream << vCodeFile.rdbuf();
			fCodeStream << fCodeFile.rdbuf();

			vCodeNonChar = vCodeStream.str();
			fCodenonChar = fCodeStream.str();

			vCodeFile.close();
			fCodeFile.close();

		}
		catch (std::ifstream::failure e) {
			std::cout << "FAILED TO INITIALIZE SHADER" << std::endl;
		}
		const char* vCode;
		const char* fCode;

		vCode = vCodeNonChar.c_str();
		fCode = fCodenonChar.c_str();


		unsigned int vertex, fragment;

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vCode, NULL);
		glCompileShader(vertex);
		CheckCompileStatus(vertex, VERTEX);

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fCode, NULL);
		glCompileShader(fragment);
		CheckCompileStatus(fragment, FRAGMENT);

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);

		CheckCompileStatus(ID, PROGRAM);

		glDeleteShader(vertex);
		glDeleteShader(fragment);

	}
	void Use() {
		glUseProgram(ID);
	}
	void setBool(const std::string& uniform_name, bool value) {
		glUniform1i(glGetUniformLocation(ID, uniform_name.c_str()), int(value));
	}
	void setInteger(const std::string& uniform_name, int value) {
		glUniform1i(glGetUniformLocation(ID, uniform_name.c_str()), value);
	}
	void setFloat(const std::string& uniform_name, float value) {
		glUniform1f(glGetUniformLocation(ID, uniform_name.c_str()), value);
	}

private:

	void CheckCompileStatus(unsigned int shader, shader_en Type) {
		int success;
		char infolog[512];
		if (Type != 2) {
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