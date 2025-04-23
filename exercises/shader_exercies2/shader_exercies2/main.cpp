#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shaders.h"
void set_frame_buffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

int main() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "shader exercise 2", NULL, NULL);

	if (!window) {
		return -1;
	}
	glfwMakeContextCurrent(window);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		return -1;
	}

	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, set_frame_buffer_size_callback);

	float vertices[] = {

		-0.9f,-0.5f,0.0f, 1.0f, 0.0f, 0.0f,
		-0.0f,-0.5f,0.0f, 0.0f, 1.0f, 0.0f,
		-0.45f,0.5f,0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, 0.5f,0.0f , 1.0f, 0.0f, 0.0f,
	};
	unsigned int indices[] = {
		0,1,2

	};

	unsigned int VBO, VAO, EBO;

	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//SHADER CODES HERE
	shaderClass shader("C:/Users/Bugra/source/repos/shader_exercies2/shader_exercies2/vertexShader.s","C:/Users/Bugra/source/repos/shader_exercies2/shader_exercies2/fragmentShader.s");

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	float offset = 0.1f;
	bool WalkWay = true;

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.4f, 0.3f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//SHADER CODES HERE
		shader.Use();

		if ( WalkWay == true) {
			offset += 0.01f;
			if (offset >= 0.7f) {
				WalkWay = false;
			}
		}
		else if( WalkWay == false){
			offset -= 0.01f;
			if (offset <= 0.2f) {
				WalkWay = true;
			}
		}
		shader.setFloat("xOffset", offset);
		shader.setFloat("yOffset", offset);
		
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}




	glfwTerminate();
	return 0;
}