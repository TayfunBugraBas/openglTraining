#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shaderClass.h"

void set_frame_buffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

int main() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600,"shader exercise 3", NULL, NULL);
	
	if (!window) {
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		return -1;
	}

	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, set_frame_buffer_size_callback);


	float vertices[] = {

		-0.9f,-0.5f,0.0f, 
		-0.0f,-0.5f,0.0f, 
		-0.45f,0.5f,0.0f, 
		-0.5f, 0.5f,0.0f 
	};
	unsigned int indices[] = {
		0,1,2

	};
	unsigned int EBO, VAO, VBO;
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//shader code here
	shaderClass shader("C:/Users/Bugra/source/repos/shader_exercise3/shader_exercise3/vertexShader.s", "C:/Users/Bugra/source/repos/shader_exercise3/shader_exercise3/fragmentShader.s");

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(0);

	glBindVertexArray(0);


	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.6f, 0.7f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.Use();

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}


	glfwTerminate();
	return 0;
}