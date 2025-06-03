#ifndef SHADER_H
#define SHADER_H


#include <glad/glad.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <glm/glm.hpp>

class ShaderClass {
public:
	unsigned int ID;
	ShaderClass(const char* VCodeFile, const char* FCodeFile){
	
		std::ifstream VStream;
		std::ifstream FStream;
		std::string VString;
		std::string FString;


		VStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		FStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try {
			VStream.open(VCodeFile);
			FStream.open(FCodeFile);

			std::stringstream Vss;
			std::stringstream Fss;

			Vss << VStream.rdbuf();
			Fss << FStream.rdbuf();

			VString = Vss.str();
			FString = Fss.str();

			VStream.close();
			FStream.close();
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
		CheckCompileStat(Vs, 0);

		Fs = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(Fs, 1, &F, NULL);
		glCompileShader(Fs);
		CheckCompileStat(Fs, 1);

		ID = glCreateProgram();
		glAttachShader(ID,Vs);
		glAttachShader(ID, Fs);
		glLinkProgram(ID);
		CheckCompileStat(ID, 2);

		glDeleteShader(Vs);
		glDeleteShader(Fs);
	}
	void Use() {
		glUseProgram(ID);
	}
	void setBool(const std::string& name, bool value) {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	void setInt(const std::string& name, int value) {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setFloat(const std::string& name, float value) {
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setMatrix4(const std::string& name, glm::mat4 value) {
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
	}
private:
	void CheckCompileStat(unsigned int Shader, int type) {
		int success;
		char infolog[512];
		if (type != 2) {
			glGetShaderiv(Shader, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(Shader, 512, NULL, infolog);
				std::cout << infolog << std::endl;
			}
		}
		else {
			glGetProgramiv(Shader, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(Shader, 512, NULL, infolog);
				std::cout << infolog << std::endl;
			}
		}

	}

};




#endif
