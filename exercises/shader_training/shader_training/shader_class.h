#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <sstream>
#include <fstream>
#include<string>
#include<iostream>

enum shader_en {
	VERTEX = 0,
	FRAGMENT = 1,
	PROGRAM = 2

} ;


class Shader {

public:
	unsigned int ID;

	Shader(const char* vertexShader, const char* fragmentShader) {
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;

		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try {
			vShaderFile.open(vertexShader);
			fShaderFile.open(fragmentShader);

			std::stringstream vShaderStream, fShaderStream;

			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();

			vShaderFile.close();
			fShaderFile.close();

			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();


		}
		catch (std::ifstream::failure e) {
			std::cout << "FILE ERROR" << std::endl;
		}
		const char* vCode = vertexCode.c_str();
		const char* fCode = fragmentCode.c_str();


		unsigned int vShader, fShader;
		vShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vShader, 1, &vCode, NULL);
		glCompileShader(vShader);
		ShaderErrorCheck(vShader, VERTEX);

		
		fShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fShader, 1, &fCode, NULL);
		glCompileShader(fShader);
		ShaderErrorCheck(fShader, FRAGMENT);

		ID = glCreateProgram();
		glAttachShader(ID, vShader);
		glAttachShader(ID, fShader);
		glLinkProgram(ID);
		ShaderErrorCheck(ID, PROGRAM);

		glDeleteShader(vShader);
		glDeleteShader(fShader);


	}
	void Use(){
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

private:
	
	void ShaderErrorCheck(unsigned int shader, shader_en shaderType) {
		int Success;
		char infolog[512];

		if(shaderType != 2){
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



#endif
