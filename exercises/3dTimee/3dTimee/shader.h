#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <glm/glm.hpp>

class ShaderClass {
public:
	unsigned int ID;
	ShaderClass(const char* vCodeFile, const char* fCodeFile) {
		
		std::ifstream vCodeBuf;
		std::ifstream fCodeBuf;
		std::string vCodeString;
		std::string fCodeString;

		vCodeBuf.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fCodeBuf.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try {
			vCodeBuf.open(vCodeFile);
			fCodeBuf.open(fCodeFile);

			std::stringstream V;
			std::stringstream F;

			V << vCodeBuf.rdbuf();
			F << fCodeBuf.rdbuf();

			vCodeString = V.str();
			fCodeString = F.str();

			vCodeBuf.close();
			fCodeBuf.close();

		}
		catch (std::ifstream::failure e) {
			std::cout << e.what() << std::endl;
		}
		const char* Vc;
		const char* Fc;

		Fc = fCodeString.c_str();
		Vc = vCodeString.c_str();

		unsigned int Vs, Fs;
		Vs = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(Vs, 1, &Vc, NULL);
		glCompileShader(Vs);
		CheckCompileStatus(Vs, 0);

		Fs = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(Fs, 1, &Fc, NULL);
		glCompileShader(Fs);
		CheckCompileStatus(Fs, 1);

		ID = glCreateProgram();
		glAttachShader(ID, Vs);
		glAttachShader(ID, Fs);
		glLinkProgram(ID); 
		CheckCompileStatus(ID, 2);

		glDeleteShader(Vs);
		glDeleteShader(Fs);

	}
	void SetBool(const std::string& name, bool value) {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	void SetInt(const std::string& name, int value) {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	void SetFloat(const std::string& name, float value) {
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}
	void SetMat4(const std::string& name, glm::mat4 &value)  {
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
	}
	void Use() {
		glUseProgram(ID);
	}

private:
	void CheckCompileStatus(unsigned int  shader, int type) {
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



#endif SHADER_H
