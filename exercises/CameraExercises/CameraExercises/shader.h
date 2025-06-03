#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>

class ShaderClass {
public:
	unsigned int ID;
	ShaderClass(const char* VFile, const char* FFile) {
		std::ifstream VSource;
		std::ifstream FSource;
		std::string VString;
		std::string FString;

	

		try {
			VSource.open(VFile);
			FSource.open(FFile);

			std::stringstream VStream;
			std::stringstream FStream;


			VStream << VSource.rdbuf();

			FStream << FSource.rdbuf();

			VString = VStream.str();
			FString = FStream.str();


			VSource.close();
			FSource.close();
		}
		catch (std::ifstream::failure e) {
			std::cout << e.what() << std::endl;
		}
	
		

		const char* V;
		const char* F;

		V = VString.c_str();
		F = FString.c_str();

		unsigned int Vs, Fs;

		Vs = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(Vs, 1, &V, NULL);
		glCompileShader(Vs);
		CheckCompileStatus(Vs, 0);


		Fs = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(Fs, 1, &F, NULL);
		glCompileShader(Fs);
		CheckCompileStatus(Fs, 1);


		ID = glCreateProgram();
		glAttachShader(ID, Vs);
		glAttachShader(ID, Fs);
		glLinkProgram(ID);

		glDeleteShader(Vs);
		glDeleteShader(Fs);
	}
	void Use() {
		glUseProgram(ID);
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
	void setMatrix4(const std::string& name, glm::mat4& value) {
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
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
