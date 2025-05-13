#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>

class ShaderClass {

public:
	unsigned int ID;
	ShaderClass(const char* vCodeFile, const char* fCodeFile) {
		std::string vCodeString;
		std::string fCodeString;
		std::ifstream vCodeStreamer;
		std::ifstream fCodeStreamer;

		vCodeStreamer.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fCodeStreamer.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try {
			vCodeStreamer.open(vCodeFile);
			fCodeStreamer.open(fCodeFile);

			std::stringstream vCodeStream;
			std::stringstream fCodeStream;

			vCodeStream << vCodeStreamer.rdbuf();
			fCodeStream << fCodeStreamer.rdbuf();

			vCodeString = vCodeStream.str();
			fCodeString = fCodeStream.str();

			vCodeStreamer.close();
			fCodeStreamer.close();
		}
		catch (std::ifstream::failure e) {
			std::cout << " Failed To Initialize" << std::endl;
		}
		const char* vChar;
		const char* fChar;

		vChar = vCodeString.c_str();
		fChar = fCodeString.c_str();
		unsigned int vertex, fragment;

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vChar, NULL);
		glCompileShader(vertex);
		CheckCompile(vertex, 0);

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fChar, NULL);
		glCompileShader(fragment);
		CheckCompile(fragment, 1);


		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		CheckCompile(ID, 2);

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

	void CheckCompile(unsigned int shader, int type) {
		int success;
		char infolog[512];
		if (type != 2) {
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(shader, 512, NULL, infolog);
				std::cout << "Shader compile/link error: " << infolog << std::endl;
			}
		}
		else {
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(shader, 512, NULL, infolog);
				std::cout << "Shader compile/link error: " << infolog << std::endl;
			}
		}
	}

};

#endif
