#include <glad/glad.h>
#include <sstream>
#include <iostream>
#include <string>
#include <fstream>
#include <glm/glm.hpp>





class ShaderClass {

public:
	unsigned int ID;

	ShaderClass(const char* VCodeFile, const char* FCodeFile) {
		std::ifstream VifStream;
		std::ifstream FifStream;
		std::string VStr;
		std::string FStr;

		VifStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		FifStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try {

			VifStream.open(VCodeFile);
			FifStream.open(FCodeFile);

			std::stringstream vCodess;
			std::stringstream fCodess;

			vCodess << VifStream.rdbuf();
			fCodess << FifStream.rdbuf();

			VStr = vCodess.str();
			FStr = fCodess.str();
			
			VifStream.close();
			FifStream.close();

		}
		catch (std::ifstream::failure e) {
			std::cout << e.what() << std::endl;
		}

		const char* V;
		const char* F;

		V = VStr.c_str();
		F = FStr.c_str();

		unsigned int Vs, Fs;

		Vs = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(Vs, 1, &V, NULL);
		glCompileShader(Vs);
		checkStat(Vs, 0);


		Fs = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(Fs, 1, &F, NULL);
		glCompileShader(Fs);
		checkStat(Fs, 1);


		ID = glCreateProgram();
		glAttachShader(ID,Vs);
		glAttachShader(ID,Fs);
		glLinkProgram(ID);
		checkStat(ID, 2);

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
	void setMatrix4v(const std::string& name, glm::mat4 value) {
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
	}
	void setVec3fv(const std::string& name, glm::vec3 &value) {
		glUniform3fv(glGetUniformLocation(ID, name.c_str()),1,&value[0]);
	}
	void setVec3(const std::string& name, float x, float y, float z) {
		glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
	}

private:
	void checkStat(unsigned int shader, int type) {
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