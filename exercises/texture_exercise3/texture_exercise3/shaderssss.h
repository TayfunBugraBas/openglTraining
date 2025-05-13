#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

class ShaderClass
{
public:
	unsigned int ID;
	ShaderClass(const char* vFileName, const char* fFileName) {
		std::string vFileCode;
		std::string fFileCode;
		std::ifstream fFileStrStream;
		std::ifstream vFileStrStream;

		fFileStrStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		vFileStrStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		
		try {
			fFileStrStream.open(fFileName);
			vFileStrStream.open(vFileName);
			
			std::stringstream V;
			std::stringstream F;

			V << vFileStrStream.rdbuf();
			F << fFileStrStream.rdbuf();

			vFileCode = V.str();
			fFileCode = F.str();

			fFileStrStream.close();
			vFileStrStream.close();
		}
		catch (std::ifstream::failure e) {
			std::cout << "FAILED TO INIT" << std::endl;
		}
		const char* Vcstr;
		const char* Fcstr;

		Vcstr = vFileCode.c_str();
		Fcstr = fFileCode.c_str();

		unsigned int vertex, fragment;

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &Vcstr, NULL);
		glCompileShader(vertex);
		CheckCompile(vertex, 0); 
			
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &Fcstr, NULL);
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
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}


private:

	void CheckCompile(unsigned int shader, int type) {
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
