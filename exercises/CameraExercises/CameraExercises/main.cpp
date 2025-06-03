#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stb_image.h"
#include "shader.h"

void processInput(GLFWwindow* window);

void SFBSCB(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

float deltaTime = 0.0f;
float lastFrame = 0.0;
glm::vec3 Camerafront = glm::vec3(0.0, 0.0, -1.0);
float FOV = 45.0f;
double lastX;
double lastY;
bool firstMouseMove = true;
float yaw = -90.0f;
float pitch = 0.0f;
glm::vec3 CameraUp = glm::vec3(0.0, 1.0, 0.0);
glm::vec3 CameraPos = glm::vec3(0.0, 0.0, 3.0);

int main() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Camera Exercise", NULL, NULL);

	if (!window) {
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		return -1;
	}

	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, SFBSCB);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	float vertices[] = {
		// positions               // texture coords
		-0.5f, -0.5f, -0.5f,     0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,     1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,     1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,     1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f,     0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,     0.0f, 0.0f,

		-0.5f, -0.5f, 0.5f,     0.0f, 0.0f,
		 0.5f, -0.5f, 0.5f,     1.0f, 0.0f,
		 0.5f,  0.5f, 0.5f,     1.0f, 1.0f,
		 0.5f,  0.5f, 0.5f,     1.0f, 1.0f,
		-0.5f,  0.5f, 0.5f,     0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f,     0.0f, 0.0f,

		 -0.5f, 0.5f, 0.5f,     1.0f, 0.0f,
		 -0.5f, 0.5f, -0.5f,     1.0f, 1.0f,
		 -0.5f,  -0.5f, -0.5f,     0.0f, 1.0f,
		-0.5f,  -0.5f, -0.5f,     0.0f, 1.0f,
		-0.5f,  -0.5f, 0.5f,     0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f,     1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,     1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,    1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,    0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,    0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,    0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,     1.0f, 0.0f,


		-0.5f, -0.5f, -0.5f,     0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,     1.0f, 1.0f,
		 0.5f, -0.5f, 0.5f,     1.0f, 0.0f,
		 0.5f, -0.5f, 0.5f,     1.0f, 0.0f,
		-0.5f,-0.5f, 0.5f,     0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,     0.0f, 1.0f,

		-0.5f, 0.5f, -0.5f,     0.0f, 1.0f,
		 0.5f, 0.5f, -0.5f,     1.0f, 1.0f,
		 0.5f, 0.5f, 0.5f,     1.0f, 0.0f,
		 0.5f, 0.5f, 0.5f,     1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f,     0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f,     0.0f, 1.0f,

	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	ShaderClass shader("C:/Users/Bugra/source/repos/CameraExercises/CameraExercises/VShader.s", "C:/Users/Bugra/source/repos/CameraExercises/CameraExercises/FShader.s");

	unsigned int VBO, VAO, EBO;

	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	unsigned int textures[2];
	unsigned char* data;
	int w, h, NrC;

	glGenTextures(2, textures);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	data = stbi_load("container.jpg", &w, &h, &NrC, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "failed to load container" << std::endl;
	}

	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	data = stbi_load("awesomeface.png", &w, &h, &NrC, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "failed to load container" << std::endl;
	}
	stbi_image_free(data);


	glEnable(GL_DEPTH_TEST);

	shader.Use();
	shader.SetInt("texture1", 0);
	shader.SetInt("texture2", 1);


	while(!glfwWindowShouldClose(window)) {
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		shader.Use();
		processInput(window);


		glClearColor(0.3f, 0.2f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textures[0]);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textures[1]);



		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(FOV), 800.0f / 600.0f, 0.1f, 100.0f);
		shader.setMatrix4("projection", projection);

		glm::mat4 view = glm::mat4(1.0f);
		view = glm::lookAt(CameraPos, CameraPos + Camerafront, CameraUp);
		shader.setMatrix4("view", view);
		glBindVertexArray(VAO);

		for (unsigned int i = 0; i < 10; i++) {
			glm::mat4 model = glm::mat4(1.0);
			model = glm::translate(model, cubePositions[i]);
			model = glm::rotate(model, glm::radians(45.0f) * (float)glfwGetTime(), glm::vec3(0.2, 0.3, 0.5));
			shader.setMatrix4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}


		glfwSwapBuffers(window);

		glfwPollEvents();
	}


	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window) {
	float camSpeed = 0.05f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		CameraPos += camSpeed * Camerafront;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		CameraPos -= camSpeed * Camerafront;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		CameraPos -= glm::normalize(glm::cross(Camerafront, CameraUp) * camSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		CameraPos += glm::normalize(glm::cross(Camerafront, CameraUp) * camSpeed);
	}
	CameraPos.y = 0.0;
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouseMove) {
		lastX = xpos;
		lastY = ypos;
		firstMouseMove = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;
	float sensivity = 0.01f;
	xoffset *= sensivity;
	yoffset *= sensivity;
	
	yaw += xoffset;
	pitch += yoffset;
	if (pitch > 89.0f) {
		pitch = 89.0f;
	}
	if (pitch < -89.0f) {
		pitch = -89.0f;
	}
	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	Camerafront = glm::normalize(direction);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	FOV -= (float)yoffset;
	if (FOV < 1.0) {
		FOV = 1.0;
	}
	if (FOV > 45.0) {
		FOV = 45.0;
	}
}