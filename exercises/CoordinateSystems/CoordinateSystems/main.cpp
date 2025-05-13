#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "stb_image.h"
#include "shaderssss.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


void SFBSC(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, 800, 600);
}


int main() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Coordinate Systems", NULL, NULL);

	if (!window) {
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		return -1;
	}
	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, SFBSC);

	ShaderClass shader("C:/Users/Bugra/source/repos/CoordinateSystems/CoordinateSystems/vertexShader.s", "C:/Users/Bugra/source/repos/CoordinateSystems/CoordinateSystems/fragmentShader.s");

	float vertices[] = {
		// positions               // texture coords
		 0.5f,  0.5f, 0.0f,     1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,     1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,     0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,     0.0f, 1.0f  // top left 
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	unsigned int VBO, VAO, EBO;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3* sizeof(float)));
	glEnableVertexAttribArray(1);
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data;
	int w, h, NrC;
	unsigned int Textures[2];

	glGenTextures(2, Textures);
	glBindTexture(GL_TEXTURE_2D, Textures[0]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load("container.jpg", &w, &h, &NrC, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "failed to load image" << std::endl;
	}
	stbi_image_free(data);


	glBindTexture(GL_TEXTURE_2D, Textures[1]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load("awesomeface.png", &w, &h, &NrC, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "failed to load image" << std::endl;
	}
	stbi_image_free(data);
	shader.Use();
	shader.setInteger("texture1", 0);
	shader.setInteger("texture2", 1);



	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.1f, 0.5f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Textures[0]);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, Textures[1]);
		
		//glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f); // orthographic clip view sað, sol, yukarý aþaðý, arka ve ön olmak üzere bu koordinat pixelleri  dýþýnda kalanlarý göstermez
		//perspektifi hesaba katmadýðý için gerçekçi gözükmez
		//glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)800 / 600, 0.1f, 100.0f);
		//fov (field of view) görüþ açýsý, aspect ratio yükseklik/geniþlik, ucak ve yakýn düzlük frustrum'un
		glm::mat4 trans = glm::mat4(1.0);
		float sinOfTime = sin(glfwGetTime());
		trans = glm::translate(trans, glm::vec3(sinOfTime, sinOfTime, sinOfTime));

		shader.Use();
		unsigned int gLoc = glGetUniformLocation(shader.ID, "transform");
		glUniformMatrix4fv(gLoc, 1, GL_FALSE, glm::value_ptr(trans));


		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		glfwPollEvents();
	}



	glfwTerminate();
	return 0;
}